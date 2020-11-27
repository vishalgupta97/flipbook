%{
#include "flipbook.tab.h"
%}
%option reentrant
%option bison-bridge
name_exp [a-zA-Z][a-zA-Z0-9]*
number [0-9]+
%%
base return base_k;
still return still_k;
line return line_k;
circle return circle_k;
type return type_k;
height return height_k;
weight return weight_k;
frame_rate return frame_rate_k;
total_frames return totalframes_k;
iamge_name return image_name_k;
frame_start return frame_start_k;
frame_end return frame_end_k;
start_pos return start_pos_k;
end_pos return end_pos_k;
center return center_k;
radius return radius_k;
"{"|"}"|";" return yytext[0];
{name_exp} {yylval->s=new std::string(yytext,yyleng); return name;}
{number} {yylval->x=stoi(yytext); return number;}
"\n" return 0;
[ \t] ;
%%
