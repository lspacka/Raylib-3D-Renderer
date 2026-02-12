build:
	gcc -o renderer ./src/*.c -lraylib -lwinmm -lgdi32 -Wall -std=c99

run:
	./renderer

clean: 
	rm renderer

chk:
	make build run