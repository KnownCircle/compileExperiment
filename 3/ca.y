%{
#include <stdio.h>
#include <string.h>
int yylex(void);
void yyerror(char *);
%}

%union{
  double d_num;
}
%token ADD SUB MUL DIV CR LP RP
%token <d_num> NUM
%type  <d_num> expression term single

%%
       line_list: line
                | line_list line
                ;
				
	       line : expression CR         {printf("上述表达式的值为: %f\n",$1);}
                | expression YYEOF      {printf("上述表达式的值为: %f\n",$1);}

      expression: term 
                | expression ADD term   {$$=$1+$3;}
                | expression SUB term   {$$=$1-$3;}
                ;

            term: single
				| term MUL single		{$$=$1*$3;}
				| term DIV single		{$$=$1/$3;}
				;
				
		  single: NUM                   {$$=$1;}
                | SUB single            {$$=-$2;}   // 负号
                | LP expression RP      {$$=$2;}    // 括号
				;
%%
void yyerror(char *str){
    fprintf(stderr,"error:%s\n",str);
}

int yywrap(){
    return 1;
}
int main()
{
    yyparse();
}
