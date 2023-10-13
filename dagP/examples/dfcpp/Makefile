headerFile = ../../src/dfcpp_dagP_port
dagPLibrary = ../../lib/libdagp.a
useapi: useapi.cpp $(headerFile) $(dagPLibrary)
	g++ -Wall -o useapi useapi.cpp -I $(headerFile) $(dagPLibrary) -lm
.PHONY: clean run
run:
	./useapi
clean:
	rm -f useapi
