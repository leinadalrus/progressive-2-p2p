# progressive-2-p2p
 Chord DHT demo examples in C++14 for a progressive working assignment/test in University.

###### Commands with Makefile to run:
```Makefile
unknown_unix_gnu_x86_64:
	g++ src/main.cpp -o main -O1 -Wall -std=c++14 -Wno-missing-braces -LC:/raylib/raylib/src -lraylib -lopengl32 -lgdi32 -lwinmm

windows_msvc_x86_64:
	copy lib/raygui/src/raygui.h lib/raygui/src/raygui.c
	gcc -o lib/raygui/src/raygui.dll lib/raygui/src/raygui.c -shared -DRAYGUI_IMPLEMENTATION -DBUILD_LIBTYPE_SHARED -static-libgcc -lopengl32 -lgdi32 -lwinmm -Wl,--out-implib,lib/raygui/src/librayguidll.a

linux_gnu_x86_64:
	mv lib/raygui/src/raygui.h lib/raygui/src/raygui.c
	gcc -o lib/raygui/raygui.so lib/raygui/src/raygui.c -shared -fpic -DRAYGUI_IMPLEMENTATION -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
```

_Compile with:_
```Bash
make unknown_unix_gnu_x86_64
```