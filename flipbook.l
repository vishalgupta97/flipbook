%{
#include "flipbook.tab.h"
%}
%option reentrant
%option bison-bridge
%option noyywrap
name_exp [a-zA-Z]+(".bmp")
number [0-9]+
%%
base return base_k;
still return still_k;
line return line_k;
square return square_k;
type return type_k;
height return height_k;
width return width_k;
frame_rate return frame_rate_k;
total_frames return total_frames_k;
image_name return image_name_k;
frame_start return frame_start_k;
frame_end return frame_end_k;
start_pos return start_pos_k;
end_pos return end_pos_k;
side return side_k;
"{"|"}"|";"|"="|"("|")"|","  return yytext[0];
{name_exp} {yylval->s=new std::string(yytext,yyleng); return name;}
{number} {yylval->x=stoi(yytext); return number;}
[ \t\n] ;
<<EOF>> return 0;
%%
