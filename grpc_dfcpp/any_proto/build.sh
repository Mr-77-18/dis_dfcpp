#!/bin/bash

proto_file="$1"

# 检查参数是否为空
if [ -z "$proto_file"   ]; then
	echo "未提供.proto文件路径作为参数"                                                                                                                              
	exit 1
fi

 # 执行 protoc 命令，并将参数替换为 $proto_file
 protoc --grpc_out=. --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` "$proto_file"
 protoc --cpp_out=. "$proto_file"
