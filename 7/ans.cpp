/*
author: 李芝塬
email: zhiyuanli0122@outlook.com
参考链接： https://cloud.tencent.com/developer/article/2291382
*/
#include <bits/stdc++.h>
using namespace std;
vector<string> symbols;
int main()
{
    int yes = 1, nextOR = 100, lineNum = 100;
    string a;
    cout << "所有符号和名词之间使用空格分开！" << endl;
    while (1)
    {
        cout << "请输入逻辑运算表达式(输入q退出程序):" << endl;
        getline(cin, a);
        if (a == "q")
            break;
        a += " #";          // 加个终止符号
        stringstream ss(a); // a赋值给ss,
        string s;
        while (ss >> s) // ss 以空格间隔输出字符串 并赋值给s
        {
            if (s == "or" || s == "#")
            {
                if (s == "or")
                    nextOR += 2;
                else
                    nextOR = 0;
                int n = symbols.size();
                for (int i = 0; i < n - 3; i += 3) // 每个逻辑运算一定占3个位置
                {
                    printf("%d(j%s,%s,%s,%d)\n", lineNum, symbols[i + 1].c_str(), symbols[i].c_str(), symbols[i + 2].c_str(), lineNum + 2); // and 真--通过 lineNum 继续
                    lineNum++;
                    printf("%d(j,_,_,%d)\n", lineNum, nextOR);
                    nextOR = lineNum++;
                }
                printf("%d(j%s,%s,%s,%d)\n", lineNum, symbols[n - 2].c_str(), symbols[n - 3].c_str(), symbols[n - 1].c_str(), yes); // or\end情况 真--跳转
                yes = lineNum++;
                printf("%d(j,_,_,%d)\n", lineNum, nextOR);
                lineNum++;
                symbols.clear();
            }
            else if (s == "and")
            {
                // tt中不保存and
                nextOR += 2; // 存一下，去or的情况下处理再一起处理
            }
            else
            {
                symbols.push_back(s);
            }
        }
        yes = 1, nextOR = 100, lineNum = 100; // 重置
        a = "";
    }
}
