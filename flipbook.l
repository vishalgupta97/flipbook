%{
#include "flipbook.tab.h"
%}
%option reentrant
%option bison-bridge
%option noyywrap
name_exp [a-zA-Z]+(".bmp")
number [0-9]+
%%
base {printf("%s\n",yytext); return base_k;}
still  {printf("%s\n",yytext); return still_k;}
line  {printf("%s\n",yytext); return line_k;}
square  {printf("%s\n",yytext); return square_k;}
type  {printf("%s\n",yytext); return type_k;}
height  {printf("%s\n",yytext); return height_k;}
width  {printf("%s\n",yytext); return width_k;}
frame_rate  {printf("%s\n",yytext); return frame_rate_k;}
total_frames  {printf("%s\n",yytext); return total_frames_k;}
image_name  {printf("%s\n",yytext); return image_name_k;}
frame_start  {printf("%s\n",yytext); return frame_start_k;}
frame_end  {printf("%s\n",yytext); return frame_end_k;}
start_pos  {printf("%s\n",yytext); return start_pos_k;}
end_pos  {printf("%s\n",yytext); return end_pos_k;}
side  {printf("%s\n",yytext); return side_k;}
"{"|"}"|";"|"="|"("|")"|","  {printf("%s\n",yytext); return yytext[0];}
{name_exp} {yylval->s=new std::string(yytext,yyleng); printf("%s\n",yytext);  return name;}
{number} {yylval->x=stoi(yytext); printf("%s\n",yytext); return number;}
[ \t\n] ;
<<EOF>> return 0;
%%
