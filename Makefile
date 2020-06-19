.DELETE_ON_ERROR:

CXX = g++
CFLAGS = -std=c++20 -O3 -Wall -Wextra -Wpedantic  -Werror\
-Wduplicated-cond -Woverloaded-virtual -Wnon-virtual-dtor
LIBS = `pkg-config --libs --cflags gtkmm-3.0`
SRC_DIR = src
SRC = $(wildcard $(SRC_DIR)/*.cpp)
HEADERS = $(wildcard $(SRC_DIR)/*.hpp)
OBJ_DIR = $(SRC_DIR)/obj
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
EXEC = $(SRC_DIR)/bin/executable

all: $(EXEC)

$(EXEC): $(OBJ)
	@$(CXX) -o $@ $^ $(CFLAGS) $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	@$(CXX) -c -o $@ $< $(CFLAGS) $(LIBS)

.PHONY: run clean cleanall

run:
	@./$(EXEC)

clean:
	@rm $(OBJ_DIR)/*.o

cleanall: clean
	@rm $(EXEC)