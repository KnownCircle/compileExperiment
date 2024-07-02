echo 编译实验6
echo 现在的时间：
date
echo 开始编译：
gcc symbolicTable.c -o  symbolicTable.out
echo 运行程序：
echo 输入的内容：
cat input.txt
echo 输出的内容：
./symbolicTable.out < input.txt