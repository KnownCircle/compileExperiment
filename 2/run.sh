echo "时间："
date
echo input.txt:
cat input.txt
echo "\n--------------------"
gcc lexScanner.c -o lexScanner
echo compile finished. Output:
./lexScanner
cat output.txt
echo lexScanner has finished
echo run \"./lexScanner --help\" for more Usage