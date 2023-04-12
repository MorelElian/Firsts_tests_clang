CC=clang
CXX=clang++

EIGENDIR=$(HOME)/eigen-3.4.0/install/

CXXFLAGS=-fjit -I$(EIGENDIR)/include/eigen3
LDFLAGS=-fjit

EXEC=Eigen_test_jit Eigen_test for_test_jit hello_world_jit

all: $(EXEC)

Eigen_test_jit: Eigen_test_jit.o
	$(CXX) -o $@ $^ $(LDFLAGS)

Eigen_test: Eigen_test.o
	$(CXX) -o $@ $^ $(LDFLAGS)

for_test_jit: for_test_jit.o
	$(CXX) -o $@ $^ $(LDFLAGS)

hello_world_jit: hello_world_jit.o
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

clean:
	rm -Rf *.o $(EXEC)

.PHONY: clean
