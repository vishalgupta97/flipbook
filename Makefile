CC=g++
CFLAGS = --std=c++11 -I/home/vishalgupta/include/ -I/usr/include/python3.8 -I/home/vishalgupta/.local/lib/python3.8/site-packages/ -I/home/vishalgupta/.local/lib/python3.8/site-packages/numpy/core/include/ -lpython3.8
NAME=flipbook

.phony: all clean lexer parser

all: $(NAME)

flipbook: lexer parser
	g++ $(NAME).cpp $(NAME).c $(NAME).tab.c -o $(NAME) $(CFLAGS)
lexer: $(NAME).l
	flex --header-file=$(NAME).h --outfile=$(NAME).c $(NAME).l

parser: $(NAME.y)
	bison -d --output=$(NAME).tab.c $(NAME).y

clean:
	rm -f $(NAME).h $(NAME).c $(NAME).tab.h $(NAME).tab.c $(NAME)
