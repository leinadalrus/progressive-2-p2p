SHELL = /bin/bash

cxx_comp = g++

target_exec := app_main

build_dir := ./builddir
include_dir := ./inc

clang_files := $(shell find $(include_dir) -name '*.cpp' -or -name '*.c' -or  -name '*.s')

static_objs := $(clang_files:%=$(build_dir)/%.o)

proj_deps := $(static_objs:.o=.d)

items_dir := $(shell find $(include_dir) -type d)
items_flags := $(addprefix -I,$(items_dir))

cxx_flags := $(items_flags) -MMD -MP # generate makefiles with .d output

# The final build step.
$(build_dir)/$(target_exec): $(static_objs)
	$(cxx_comp) $(static_objs) -o $@ $(LDFLAGS)

# Build step for C++ source
$(build_dir)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(cxx_comp) $(cxx_flags) -c $< -o $@

.PHONY: clean
	clean:
		rm -r $(build_dir)

-include $(proj_deps)

windows_msvc_x86_64:
	copy lib/raygui/src/raygui.h lib/raygui/src/raygui.c
	gcc -o lib/raygui/src/raygui.dll lib/raygui/src/raygui.c -shared -DRAYGUI_IMPLEMENTATION -DBUILD_LIBTYPE_SHARED -static-libgcc -lopengl32 -lgdi32 -lwinmm -Wl,--out-implib,lib/raygui/src/librayguidll.a

linux_gnu_x86_64:
	mv lib/raygui/src/raygui.h lib/raygui/src/raygui.c
	gcc -o lib/raygui/raygui.so lib/raygui/src/raygui.c -shared -fpic -DRAYGUI_IMPLEMENTATION -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
