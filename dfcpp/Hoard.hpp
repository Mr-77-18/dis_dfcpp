//
// Created by Gboom on 11/18/22.
//

#ifndef DFCPP_HOARD_HPP
#define DFCPP_HOARD_HPP

#include "NumaNum.hpp"
#include <numa.h>
#include <numaif.h>
#include <vector>
#include <thread>
#include <mutex>
#include <stdexcept>
#include <atomic>
#include <cassert>


namespace DFCPP{

    constexpr int F = 4;    // emptiness threshold
    constexpr int K = 4;    // shrinkage constant
    constexpr size_t S = 4096 << 2;  // 超级块大小，必须为系统页的整数倍


    /**
     * @brief 用于分配特定大小内存的Hoard
     */
    class HoardSizeSpec{
    private:
        struct SuperBlockList{
            SuperBlockList* prev;
            SuperBlockList* next;
            SuperBlockList() {
                prev = this;
                next = this;
            }
        };

        struct GlobalHeap{
            SuperBlockList list;
            std::mutex  mutex;
        };

        struct LocalHeap{
            std::mutex mutex;
            SuperBlockList lists[F + 1];    // 区分不同的使用量。下标越大，使用率越高
            size_t u = 0;   // 使用量
            size_t a = 0;   // 分配量
        };

        struct SuperBlock{
            SuperBlockList list;
            std::atomic<LocalHeap*> heap{nullptr};
            size_t u = 0;               // 使用量
            size_t i = 0;               // 下一个分配的下标索引，当activateItem为空时
            char* activateItem = nullptr;     // 下一个可分配的内存
            char* data = nullptr;             // 缓冲区
        };

    public:
        /**
         * @param node  numa节点
         * @param s     对象大小
         * @param n     localHeap数量
         */
        HoardSizeSpec(int node, size_t s, size_t n);

        /**
         * @brief   分配一项
         * @return  返回分配的地址
         */
        void* alloc();

        void* allocWithThreadId(size_t id);

        /**
         * @brief   回收地址p
         */
        void free(void* p);

    private:
        const int _node;            // numa节点
        const size_t  _size;        // 每个对象大小，即一次分配多少内存
        const size_t _m;            // 每个超级块可以存储的对象数量
        const size_t _w;
        const size_t _n;            // localHeap数量
        GlobalHeap  _globalHeap;
        std::vector<LocalHeap> _localHeaps;

        /**
         * @brief   返回该超级块所属的bin下标
         */
        size_t _binIndex(size_t u) const;
        /**
         * @brief 是否为空链
         */
        static bool _blockIsEmpty(SuperBlockList* head);
        /**
         * @brief   p作为链表第一项，即head的下一项
         */
        static void _emplaceBefore(SuperBlockList* head, SuperBlockList* p);
        /**
         * @brief           从链表中删除一项
         * @param prev      待删除项的prev
         * @param next      待删除项的next
         */
        static void _removeFromList(SuperBlockList* p);
        /**
         * @brief 将p转换成对应的SuperBlock*
         */
        static SuperBlock* _superBlockListToSuperBlock(SuperBlockList* p);
        /**
         * @brief   从链表p中获取一项，将其从链表中删除并转换为SuperBlock*返回。
         * p必须为非空链表。
         */
        static SuperBlock* _getAndRemoveFromList(SuperBlockList*head);
    };

    void *HoardSizeSpec::alloc() {
        auto idx = std::hash<std::thread::id>()(std::this_thread::get_id());
        return allocWithThreadId(idx);
    }


    void *HoardSizeSpec::allocWithThreadId(size_t id) {
        SuperBlock* superBlock = nullptr;
        id = std::hash<size_t>()(id) % _n;
        LocalHeap& localHeap = _localHeaps[id];
        std::lock_guard<std::mutex> localLock(localHeap.mutex);
        int f = F - 1;
        for(; f >= 0; f--) {
            if(!_blockIsEmpty(&localHeap.lists[f])) {
                superBlock = _superBlockListToSuperBlock(localHeap.lists[f].next);      // 第一个为链表头
                break;
            }
        }
        assert(!(f > -1 && superBlock->data == nullptr));
        // if(f > -1 && superBlock->data == nullptr) {
        //     throw std::runtime_error("memory has not been allocated 1\n");
        // }
        if(f == -1) { // localHeap没有空闲的空间
            {
                std::lock_guard<std::mutex> globalLock(_globalHeap.mutex);
                if (!_blockIsEmpty(&_globalHeap.list)) {  // 非空
                    superBlock = _getAndRemoveFromList(_globalHeap.list.next);
                }
            }
            if(superBlock == nullptr) {
                superBlock = new SuperBlock;
                superBlock->data = (char *) numa_alloc_onnode(S, _node);     // 在线程的本地节点分配内存
                if(superBlock->data == nullptr) {       // 分配内存失败
                    throw std::bad_alloc();
                }
            }
            assert(superBlock && superBlock->data);
            // if(superBlock->data == nullptr) {
            //     throw std::runtime_error("memory has not been allocated 2\n");
            // }
            superBlock->heap = &localHeap;
            f = _binIndex(superBlock->u);
            _emplaceBefore(localHeap.lists[f].next, &superBlock->list);
            localHeap.a += _m;
            localHeap.u += superBlock->u;
        }

        void* mem;
        if(superBlock->activateItem) {
            mem = (void*)superBlock->activateItem;
            superBlock->activateItem = *(char**)(superBlock->activateItem);
        } else {
            mem = superBlock->data + superBlock->i * _size;
            superBlock->i++;
        }
        // 先记录此内存所属的SuperBlock，free时使用。
        *((SuperBlock**)mem) = superBlock;
        mem = (void*)((SuperBlock**)mem + 1);
        superBlock->u++;
        assert(superBlock->u <= _m);
        auto ff = _binIndex(superBlock->u);
        if(ff != f) {
            _removeFromList(&superBlock->list);
            _emplaceBefore(localHeap.lists[ff].next, &superBlock->list);
        }

        localHeap.u++;
        return mem;
    }

    size_t HoardSizeSpec::_binIndex(size_t u) const {
        return (u == _m) ? F : (u /_w) ;
    }

    HoardSizeSpec::HoardSizeSpec(int node, size_t s, size_t n):
            _node(node),
            _size(s),
            _m(S/s),
            _w{(_m + F - 1) / F},
            _n(n),
            _localHeaps(n)
    {}

    bool HoardSizeSpec::_blockIsEmpty(SuperBlockList * head) {
        return head->next == head;
    }

    void HoardSizeSpec::_emplaceBefore(SuperBlockList *node, SuperBlockList *p) {
        p->prev = node->prev;
        p->next = node;
        node->prev->next = p;
        node->prev = p;

    }

    void HoardSizeSpec::_removeFromList(SuperBlockList *p) {
        p->prev->next = p->next;
        p->next->prev = p->prev;
    }

    HoardSizeSpec::SuperBlock *HoardSizeSpec::_superBlockListToSuperBlock(SuperBlockList *p) {
        auto offset =  (size_t)&(((SuperBlock*) nullptr)->list);
        return (SuperBlock*) ((char*)(p) - offset);
    }

    HoardSizeSpec::SuperBlock *HoardSizeSpec::_getAndRemoveFromList(HoardSizeSpec::SuperBlockList *head) {
        _removeFromList(head);
        return _superBlockListToSuperBlock(head);
    }

    void HoardSizeSpec::free(void *p) {
        auto superBlock = *((SuperBlock**)p-1);
        bool sync = false;
        while(!sync) {
            auto localHeap = superBlock->heap.load();
            if(localHeap != nullptr) {
                std::lock_guard<std::mutex> localLock(localHeap->mutex);
                if(superBlock->heap == localHeap) {
                    sync = true;
                    auto f = _binIndex(superBlock->u);
                    superBlock->u--;
                    localHeap->u--;

                    *((char**)p-1) = superBlock->activateItem;
                    superBlock->activateItem = (char *)((char**)p-1);

                    auto ff = _binIndex(superBlock->u);
                    if(f != ff) {
                        _removeFromList(&superBlock->list);
                        _emplaceBefore(localHeap->lists[ff].next, &superBlock->list);
                    }

                    // 需要将一个SuperBlock转移到globalHeap
                    // if((localHeap->u * F < ((F - 1) * localHeap->a)) && (localHeap->u + K * _m < localHeap->a)) {
                    //     for(int i = 0; i < F; i++) {
                    //         if(!_blockIsEmpty(&localHeap->lists[i])) {
                    //             auto b = _superBlockListToSuperBlock(localHeap->lists[i].next);
                    //             _removeFromList(&b->list);
                    //             localHeap->u -= b->u;
                    //             localHeap->a -= _m;
                    //             std::lock_guard<std::mutex> lockGuard(_globalHeap.mutex);
                    //             _emplaceBefore(_globalHeap.list.next, &b->list);
                    //             b->heap = nullptr;       // todo: 这里应该要设置的，但是不知道为什么报错
                    //             break;
                    //         }
                    //     }
                    // }
                }
            }
            else {
                std::lock_guard<std::mutex> globalLock(_globalHeap.mutex);
                if(superBlock->heap.load() == nullptr) {
                    sync = true;
                    superBlock->u--;
                    *((char**)p-1) = superBlock->activateItem;
                    superBlock->activateItem = (char *)((char**)p-1);
                }
            }
        }
    }


    /**
     * @brief   每个numa节点有一个Hoard。
     * 每个Hoard拥有多个Heap，分别用于分配不同大小的内存。
     * 每个Heap又拥有多个bin，用于区分Heap的使用率。
     */
    class Hoard{
    public:
        void* alloc(size_t size);
        void* allocWithThreadId(size_t threadId, size_t size);
        void free(void* p, size_t size);

        Hoard(int node);

    private:

        std::vector<HoardSizeSpec*> _hoards;
        int _node;      // numa node


        /**
         * @brief   返回一个2的指数值，即实际分配的内存大小。
         * 最小为一个指针大小。
         */
        static size_t _getExponentSize(size_t size);
        static size_t _getSizeIndex(size_t size);
    };

    size_t Hoard::_getExponentSize(size_t size) {
        if(size > 0) {
            size--;
            size |= size >> 1;
            size |= size >> 2;
            size |= size >> 4;
            size |= size >> 8;
            size |= size >> 16;
            size |= size >> 32;
            size++;
        }
        return std::max(size, sizeof(void *));
    }

    void *Hoard::alloc(size_t size) {
        size += sizeof(void*);
        if(size > S / 2) {  // 大于S/2，直接分配
            auto res = numa_alloc_onnode(size, _node);
            if(res == nullptr)
                throw std::runtime_error("numa node has no enough memory");
            return res;
        }
        auto idx = _getSizeIndex(size);
        return _hoards[idx]->alloc();
    }

    void* Hoard::allocWithThreadId(size_t threadId, size_t size) {
        size += sizeof(void*);
        if(size > S / 2) {
            auto res = numa_alloc_onnode(size, _node);
            if(res == nullptr)
                throw std::runtime_error("numa node has no enough memory");
            return res;
        }
        auto idx = _getSizeIndex(size);
        return _hoards[idx]->allocWithThreadId(threadId);
    }

    size_t Hoard::_getSizeIndex(size_t size) {
        size_t idx = 0;
        size_t s = 8;
        while (size > s) {
            idx++;
            s <<= 1;
        }
        return idx;
    }

    void Hoard::free(void *p, size_t size) {
        if(size > S / 2)
        {
            numa_free(p, size);
            return;
        }
        auto idx = _getSizeIndex(size + sizeof(void*));   // 多一个SuperBlock*的空间
        _hoards[idx]->free(p);
    }

    Hoard::Hoard(int node): _node(node) {
        // TODO: 获取当前节点cpu数
        auto n = std::thread::hardware_concurrency();
        n /= NUMANUM;
        for(size_t i = sizeof(void*); i <= S; i*=2) {
            auto temp = new HoardSizeSpec(_node, i, n);
            _hoards.emplace_back(temp);
        }

    }


    class HoardNuma{
    public:
        HoardNuma();
        Hoard* getHoardByNuma(int numaNode) {
            return &_hoards[numaNode];
        }
        void free(int node, void* p, size_t size) {
            _hoards[node].free(p, size);
        }

        void* allocOnNumaNodeWithThreadID(int numaNode, size_t threadId, size_t size) {
            return _hoards[numaNode].allocWithThreadId(threadId, size);
        }

        void* alloc(int numaNode, size_t size) {
            return _hoards[numaNode].alloc(size);
        }

    private:
        int _numaNum;
        std::vector<Hoard> _hoards;
    };

    HoardNuma::HoardNuma():
            _numaNum(NUMANUM)
    {
        _hoards.reserve(NUMANUM);
        for(int i = 0; i < NUMANUM; i++) {
            _hoards.emplace_back(Hoard(i));
        }
    }



}

#endif //DFCPP_HOARD_HPP
