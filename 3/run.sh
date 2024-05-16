echo 开始bison
bison --yacc -dv ca.y
echo 开始flex
flex ca.l
echo 开始编译
gcc -o ca y.tab.c lex.yy.c
echo 编译完成，开始运行
./ca < input.txt