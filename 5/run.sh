clear
echo 现在的日期：
date
echo 开始编译
g++ ans.cpp -o b
echo 开始运行
echo 输入的内容：
cat input.txt
echo 输出的内容：
./b < input.txt > output.txt
cat output.txt