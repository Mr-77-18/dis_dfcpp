headerFile = ../../graph_partition/dagP/src/dfcpp_dagP_port
dagPLibrary = ../../graph_partition/dagP/lib/libdagp.a
useapi: useapi.cpp $(headerFile) $(dagPLibrary)
	g++ -Wall -o useapi useapi.cpp -I $(headerFile) $(dagPLibrary) -lm
.PHONY: clean run
run:
	./useapi
clean:
	rm -f useapi
