all:
	g++ -I src/include -L src/lib -o main *.cpp *.hpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image