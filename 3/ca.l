%{
#include <stdio.h>
#include "y.tab.h"
void yyerror(char *);
%}

%%
(0|[1-9][0-9]*)(\.[0-9]+)?  {sscanf(yytext,"%lf",&yylval.d_num); return NUM;}
"\+"							return ADD;
"\-"							return SUB;
"\*"							return MUL;
"\/"							return DIV;
\n                          return CR;
[ \t]+                     /* ignore whitespace */;
\(                          return LP;
\)                          return RP;
&&                          return AND;
\|\|                        return OR;
!                           return NOT;
.                           {fprintf(stderr,"无法识别的字符: %c:0x%x\n",*yytext,*yytext); exit(EXIT_FAILURE);}
%%
