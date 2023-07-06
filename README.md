# 改造框架
如图为大体框架
![框架](https://raw.githubusercontent.com/Mr-77-18/dis_dfcpp/main/image/1.png) 
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
