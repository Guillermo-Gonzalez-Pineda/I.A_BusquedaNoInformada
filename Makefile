CXX = g++
CXXFLAGS = -g -w
NAMEGLAGS = -o
MAIN = main
INCLUDE	:= Include
TARGET = Prueba1

make:
	$(CXX) -std=c++17 $(CXXFLAGS) main.cpp -I $(INCLUDE) $(NAMEGLAGS) $(TARGET)

.PHONY: all clean

	$(CXX) $(CXXFLAGS) -c $<

clean :
	rm -f $(TARGET) *.o
	rm -rf *~ basura b i