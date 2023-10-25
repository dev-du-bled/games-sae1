CXX = g++
CXXFLAGS = -Wall

ifeq ($(shell uname), Darwin)
    CXXFLAGS += -std=c++20
endif

TARGET = main
SRC = main.cpp

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)
	./$(TARGET)
clean:
	rm -f $(TARGET)

.PHONY: clean

