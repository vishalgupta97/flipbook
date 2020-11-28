%{
#include "flipbook.tab.h"
#include "flipbook.h"
%}
%define api.pure
%lex-param {void * scanner}
%parse-param {void * scanner}
%parse-param {vector<FB_stmt*> **stmt1}
%code requires {
#include<stdio.h>
#include "tree.h"
void yyerror(void *scanner, vector<FB_stmt*> **list, const char *s);
/*{
	printf("%s\n", s);
	*list=NULL;
}*/
}
%union
{
	Base_stmt *base_stmt;
	Still_stmt *still_stmt;
	Line_stmt *line_stmt;
	Square_stmt *square_stmt;
	vector<FB_stmt*> *fb_stmt_list;
	vector<FB_stmt*> **fb;
	FB_stmt *fb_stmt;
	vector<Property*> *property_list;
	Property *property;	
	int x;
	string *s;
}

%token <x> base_k still_k line_k square_k type_k height_k width_k frame_rate_k total_frames_k image_name_k frame_start_k frame_end_k start_pos_k end_pos_k side_k 
%token <s> name
%token <x> number 

%left ';'

%type <x> single_val_property double_val_property

%type <fb> fb
%type <fb_stmt_list> fb_stmt_list
%type <fb_stmt> fb_stmt
%type <base_stmt> base_stmt
%type <line_stmt> line_stmt
%type <still_stmt> still_stmt;
%type <square_stmt> square_stmt;
%type <property_list> property_list property_list1;
%type <property> property;

%start fb

%%
fb : fb_stmt_list {*stmt1=$1;}
;

fb_stmt_list : fb_stmt_list ';' fb_stmt {$$ = $1; $$->push_back($3);}
				| fb_stmt {vector<FB_stmt*> *list = new vector<FB_stmt*>(); list->push_back($1); $$=list;}


fb_stmt : still_stmt {$$=$1;}
		| line_stmt {$$=$1;}
		| square_stmt {$$=$1;}
		| base_stmt {$$=$1;}
;

base_stmt : '{' type_k '=' base_k ';' property_list1 '}' { $$=new Base_stmt($6); }
;
still_stmt : '{' type_k '=' still_k ';' property_list1 '}' { $$=new Still_stmt($6); }
;
line_stmt : '{' type_k '=' line_k ';' property_list1 '}' { $$=new Line_stmt($6); }
;
square_stmt : '{' type_k '=' square_k ';' property_list1 '}' { $$=new Square_stmt($6); }
;

property_list1 : property_list { $$ = $1;};
					|	{$$ = NULL;}
property_list : property_list ';' property {$$=$1; $$->push_back($3);}
			| property { vector<Property*> *list = new vector<Property*>(); list->push_back($1); $$= list; }
;

property : single_val_property '=' number {$$ = new Property($1,$3);}
		| image_name_k '=' name {$$ = new Property(IMAGE_NAME_T,$3);}
		| double_val_property '=' '('number','number')' {$$ = new Property($1,$4,$6);} 
;
single_val_property : height_k {$$=HEIGHT_T;} | width_k  {$$=WIDTH_T;} | frame_rate_k  {$$=FRAME_RATE_T;} | total_frames_k {$$=TOTAL_FRAMES_T;}  | frame_start_k  {$$=FRAME_START_T;} | frame_end_k {$$=FRAME_END_T;}  | side_k {$$=SIDE_T;} 
;
double_val_property : start_pos_k  {$$=START_POS_T;} | end_pos_k {$$=END_POS_T;} 
;
%%

void yyerror(void *scanner, vector<FB_stmt*> **list, const char *s)
{
	printf("%s\n", s);
	*list=NULL;
}

