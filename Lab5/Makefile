# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall
# Target executable
TARGET = zoo
# Source files
SRC = main.cpp
# Object files
OBJ = $(SRC:.cpp=.o)
# Rule to build the target
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)
# Rule to compile the source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
# Rule to run the program with input/output redirection
run: $(TARGET)
	./$(TARGET) < input.txt > output.txt
# Rule to initialize db.txt with an empty file
init-db:
	touch db.txt
# Rule to clean up the build (clears the contents of db.txt)
clean:
	> db.txt
	rm -f $(OBJ) $(TARGET)
