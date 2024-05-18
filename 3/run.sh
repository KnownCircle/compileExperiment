echo 开始bison
bison --yacc -dv ca.y
echo 开始flex
flex ca.l
echo 开始编译
gcc -o ca y.tab.c lex.yy.c
echo 编译完成，开始运行
echo 当前时间：
date
echo 输入的内容：
cat input.txt
echo 
echo 输出的内容为：
./ca < input.txt