%{
#include "flipbook.tab.h"
#include "flipbook.h"
%}
%pure-parser
%lex-param {void * scanner}
%parse-param {void * scanner}
%code requires {
#include<stdio.h>
#include "tree.h"
void yyerror(void *scanner, FB_stmt **stmt1, const char *s);
}
%union
{
}

%token <x> 
%token <s> name
%token <x> number

%start fb

%%
fb : fb_stmt '$$' {*stmt1=$1;}
	| {stmt1=NULL;}
;

fb_stmt : base_stmt {$$=$1;}
		| still_stmt {$$=$1;}
		| line_stmt {$$=$1;}
		| circle_stmt {$$=$1;}
;

base_stmt : '{' type_k '=' base_k ';' property_list '}' | { $$=new Base_stmt($6); }
;
still_stmt : '{' type_k '=' still_k ';' property_list '}' | { $$=new Still_stmt($6); }
/Users/vishalgupta/hasura/temp ;
line_stmt : '{' type_k '=' line_k ';' property_list '}' | { $$=new Line_stmt($6); }
;
circle_stmt : '{' type_k '=' circle_k ';' property_list '}' | { $$=new Circle_stmt($6); }
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
double_val_property : start_pos_k | end_pos_k | center_pos_k
;
 
