CC=g++
CFLAGS = --std=c++17
NAME=flipbook

.phony: all clean lexer parser

all: $(NAME)

flipbook: lexer parser
	g++ $(CFLAGS) $(NAME).cpp $(NAME).c $(NAME).tab.c -o $(NAME) 
lexer: $(NAME).l
	flex --header-file=$(NAME).h --outfile=$(NAME).c $(NAME).l

parser: $(NAME.y)
	bison -d --output=$(NAME).tab.c $(NAME).y

clean:
	rm -f $(NAME).h $(NAME).c $(NAME).tab.h $(NAME).tab.c $(NAME)
