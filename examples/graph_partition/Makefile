headerFile = -I ../../graph_partition/dagP/src/common -I ../../graph_partition/dagP/src/recBisection -I ../../graph_partition/dfcpp_dagP_port
dagPLibrary = ../../graph_partition/dagP/lib/libdagp.a -lm
dagPToDfcpp = ../../graph_partition/dfcpp_dagP_port/dfcpp_dagP_port.cpp
useapi: useapi.cpp
	g++ -Wall -o useapi useapi.cpp $(dagPToDfcpp) $(headerFile) $(dagPLibrary)
run:
	./useapi
clean:
	rm -f useapi
