echo 编译实验7
echo 当前时间
date
echo 开始编译
g++ -o ans.out ans.cpp
echo 输入内容
cat input.txt
echo 开始运行
./ans.out < input.txt > output.txt
echo 输出内容
cat output.txt
