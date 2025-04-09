.PHONY: all clean run

CXX = g++
CXXFLAGS = -std=c++23 -fmodules-ts
CXXFLAGS+=-Isrc
# debug:
CXXFLAGS+=-g

SRC := sortings/quick.cpp sortings/merge.cpp sortings/heap.cpp sortings/counting.cpp sortings/radix.cpp main.cpp
OBJS=$(patsubst %.cpp,$(OBJ_CATALOG)%.o,$(SRC))

OUT_DIR = bin
OUT_EXECUTABLE = sorts
OBJ_CATALOG = obj/

vpath %.cpp src
vpath %.h src

default: all

all: build

build: $(OBJS)
	${CXX} $^ -o ${OUT_DIR}/${OUT_EXECUTABLE}

cache/%.o: src/%.cpp
	${CXX} ${CXXFLAGS} -o $@ -c $<

test:
	./test.sh

clean:
	rm -f *.txt
	rm -rf build
	rm -rf */*.o
	@-rm -r gcm.cache
