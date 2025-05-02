./bin/main: ./obj/main.o ./obj/Token.o ./obj/Tokenizer.o ./obj/Calculator.o
	g++ $^ -o $@ -std=c++17

./obj/main.o: ./src/main.cpp ./src/Exception.h
	g++ -c $< -o $@ -std=c++17 

./obj/%.o: ./src/%.cpp ./src/%.h
	g++ -c $< -o $@ -std=c++17 

.PHONY: clean

.PHONY: run

.PHONY: debug

.PHONY: fresh

clean:
	rm -rf ./obj/*.o ./bin/main

run:
	./bin/main

debug:
	g++ -g ./src/*.cpp -o ./bin/debug -DDEBUG -std=c++17
	./bin/debug

fresh:
	touch ./src/*.cpp
	touch ./src/*.h