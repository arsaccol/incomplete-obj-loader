all:
	clang++-12 -std=c++2a main.cpp -g -o app

clean:
	rm app
