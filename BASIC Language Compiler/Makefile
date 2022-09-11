CXX = g++
CPPFLAGS = -Wall -g


interpreter: Interpreter.o LetStatement.o PrintStatement.o ProgramState.o EndStatement.o PrintallStatement.o AddStatement.o SubStatement.o MultStatement.o DivStatement.o GotoStatement.o GosubStatement.o ReturnStatement.o IfStatement.o
	$(CXX) $(CPPFLAGS) $^ -o $@

LetStatement.o: LetStatement.cpp LetStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

PrintStatement.o: PrintStatement.cpp PrintStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

ProgramState.o: ProgramState.cpp ProgramState.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

EndStatement.o: EndStatement.cpp EndStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

PrintallStatement.o: PrintallStatement.cpp PrintallStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

AddStatement.o: AddStatement.cpp AddStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

SubStatement.o: SubStatement.cpp SubStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

MultStatement.o: MultStatement.cpp MultStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

DivStatement.o: DivStatement.cpp DivStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

GotoStatement.o: GotoStatement.cpp GotoStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

GosubStatement.o: GosubStatement.cpp GosubStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

ReturnStatement.o: ReturnStatement.cpp ReturnStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

IfStatement.o: IfStatement.cpp IfStatement.h
	$(CXX) $(CPPFLAGS) -c $< -o $@


clean:
	rm *.o