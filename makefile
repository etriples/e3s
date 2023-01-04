CC=g++
SRC=$(shell ls ./src)
HDR=$(SRC:.cpp=.hpp)
OBJ=$(SRC:.cpp=.o)
OUT=e3s.out
OBJ_DEP=$(addprefix  ./obj/, ${OBJ})
BUILD_DIR=./build
FLAGS=-Wall -pthread  -std=c++17 
LIB=-lpng

e3s: ${OBJ_DEP}
	@${CC} ${FLAGS} ${OBJ_DEP} ${LIB} -o ./${BUILD_DIR}/${OUT}

obj/%.o: src/%.cpp include/%.hpp
	${CC} -c $< -o $@

run:
	@cd ${BUILD_DIR}; ./${OUT}


clean:
	@rm -r ./obj/*
	@rm ./build/${OUT}