CXX       := g++
CXX_FLAGS := -Wall -Wextra -std=c++11

BIN     := bin
SRC     := src
INCLUDE :=  /usr/include/SFML/include -I include 
LIB     := /usr/include/SFML/lib
LIBRARIES   := -lsfml-graphics -lsfml-window -lsfml-system
EXECUTABLE  := main
DLL	:= mydll.dll


all: $(BIN)/$(EXECUTABLE)

run: clean all
	@echo "🚀 Executing..."
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	@echo "🚧 Building..."
	$(CXX) $(CXX_FLAGS) -I $(INCLUDE) -L $(LIB) $^ -o  $@ $(LIBRARIES) 

clean:
	@echo "🧹 Clearing..."
	-rm $(BIN)/* 
 
 
