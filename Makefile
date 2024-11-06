cpp_files := $(shell find src -name *.cpp)

CPPFLAGS = -Iinclude

.PHONY: run
run: $(obj_files)
	echo $(cpp_files)
	mkdir bin/run -p
	g++ $(cpp_files) -o bin/run/a.out $(CPPFLAGS)

.PHONY: debug
debug: $(obj_files)
	echo $(cpp_files)
	mkdir bin/debug -p
	g++ $(cpp_files) -o bin/debug/a.out $(CPPFLAGS) -g