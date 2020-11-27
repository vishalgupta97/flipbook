#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<sys/mman.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<iostream>
#include "flipbook.tab.h"
#include "flipbook.h"

using namespace std;

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		return -1;
	}
	
	int fd = open(argv[1], O_RDONLY);
	struct stat sb;
	fstat(fd, &sb);
	char* memblock = (char*)mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);
	
	yyscan_t scanner;
	yylex_init(&scanner);
	yyset_in(fmemopen(memblock, sb.st_size, "r"), scanner);
	vector<FB_stmt*> *list;
	int yacc_err = yyparse(scanner, &list);
	yylex_destroy(scanner);
	if(yacc_err > 0)
	{
		cout << "Parsing Error\n" << endl;
	}
	else
	{
		cout << "Entries: " << list->size() << endl;
		for(auto it: *list)
		{
			cout << "Type: " << it->type << endl;
			if(it->type == 1)
			{
				Base_stmt *ptr = (Base_stmt*)it;
				cout << "PL: " << ptr->properties->size() << endl;
			}
			else if(it->type == 2)
			{
				Still_stmt *ptr = (Still_stmt*)it;
				cout << "PL: " << ptr->properties->size() << endl;
			}

		}
	}	
}
