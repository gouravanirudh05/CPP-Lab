# Variables
CXX = g++
CXXFLAGS = -std=c++11
TARGET = code
SRC = latestcode.cpp
INPUTS = 1.in 2.in 3.in 4.in 5.in 6.in
OUTPUTS = output_1.txt output_2.txt output_3.txt output_4.txt output_5.txt output_6.txt
EXPECTED_OUTPUTS = 1.ans 2.ans 3.ans 4.ans 5.ans 6.ans

# Default target
all: $(TARGET)

# Compilation rule
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Run the program with multiple inputs and generate outputs
run: $(TARGET)
	./$(TARGET) < 1.in > output_1.txt
	./$(TARGET) < 2.in > output_2.txt
	./$(TARGET) < 3.in > output_3.txt
	./$(TARGET) < 4.in > output_4.txt
	./$(TARGET) < 5.in > output_5.txt
	./$(TARGET) < 6.in > output_6.txt

# Compare the generated outputs with the expected answers (1.ans, 2.ans, ...)
compare: run
	diff -q output_1.txt 1.ans
	diff -q output_2.txt 2.ans
	diff -q output_3.txt 3.ans
	diff -q output_4.txt 4.ans
	diff -q output_5.txt 5.ans
	diff -q output_6.txt 6.ans

# Clean up generated files
clean:
	rm -f $(TARGET) $(OUTPUTS)
