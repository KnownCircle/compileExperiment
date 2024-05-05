flex -o flex_output.c flex_input.l
gcc flex_output.c -o a
./a < input.txt > output.txt
cat output.txt