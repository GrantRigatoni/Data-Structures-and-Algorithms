CXX = g++
CPPFLAGS = -Wall -g

doublet: doublet.o
	$(CXX) $(CPPFLAGS) $^ -o $@

doublet.o: doublet.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

clean:
	rm *.o