%{
#include <stdio.h>
#include <string.h>
int yylex(void);
void yyerror(char *);
%}

%union{
  double d_num;
}
%token ADD SUB MUL DIV CR LP RP AND OR
%token <d_num> NUM
%type  <d_num> expression term single logic

%%
       line_list: line
                | line_list line
                ;
				
	       line : logic CR         {printf("上述表达式的值为: %f\n",$1);}
                | logic YYEOF      {printf("上述表达式的值为: %f\n",$1);}
                ;

           logic:expression
                | expression AND expression {$$=($1 && $3);}
                | expression OR expression {$$=($1 || $3);}
                ;

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
                | ADD single            {$$=$2;}
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
