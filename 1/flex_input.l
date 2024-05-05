%{
    #include<stdio.h>
%}

%%
main    printf("MAINTK %s\n",yytext);
const   printf("CONSTTK %s\n",yytext);
int     printf("INTTK %s\n",yytext);
break   printf("BREAKTK %s\n",yytext);
continue     printf("CONTINUETK %s\n",yytext);
if     printf("IFTK %s\n",yytext);
ELSE     printf("ELSETK %s\n",yytext);
!     printf("NOT %s\n",yytext);
&&     printf("AND %s\n",yytext);
\|\|     printf("OR %s\n",yytext);
while     printf("WHILETK %s\n",yytext);
getint     printf("GETINTTK %s\n",yytext);
printf     printf("PRINTFTK %s\n",yytext);
\+     printf("PLUS %s\n",yytext);
\-     printf("MINU %s\n",yytext);
void     printf("VOIDTK %s\n",yytext);
=     printf("ASSIGN %s\n",yytext);
;     printf("SEMICN %s\n",yytext);
,     printf("COMMA %s\n",yytext);
\(    printf("LPARENT %s\n",yytext);
\)     printf("RPAARENT %s\n",yytext);
\[     printf("LBRACK %s\n",yytext);
\]     printf("RBRACK %s\n",yytext);
\{    printf("LBRACE %s\n",yytext);
\}     printf("RBRACE %s\n",yytext);
[a-zA-Z]+[a-zA-Z0-9_]* printf("IDENFR %s\n",yytext);
0|([1-9][0-9]*) printf("INTCON %s\n",yytext);
\".*\"  printf("STRCON %s\n",yytext);
[ \t\n]
\\\\.*
. printf("ERROR!");

%%
int scanner(){
    yylex();
    yywrap();
}
int main(int argc, char **argv)
{
    scanner();
}
int yywrap()
{
	return 1;
}
