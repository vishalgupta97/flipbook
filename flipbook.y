%{
#include "flipbook.tab.h"
#include "flipbook.h"
#include<stdio.h>
#include "tree.h"
void yyerror(void *scanner, vector<FB_stmt*> *stmt1, const char *s);
%}
%pure-parser
%lex-param {void * scanner}
%parse-param {void * scanner}
%parse-param {vector<FB_stmt*> *stmt1}
%union
{
	Base_stmt *base_stmt;
	Still_stmt *still_stmt;
	Line_stmt *line_stmt;
	Circle_stmt *circle_stmt;
	vector<FB_stmt*> *fb_stmt_list;
	FB_stmt *fb_stmt;
	vector<Property*> *property_list;
	Property *property;	
	int x;
	string s;
}

%token <x> base_k still_k line_k circle_k type_k height_k width_k frame_rate_k total_frames_k image_name_k frame_start_k frame_end_k start_pos_k end_pos_k center_k radius_k 
%token <s> name
%token <x> number 

%type <x> single_val_property double_val_property

%type <fb_stmt_list> fb fb_stmt_list
%type <fb_stmt> fb_stmt
%type <base_stmt> base_stmt
%type <line_stmt> line_stmt
%type <still_stmt> still_stmt;
%type <circle_stmt> circle_stmt;
%type <property_list> property_list;
%type <property> property;

%start fb

%%
fb : fb_stmt_list {*stmt1=$1;}
;

fb_stmt_list : base_stmt ';' {vector<FB_stmt*> *list = new vector<FB_stmt*>(); list->push_back($1); $$=list;}
				| fb_stmt_list fb_stmt ';' {$$ = $1; $$->push_back($2);}

fb_stmt : still_stmt {$$=$1;}
		| line_stmt {$$=$1;}
		| circle_stmt {$$=$1;}
;

base_stmt : '{' type_k '=' base_k ';' property_list '}' { $$=new Base_stmt($6); }
;
still_stmt : '{' type_k '=' still_k ';' property_list '}' { $$=new Still_stmt($6); }
;
line_stmt : '{' type_k '=' line_k ';' property_list '}' { $$=new Line_stmt($6); }
;
circle_stmt : '{' type_k '=' circle_k ';' property_list '}' { $$=new Circle_stmt($6); }
;

property_list : property ';' { vector<Property*> *list = new vector<Property*>(); list->push_back($1); $$= list; }
			| property_list property ';' {$$=$1; $$->push_back($2);}
			| {$$=NULL;}
;

property : single_val_property '=' number {$$ = new Property($1,$3);}
		| double_val_property '=' '('number','number')' {$$ = new Property($1,$4,$6);} 
;
single_val_property : height_k | width_k | frame_rate_k | total_frames_k | image_name_k | frame_start_k | frame_end_k | radius_k
;
double_val_property : start_pos_k | end_pos_k | center_k
;

%%

void yerror(void *scanner, vector<FB_stmt*> *list, const char *s)
{
	print("%s\n", s);
	*list=NULL;
} 
