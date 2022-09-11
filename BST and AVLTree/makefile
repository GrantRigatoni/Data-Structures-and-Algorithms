cxx = g++ -g -Wall

scheduling: scheduling.o
	$(cxx) $^ -o $@

scheduling.o: scheduling.cpp
	$(cxx) -c $< -o $@

clean:
	rm -f scheduling.o