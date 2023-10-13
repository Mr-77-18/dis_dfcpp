# 改造框架
如图为大体框架
![框架](https://raw.githubusercontent.com/Mr-77-18/dis_dfcpp/main/image/1.png =300x300) 
流程大致分为如下：
```mermaid
timeline
title 改造流程
	单机改造 : 根据任务动态创建子图
	结合grpc : 搭建服务端
	掌控者改造 : 图信息掌控
   				 	 : 图的动态划分

`````
## 记录2023 7-6
### 新增部分通过"新增_lsh"索引
![新增](https://raw.githubusercontent.com/Mr-77-18/dis_dfcpp/main/image/3.png) 
到目前为止，初步完成如框架图所示中的单机中的改造。既可以完成服务启动之后监听任务，当拿到任务之后能执行对应任务的效果。

接下来说明到目前位置的改造过程:
1. 增加Node和DFV<T>两种数据类型的全局管理工具。（dfcpp/global.hpp)
2. 改造必要的函数：包括但不限于以下几个(在源代码中有“新增”标注，可以自己定位)
	1. DFGraph.createDFV<T>();
	2. DFGraph.emplace();
3. 结合gprc实现服务程序,监听任务到来。
---

#### 测试：example/main10.cpp
如下一个的示例展示改造之后于原来的差别在哪里(源码见example/main10.cpp)，其中以下部分是改造后需要新增的代码：
```c++
//模拟任务下发后得到的数据
vector<int> dfv_index = {3};
vector<int> task_index = {3 , 4};
vector<int> value = {77};

//同步前向dfv状态
gl.set_dfv_write(dfv_index , value);
//创建任务图
graph.cre_new_graph(task_index);

`````
![本地改造测试](https://raw.githubusercontent.com/Mr-77-18/dis_dfcpp/main/image/2.png) 
#### 测试：example/main_grpc
这个测试是把本地改造结合grpc，尝试接受发布过来的任务，然后执行任务的测试。
**main_grpc** 作为服务端,接受任务并执行
**grpc_dfcpp/send_client.cc** 作为客户端，发布任务

## 记录2023 7-7
今天完成了通信信息部分,可以看commu.proto文件（grpc_dfcpp/commu.proto)的第二版request部分,关键部分如下。
```protobuf
message threemess{
repeated int32 dfv_index = 1;
repeated int32 value = 2;
repeated int32 task_index = 3;
}

`````

对应的send_client.cc和send_server.cc展示了客户端和服务端传输信息的案例。

由于DFV<T>是一个模板类，所以最终版本的消息传递也应该支持传递不同的数据类型，这里可以用::google:protobuf::Any这个数据类型去实现，但有一点需要注意，就是只能泛化proto中定义的类型，可以参考grpc_dfcpp/any_proto/目录下的测试.

---

到此做一个总结：如图所示，红框内是执行体，它只需要三个元素**(三个元素就可以描述一个任务)** ：
1. vector<int> task_index
2. vector<int> dfv_index
3. vector<T> value
就可以执行。那么主要就看掌控者怎么传这三个元素。要注意的是第三个元素vector<T> value，是泛型的，即红框内是支持value是任意类型。但传输支不支持泛型又是另外一码事。这就要看你grpc的使用了。
![总结](https://raw.githubusercontent.com/Mr-77-18/dis_dfcpp/main/image/4.png =300x300) 
---


由于grpc我也是第一次使用，所有能传输说明，怎么传（代码怎么写）也是要探究的过程。这里阐述一下使用grpc和结合到dfcpp中的过程：
1. 首先在**grpc_dfcpp/** 目录下根据grpc的规则进行代码编写
	1. 定义.proto文件，产生源代码
	2. 编写server.cc和client.cc
2. 测试好之后就可以结合到dfcpp当中了，且非常容易，请看以下步骤。
	1. 在example/目录下根据main_grpc.cpp的模板重新写一个grpc的server,你只需要重写定义的rpc函数就可以了。只需要在example/CMakeLists.txt里面加上这个程序，产后cmake就行，即可产生server可执行程序。然后client可执行程序在第一步骤中已经生成了。

## 记录2023 7-8
今天解决残留问题：
**问题描述** 以上面main10.cpp图为例子，当我发布两个任务
1. 任务1 [task2 , task3]
2. 任务2 [task4 , task5]
会出现问题如下图所示，即task6节点也执行了，这是不符合设定的（设定是掌控者给你什么，你才能执行什么）

![问题](https://raw.githubusercontent.com/Mr-77-18/dis_dfcpp/main/image/5.png) \

**问题产生的原因** :在每一个执行线程当中，都会对readyDFV所指向的node进行操作，即使不在任务范围内的node也有可能会被executor执行。

**解决问题的方法** :限制操作范围，只允许线程操作任务范围内的node。解决完问题之后的结果如下：
![解决](https://raw.githubusercontent.com/Mr-77-18/dis_dfcpp/main/image/6.png) \
今天的新增内容通过"新增_7-8"索引

---

# 以下进入到掌控者改造，即第三步
## 记录2023 7-9 新增代码通过”新增_7-9索引"
首先构思以下掌控者要怎么做，前面也提到过掌控者的任务有以下：
1. 掌握全局图的信息
2. 图的划分
3. 发布任务给Executor
先初步设计掌控者逻辑如下：首先中间**红色** 部分表示掌控者的资源，即掌握全局图的信息；任务产生器用来图的划分，并将更新反馈给图更新器用来更新状态，然后发布任务给Executor;然后就是图更新器，用来接收Executor和任务生产器的反馈，以此来更新图的状态.
![掌控者](https://raw.githubusercontent.com/Mr-77-18/dis_dfcpp/main/image/7.png)

---

在图的管理上我采用了一个矩阵和两个一维数组，如下图所示。请听我慢慢道来。
![掌控者](https://raw.githubusercontent.com/Mr-77-18/dis_dfcpp/main/image/8.png) \
如图上半部分是图其中一种状态：
1. task1已经完成了
2. task2,task3发步出去了，但是还没有完成
图的下半部分用来描述整个图的信息：
1. node_status数组用来表示node(task)的状态
	1. 0表示task还没有发布
	2. 1表示任务发布了但还没有执行
	3. 2表示任务执行完了。即从executor得到反馈了
2. dfv_value数组用来存储value值
3. matrix是图的存储，其中存储的元素意义如下：
	1. =0表示没有边
	2. !=0表示右边
		1. 大于0表示依赖存在，在计算入度的时候算在内,且数值-1是dfv_value的索引
		2. 小于0表示依赖不存在，在计算入度的收不算在内，且-value-1是dfv_value的索引

---

## 记录：7-14
这些天一直忙着其它事情，以及现在主要还是在图划分算法这一块（代码写的七七八八，还没有debug。）现在只要图划分算法debug好，能加任务划分出来就好了。下图作为展示，我启用了两个Executor,一个Master。由于Master图划分算法还没有合并进去，所以进行手动划分并发送任务的测试。可以看到都能成功且无误执行。期待算法能跑起来那一刻。\
![多机展示](https://raw.githubusercontent.com/Mr-77-18/dis_dfcpp/main/image/9.png) \

## 记录： 8-25
之前的图的数据结构的设计不够合理，导致代码编写的过于繁杂（也许是因为自己编码能力有限），所以这次重新设计了一种数据结构来表示图，如下图所示：(代码见dfcpp/master1.hpp)
![多机展示](https://raw.githubusercontent.com/Mr-77-18/dis_dfcpp/main/image/11.png)
图中使用3个数据结构points , m_edge , m_graph来表示一张图。
至此以及可以初步划分出dfv_index , value , node_index.(例子见dfcpp/test.cpp)

## 10/11
今天在grpc_dfcpp下面更新了schedule.cc,大部分master的工作都在这里面完成
思路：
```c++
//使用的最简单的方法：
//获取图信息
//filename
//
//Executor地址：std::string ABSL_FLAG(std::string , target , "localhost:50057" , "Server address");
//
//Schedule schedule(filename , Sendclient , std::vector<str::string&>& Executor_address)
//
//schedule.run()
//
//while(1){
//直到任务发布完成
//
//
//发布任务
//
//end
//
//结束
`````

## 10-13 合并图算法完成
图算法在dagP目录下面

master的大部分code在grpc_dfcpp/schedule.cc里面

消息类型在grpc_dfcpp/commu.proto里面

对应的Executor模板在example/main_grpc_threemess2.cpp里面
