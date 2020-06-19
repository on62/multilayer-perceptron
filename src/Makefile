.DELETE_ON_ERROR:

CXX=g++
INCDIR=../include
OBJDIR=obj
CFLAGS=-I$(INCDIR) -O3 -Wall -std=c++17 -g
LIBS=`pkg-config --libs --cflags gtkmm-3.0`
EXEC=executable
SRC=$(wildcard *.cpp)
HEADERS=$(patsubst %,$(INCDIR)/%,$(wildcard *.hpp))
OBJ=$(patsubst %,$(OBJDIR)/%,$(SRC:.cpp=.o))

all: $(EXEC)

$(EXEC): $(OBJ)
	@$(CXX) -o $@ $^ $(CFLAGS) $(LIBS)

$(OBJDIR)/%.o: %.cpp $(HEADERS)
	@$(CXX) -c -o $@ $< $(CFLAGS) $(LIBS)

.PHONY: run clean mrproper

run:
	@./$(EXEC)

clean:
	@rm -f $(OBJDIR)/*.o *~ core $(INCDIR)/*~

mrproper: clean
	@rm -rf $(EXEC)
