unknown_unix_gnu_x86_64:
	g++ src/main.cpp -o main -O1 -Wall -std=c++14 -Wno-missing-braces

all: unknown_unix_gnu_x86_64
