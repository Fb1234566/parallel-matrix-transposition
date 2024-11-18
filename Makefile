implicit_parallelism_cpp_files := $(shell find src -name implicitParallelism.cpp)
implicit_parallelism_obj_files := $(patsubst src/%.cpp, bin/obj/%.o, $(implicit_parallelism_cpp_files))

serial_cpp_files := $(shell find src -name serial.cpp)
serial_obj_files := $(patsubst src/%.cpp, bin/obj/%.o, $(serial_cpp_files))

openmp_cpp_files := $(shell find src -name openmp.cpp)
openmp_obj_files := $(patsubst src/%.cpp, bin/obj/%.o, $(openmp_cpp_files))

utility_cpp_file := $(shell find src -name utility.cpp)
utility_obj_file := $(patsubst src/%.cpp, bin/obj/%.o, $(utility_cpp_file))

CPPFLAGSSR = -Iinclude -fopenmp -std=c++11 # serial compilation flags
CPPFLAGSIM = -Iinclude -O1 -std=c++11 # implicit parallelism cserial_cpp_filesompilation flags


obj_files := $(serial_obj_files) $(implicit_parallelism_obj_files) $(utility_obj_file) $(openmp_obj_files)

$(implicit_parallelism_obj_files): bin/obj/%.o : src/%.cpp
	$(info $(CPPFLAGSIM))
	mkdir -p $(dir $@) && \
	g++ -c $(patsubst bin/obj/%.o, src/%.cpp, $@) -o $@ $(CPPFLAGSIM)

$(serial_obj_files): bin/obj/%.o : src/%.cpp
	$(info $(CPPFLAGSSR))
	mkdir -p $(dir $@) && \
	g++ -c $(patsubst bin/obj/%.o, src/%.cpp, $@) -o $@ $(CPPFLAGSSR)

$(openmp_obj_files): bin/obj/%.o : src/%.cpp
	$(info $(CPPFLAGSSR))
	mkdir -p $(dir $@) && \
	g++ -c $(patsubst bin/obj/%.o, src/%.cpp, $@) -o $@ $(CPPFLAGSSR)

$(utility_obj_files): bin/obj/%.o : src/%.cpp
	$(info $(CPPFLAGSSR))
	mkdir -p $(dir $@) && \
	g++ -c $(patsubst bin/obj/%.o, src/%.cpp, $@) -o $@ $(CPPFLAGSSR)

.PHONY: run
run: $(obj_files)
	g++ src/main.cpp -c -o bin/obj/main.o $(CPPFLAGSSR)
	mkdir bin/run -p && \
	g++ $(obj_files) bin/obj/main.o -o bin/run/a.out -std=c++11 -fopenmp
