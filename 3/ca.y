%{
#include <stdio.h>
#include <string.h>
int yylex(void);
void yyerror(char *);
%}

%union{
  double d_num;
}
%token ADD SUB MUL DIV CR LP RP AND OR NOT
%token <d_num> NUM
%type  <d_num> expression term single logic0 logic2 logic3 logic1

%%
       line_list: line
                | line_list line
                ;
				
	       line : logic3 CR         {printf("上述表达式的值为: %f\n",$1);}
                | logic3 YYEOF      {printf("上述表达式的值为: %f\n",$1);}
                ;

          logic3:logic2
                | logic3 OR logic2{$$=$1||$3;}
                ;

          logic2:logic1
                | logic2 AND logic1 {$$=($1&&$3);}
                ;

          logic1:logic0
                | NOT logic0 {$$=!$2;}
                ;

          logic0:expression
                | LP logic3 RP {$$=$2;}
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
