.PHONY: all
all: clean stars debug

.PHONY: stars
stars:
	gcc -Wall bmp.c stars.c -o stars -lm

.PHONY: debug
debug:
	gcc -Wall -g bmp.c stars.c -o stars -lm

.PHONY: clean
clean:
	rm -rf stars
