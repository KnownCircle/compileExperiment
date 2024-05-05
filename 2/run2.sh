echo "时间："
date
echo input2.txt:
cat input2.txt
echo "\n--------------------"
gcc lexScanner.c -o lexScanner
echo compile finished. Output:
./lexScanner input2.txt output2.txt
cat output2.txt
echo lexScanner has finished
echo run \"./lexScanner --help\" for more Usage