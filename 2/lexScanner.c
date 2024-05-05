#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lexScanner.h"
#define TOKENSIZE 64
#define PRINT_TO_FILE 1 // 设为1， 输出到output.txt; 设为0，则输出到stdout
// 使用word文档中对token的定义
char *input;
char token[TOKENSIZE];
char ch;    // 当前字符
int p = 0;  // input下标
enum TK fg; // switch标记 与TK表中的内容一致  注意：ERROR是38，
int num;    // 存放读取到的数字
int fileSize;
FILE *outputFile;

int main(int argc, char **argv)
{
    char *file1;
    char *file2;
    if (argc == 1)
    { // default
        file1 = "input.txt";
        file2 = "output.txt";
    }
    else if (argc == 3)
    {
        file1 = argv[1];
        file2 = argv[2];
    }
    else if(argc ==2 && strcmp(argv[1],"--help")==0){
        printf("Usage:\n %s [<inputFile outputFile>]\ndefault: %s input.txt output.txt\n",argv[0],argv[0]);
        return 0;
    }
    else
    {
        fprintf(stderr, "Arguments Error! argc=%d\nUsage:\n %s [<inputFile outputFile>].\ndefault: %s input.txt output.txt\n", argc,argv[0],argv[0]);
        exit(EXIT_FAILURE);
    }
    initScanner(file1, file2);
}

void initScanner(char *filename1, char *filename2)
{
    readInputFile(filename1);
    if (PRINT_TO_FILE == 1)
    {
        outputFile = fopen(filename2, "w");
        if (outputFile == NULL)
        {
            perror("Error opening outputFile");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        outputFile = stdout;
    }
    while (p < fileSize)
    {
        scanner();
        lexScan();
        output(fg);
    }
    if (PRINT_TO_FILE == 1)
    {
        fclose(outputFile);
    }
}

void scanner()
{

    int n;
    for (n = 0; n < TOKENSIZE; n++)
        token[n] = 0;
    ch = input[p++];
    while (ch == ' ' || ch == '\n' || ch == '\t')
        ch = input[p++];
}

void lexScan()
{
    if ((ch <= 'z' && ch >= 'a') || (ch <= 'Z' && ch >= 'A'))
    {
        isAlpha();
    }
    else if (ch <= '9' && ch >= '0')
    {
        isNumber();
    }
    else
    {
        isOther();
    }
}

void isNumber()
{
    num = 0;
    while ((ch <= '9' && ch >= '0'))
    {
        num = num * 10 + ch - '0';
        ch = input[p++];
    }
    ch = input[--p];
    fg = INTCON;
}

void isAlpha()
{
    int m = 0;
    while ((ch <= 'z' && ch >= 'a') || (ch <= 'Z' && ch >= 'A') || (ch <= '9' && ch >= '0') || ch == '_')
    {
        token[m++] = ch;
        ch = input[p++];
    }
    token[m++] = '\0';
    ch = input[--p];
    fg = IDENFR;
    for (int i = MAINTK; i < 38; i++)
    {
        if (strcmp(token, Index[i]) == 0) // strcmp()比较两个字符串,相等返回0
        {
            fg = i;
            break;
        }
    }
}

void isOther()
{
    switch (ch)
    {
    case 0:
        fg = EndOfFile;
        break;
    case '!':
        token[0] = ch;
        if (input[p] == '=')
        {
            fg = NEQ;
            p++;
            token[1] = '=';
        }
        else
        {
            fg = NOT;
        }
        break;
    case '&':
        token[0] = '&';
        if (input[p] == '&')
        {
            p++;

            token[1] = '&';
            fg = AND;
        }
        else
        {
            fg = ERROR;
        }
        break;
    case '|':
        token[0] = '|';

        if (input[p] == '|')
        {
            p++;
            token[1] = '|';
            fg = OR;
        }
        else
        {
            fg = ERROR;
        }
        break;
    case '+':
        token[0] = ch;
        fg = PLUS;
        break;
    case '-':
        token[0] = ch;
        fg = MINU;
        break;
    case '*':
        token[0] = ch;
        fg = MULT;
        break;
    case '/':
        if (input[p] == '/')
        {
            // anotation
            isAnotation();
        }
        else
        {
            token[0] = ch;
            fg = DIV;
        }
        break;
    case '%':
        token[0] = ch;
        fg = MOD;
        break;
    case '<':
        token[0] = ch;
        if (input[p] == '=')
        {
            p++;
            token[1] = '=';
            fg = LEQ;
        }
        else
        {
            fg = LSS;
        }
        break;
    case '>':
        token[0] = ch;
        if (input[p] == '=')
        {
            p++;
            token[1] = '=';
            fg = GEQ;
        }
        else
        {
            fg = GRE;
        }
        break;
    case '=':
        token[0] = ch;
        if (input[p] == '=')
        {
            p++;
            token[1] = '=';
            fg = EQL;
        }
        else
        {
            fg = ASSIGN;
        }
        break;
    case ';':
        token[0] = ch;
        fg = SEMICN;
        break;
    case ',':
        token[0] = ch;
        fg = COMMA;
        break;
    case '(':
        token[0] = ch;
        fg = LPARENT;
        break;
    case ')':
        token[0] = ch;
        fg = RPARENT;
        break;
    case '[':
        token[0] = ch;
        fg = LBRACK;
        break;
    case ']':
        token[0] = ch;
        fg = RBRACK;
        break;
    case '{':
        token[0] = ch;
        fg = LBRACE;
        break;
    case '}':
        token[0] = ch;
        fg = RBRACE;
        break;
    case '\"':
        ch = input[p++];
        int m = 0;
        while (m < TOKENSIZE && p < fileSize && ch != '\"' && ch != 0 && ch!='\n')
        {
            token[m++] = ch;
            ch = input[p++];
        }
        if (ch == '\"')
        {
            fg = STRCON;
        }
        else
        {
            fg = ERROR;
        }
        // puts(token);
        break;
    default:
        token[0] = ch;
        fg = ERROR;
    }
}

void isAnotation()
{
    char temp = input[++p];
    while (p < fileSize && temp != '\n' && temp != 0)
    {
        temp = input[++p];
    }
    fg = ANOTATION;
}

void output(int n)
{

    if (n == INTCON)
    {
        fprintf(outputFile, "(%s, %d)\n", printTK[n], num);
    }
    else if (n == ANOTATION || n == EndOfFile)
    {
    }
    else
    {
        fprintf(outputFile, "(%s, %s)\n", printTK[n], token);
    }
}

void readInputFile(char *filename)
{
    FILE *file;
    size_t result;

    file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("File opening failed");
        exit(EXIT_FAILURE);
    }

    // 获取文件大小
    fseek(file, 0, SEEK_END); // 移动到文件末尾
    fileSize = ftell(file);   // 获取当前位置，即文件大小
    rewind(file);             // 重置文件位置指针到文件开头

    input = (char *)malloc(fileSize + 1);
    if (input == NULL)
    {
        fclose(file);
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    result = fread(input, 1, fileSize, file); // 读取fileSize个字节
    if (result != fileSize)
    {
        // 如果读取的字节数不等于文件大小，打印错误信息
        fclose(file);
        free(input);
        perror("File reading failed");
        exit(EXIT_FAILURE);
    }
}
