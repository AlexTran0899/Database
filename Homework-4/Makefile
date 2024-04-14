PROJECT_DIR=.
CFLAGS=-I${PROJECT_DIR}/include/
CC=gcc
CXX=g++ -std=c++11
LDFLAGS=

SRC_DIR=${PROJECT_DIR}/src
OBJ_DIR=${PROJECT_DIR}/objs
BIN_DIR=${PROJECT_DIR}/bin

# Ensure the bin and objs directories exist
$(shell mkdir -p $(OBJ_DIR))
$(shell mkdir -p $(BIN_DIR))

all: run

run: compile
	@./bin/main

compile: main

main: ${OBJ_DIR}/main.o
	@${CXX} ${CFLAGS} $^ ${LDFLAGS} -o ${BIN_DIR}/$@ 

${OBJ_DIR}/%.o: ${SRC_DIR}/%.cpp
	@${CXX} ${CFLAGS} -c $< -o $@ 

clean:
	@rm -rf $(OBJ_DIR)/* $(BIN_DIR)/*
