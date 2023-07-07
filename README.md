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

## 记录2023 7-7
今天完成了通信信息部分,可以看commu.proto文件（grpc_dfcpp/commu.proto)的第二版request部分,关键部分如下。
```protobuf
message threemess{
repeated int32 dfv_index = 1;
repeated int32 value = 2;
repeated int32 task_index = 3;
}

`````

对应的send_client.cc和send_server.cc展示了客户端和服务端传输信息的案例。\
由于DFV<T>是一个模板类，所以最终版本的消息传递也应该支持传递不同的数据类型，这里可以用::google:protobuf::Any这个数据类型去实现，但有一点需要注意，就是只能泛化proto中定义的类型，可以参考grpc_dfcpp/any_proto/目录下的测试.\

到此做一个总结：如图所示，红框内是执行体，它只需要三个元素**(三个元素就可以描述一个任务)** ：
1. vector<int> task_index
2. vector<int> dfv_index
3. vector<T> value
就可以执行。那么主要就看掌控者怎么传这三个元素。要注意的是第三个元素vector<T> value，是泛型的，即红框内是支持value是任意类型。但传输支不支持泛型又是另外一码事。这就要看你grpc的使用了。
![总结](https://raw.githubusercontent.com/Mr-77-18/dis_dfcpp/main/image/4.png) \
由于grpc我也是第一次使用，所有能传输说明，怎么传（代码怎么写）也是要探究的过程。这里阐述一下使用grpc和结合到dfcpp中的过程：
1. 首先在**grpc_dfcpp/** 目录下根据grpc的规则进行代码编写
	1. 定义.proto文件，产生源代码
	2. 编写server.cc和client.cc
2. 测试好之后就可以结合到dfcpp当中了，且非常容易，请看以下步骤。
	1. 在example/目录下根据main_grpc.cpp的模板重新写一个grpc的server,你只需要重写定义的rpc函数就可以了。只需要在example/CMakeLists.txt里面加上这个程序，产后cmake就行，即可产生server可执行程序。然后client可执行程序在第一步骤中已经生成了。

