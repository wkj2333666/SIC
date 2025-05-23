OBJDIR = obj
BINDIR = bin

./bin/SIC: ./obj/main.o ./obj/Token.o ./obj/Tokenizer.o ./obj/Calculator.o ./obj/Interpreter.o ./obj/Line.o src/Exception.h | $(BINDIR)
	g++ $^ -o $@ -std=c++17

.PHONY: $(OBJDIR)
.PHONY: $(BINDIR)

$(OBJDIR):
	mkdir -p $@

$(BINDIR):
	mkdir -p $@

./bin/main: ./obj/main.o ./obj/Token.o ./obj/Tokenizer.o ./obj/Calculator.o ./obj/Interpreter.o ./obj/Line.o src/Exception.h | $(BINDIR)
	g++ $^ -o $@ -std=c++17

./obj/main.o: ./src/main.cpp ./src/Exception.h | $(OBJDIR)
	g++ -c $< -o $@ -std=c++17 

./obj/%.o: ./src/%.cpp ./src/%.h | $(OBJDIR)
	g++ -c $< -o $@ -std=c++17 

.PHONY: clean

.PHONY: run

.PHONY: debug

.PHONY: idebug

.PHONY: fresh

clean:
	rm -rf ./obj/*.o ./bin/*

run:
	./bin/main

debug:
	g++ -g ./src/*.cpp -o ./bin/debug -DDEBUG -std=c++17
	./bin/debug

fresh:
	touch ./src/*.cpp
	touch ./src/*.h

idebug: 
	g++ src/*.cpp -o bin/$@ -std=c++17 -DiDEBUG