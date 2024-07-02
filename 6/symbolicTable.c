// in this program ,read a program from stdin and the output is the symbolic table
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100
/*
类型：
0: void
1: int
2: char
3: function
4: int *
5: char *
6: constString
*/

typedef struct
{
    // 每个函数 arg_type是函数的参数类型， arg_value是形参名称。 最多支持4个参数
    char *name;
    int returnType;
    int arg0_type;
    char *arg0_name;
    int arg1_type;
    char *arg1_name;
    int arg2_type;
    char *arg2_name;
    int arg3_type;
    char *arg3_name;
} function;

char *type[] = {"void", "int", "char", "function", "int *", "char *", "constString"};

struct SymbolEntry
{
    char *name;
    int type;
    int val; // 对于int与char是值， 对于int arrary, char arrary, constStr是长度
    function *fun;
    char *constString;
    function *level; // 0为全局变量，function为所在的函数
    struct SymbolEntry *next;
};

function globalVariable;

struct SymbolEntry *symbolTable[TABLE_SIZE];
int constStringCount = 0;

void initSymbolTable()
{
    globalVariable.name = "globalVariable";
    globalVariable.returnType = 0;
    globalVariable.arg0_type = 0;
    globalVariable.arg0_name = NULL;
    globalVariable.arg1_type = 0;
    globalVariable.arg1_name = NULL;
    globalVariable.arg2_type = 0;
    globalVariable.arg2_name = NULL;
    globalVariable.arg3_type = 0;
    globalVariable.arg3_name = NULL;

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        symbolTable[i] = NULL;
    }
}

int hashFunction(char *str)
{
    unsigned int hash = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        hash = (hash << 5) - hash + str[i];
        hash &= 0x7FFFFFFF; // 保持hash值非负
    }
    return hash % TABLE_SIZE;
}

void insertInt(char *name, char value, function *level)
{
    int index = hashFunction(name);
    struct SymbolEntry *entry = (struct SymbolEntry *)malloc(sizeof(struct SymbolEntry));
    entry->name = strdup(name);
    entry->type = 1;
    entry->next = NULL;
    entry->val = value;
    entry->fun = NULL;
    entry->level = level;
    entry->constString = NULL;
    if (symbolTable[index] == NULL)
    {
        symbolTable[index] = entry;
    }
    else
    {
        struct SymbolEntry *temp = symbolTable[index];
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = entry;
    }
}

void insertChar(char *name, char value, function *level)
{
    int index = hashFunction(name);
    struct SymbolEntry *entry = (struct SymbolEntry *)malloc(sizeof(struct SymbolEntry));
    entry->name = strdup(name);
    entry->type = 2;
    entry->next = NULL;
    entry->val = (int)value;
    entry->fun = NULL;
    entry->level = level;
    entry->constString = NULL;
    if (symbolTable[index] == NULL)
    {
        symbolTable[index] = entry;
    }
    else
    {
        struct SymbolEntry *temp = symbolTable[index];
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = entry;
    }
}

void insertFunction(char *name, function *level, int returnType, int arg0_type, char *arg0_name, int arg1_type, char *arg1_name, int arg2_type, char *arg2_name, int arg3_type, char *arg3_name)
{
    int index = hashFunction(name);
    struct SymbolEntry *entry = (struct SymbolEntry *)malloc(sizeof(struct SymbolEntry));
    entry->name = strdup(name);
    entry->type = 3;
    entry->next = NULL;
    entry->val = 0;
    entry->level = level;
    entry->fun = malloc(sizeof(function));
    entry->fun->name = strdup(name);
    entry->fun->returnType = returnType;
    entry->fun->arg0_type = arg0_type;
    entry->fun->arg0_name = strdup(arg0_name);
    entry->fun->arg1_type = arg1_type;
    entry->fun->arg1_name = strdup(arg1_name);
    entry->fun->arg2_type = arg2_type;
    entry->fun->arg2_name = strdup(arg2_name);
    entry->fun->arg3_type = arg3_type;
    entry->fun->arg3_name = strdup(arg3_name);
    entry->constString = NULL;
    if (symbolTable[index] == NULL)
    {
        symbolTable[index] = entry;
    }
    else
    {
        struct SymbolEntry *temp = symbolTable[index];
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = entry;
    }
}

void insertIntArray(char *name, int length, function *level)
{
    int index = hashFunction(name);
    struct SymbolEntry *entry = (struct SymbolEntry *)malloc(sizeof(struct SymbolEntry));
    entry->name = strdup(name);
    entry->type = 4;
    entry->next = NULL;
    entry->val = length;
    entry->fun = NULL;
    entry->level = level;
    entry->constString = NULL;
    if (symbolTable[index] == NULL)
    {
        symbolTable[index] = entry;
    }
    else
    {
        struct SymbolEntry *temp = symbolTable[index];
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = entry;
    }
}

void insertCharArray(char *name, int length, function *level)
{
    int index = hashFunction(name);
    struct SymbolEntry *entry = (struct SymbolEntry *)malloc(sizeof(struct SymbolEntry));
    entry->name = strdup(name);
    entry->type = 5;
    entry->next = NULL;
    entry->val = length;
    entry->fun = NULL;
    entry->level = level;
    entry->constString = NULL;
    if (symbolTable[index] == NULL)
    {
        symbolTable[index] = entry;
    }
    else
    {
        struct SymbolEntry *temp = symbolTable[index];
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = entry;
    }
}

void insertConstString(char *str)
{
    int length = strlen(str);
    char *strName = (char *)malloc(sizeof(char) * 20);
    sprintf(strName, "constString%d", constStringCount);
    constStringCount++;
    int index = hashFunction(strName);
    struct SymbolEntry *entry = (struct SymbolEntry *)malloc(sizeof(struct SymbolEntry));
    entry->name = strdup(strName);
    entry->type = 6;
    entry->next = NULL;
    entry->val = length;
    entry->fun = NULL;
    entry->level = &globalVariable;
    entry->constString = strdup(str);
    if (symbolTable[index] == NULL)
    {
        symbolTable[index] = entry;
    }
    else
    {
        struct SymbolEntry *temp = symbolTable[index];
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = entry;
    }
}

struct SymbolEntry *findSymbol(char *name)
{
    int index = hashFunction(name);
    struct SymbolEntry *entry = symbolTable[index];
    while (entry != NULL)
    {
        if (strcmp(entry->name, name) == 0)
        {
            return entry;
        }
        entry = entry->next; // 假设使用链表解决冲突
    }
    return NULL;
}

struct SymbolEntry *findSymbolByConstString(char *str)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        struct SymbolEntry *entry = symbolTable[i];
        while (entry != NULL)
        {
            if (entry->constString != NULL && strcmp(entry->constString, str) == 0)
            {
                return entry;
            }
            entry = entry->next;
        }
    }
    return NULL;
}

void printSymbolTable()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        struct SymbolEntry *entry = symbolTable[i];
        // printf("out of while:  %p\n", entry);
        while (entry != NULL)
        {
            // printf("in while:  %p\n", entry);
            printf("name:\t%s\n", entry->name);
            if (entry->type == 1)
            {
                printf("\ttype: int\n\tval: %d\n\tlevel: %s\n", entry->val, entry->level->name);
            }
            else if (entry->type == 2)
            {
                // printf("%p\n", entry->level);
                printf("\ttype: char\n\tval: %c\n\tlevel: %s\n", (char)(entry->val), entry->level->name);
            }
            else if (entry->type == 3)
            {
                printf("\ttype: function\n");
                printf("\tlevel: %s\n", entry->level->name);
                printf("\treturnType: %s,\n", type[entry->fun->returnType]);
                printf("\targ0_type: %s, arg0_name: %s,\n", type[entry->fun->arg0_type], entry->fun->arg0_name);
                printf("\targ1_type: %s, arg1_name: %s,\n", type[entry->fun->arg1_type], entry->fun->arg1_name);
                printf("\targ2_type: %s, arg2_name: %s,\n", type[entry->fun->arg2_type], entry->fun->arg2_name);
                printf("\targ3_type: %s, arg3_name: %s \n", type[entry->fun->arg3_type], entry->fun->arg3_name);
            }
            else if (entry->type == 4)
            {
                printf("\ttype: int array\n\tlength: %d\n\tlevel:%s\n", entry->val, entry->level->name);
            }
            else if (entry->type == 5)
            {
                printf("\ttype: char array\n\tlength: %d\n\tlevel:%s\n", entry->val, entry->level->name);
            }
            else if (entry->type == 6)
            {
                printf("\ttype: const string\n\tvalue: %s\n\tlevel:%s\n", entry->constString, entry->level->name);
            }
            else
            {
                printf("Error!\ttpe: %d\n", entry->type);
            }
            // printf("Name: %s , Type: %d , val: %d , constString: %s , nextName: %s\n", entry->name, entry->type, entry->val,entry->constString, entry->next->name);
            // if(entry->type==3){
            //     printf("function %s \nreturnType: %d, arg0_type: %d, arg0_name: %s, arg1_type: %d, arg1_name: %s, arg2_type: %d, arg2_name: %s, arg3_type: %d, arg3_name: %s\n", entry->fun->name, entry->fun->returnType, entry->fun->arg0_type, entry->fun->arg0_name, entry->fun->arg1_type, entry->fun->arg1_name, entry->fun->arg2_type, entry->fun->arg2_name, entry->fun->arg3_type, entry->fun->arg3_name);
            // }
            entry = entry->next;
        }
    }
}

void readData()
{
    char *str = (char *)malloc(sizeof(char) * 100);
    while (scanf("%s", str) != EOF)
    {
        if (strcmp(str, "int") == 0)
        {
            char name[20];
            scanf("%s", name);
            int value;
            scanf("%d", &value);
            char funName[20];
            scanf("%s", funName);
            function *level;
            if (strcmp(funName, "0") == 0)
            {
                level = &globalVariable;
            }
            else
            {
                struct SymbolEntry *temp = findSymbol(funName);
                if (!temp)
                {
                    printf("Error: function %s not found\n", funName);
                    level = &globalVariable;
                    continue;
                }
                level = findSymbol(funName)->fun;
            }
            struct SymbolEntry *temp = findSymbol(name);
            if (temp && temp->type == 1 && temp->level == level)
            {
                printf("Error: variable %s already exists\n", name);
                continue;
            }
            insertInt(name, value, level);
        }
        else if (strcmp(str, "char") == 0)
        {
            char name[20];
            scanf("%s", name);
            char value;
            while ((value = getchar()) == ' ')
            {
            }
            char funName[20];
            scanf("%s", funName);
            function *level;
            if (strcmp(funName, "0") == 0)
            {
                level = &globalVariable;
            }
            else
            {
                struct SymbolEntry *temp = findSymbol(funName);
                if (!temp)
                {
                    printf("Error: function %s not found\n", funName);
                    level = &globalVariable;
                    continue;
                }
                level = findSymbol(funName)->fun;
            }
            struct SymbolEntry *temp = findSymbol(name);
            if (temp && temp->type == 2 && temp->level == level)
            {
                printf("Error: variable %s already exists\n", name);
                continue;
            }
            insertChar(name, value, level);
        }
        else if (strcmp(str, "function") == 0)
        {
            char name[20];
            scanf("%s", name);
            char funName[20];
            scanf("%s", funName);
            function *level;
            if (strcmp(funName, "0") == 0)
            {
                level = &globalVariable;
            }
            else
            {
                struct SymbolEntry *temp = findSymbol(funName);
                if (!temp)
                {
                    printf("Error: function %s not found\n", funName);
                    level = &globalVariable;
                    continue;
                }
                level = findSymbol(funName)->fun;
            }
            int returnType;
            scanf("%d", &returnType);
            int arg0_type;
            scanf("%d", &arg0_type);
            char arg0_name[20];
            scanf("%s", arg0_name);
            int arg1_type;
            scanf("%d", &arg1_type);
            char arg1_name[20];
            scanf("%s", arg1_name);
            int arg2_type;
            scanf("%d", &arg2_type);
            char arg2_name[20];
            scanf("%s", arg2_name);
            int arg3_type;
            scanf("%d", &arg3_type);
            char arg3_name[20];
            scanf("%s", arg3_name);
            struct SymbolEntry *temp = findSymbol(name);
            if (temp && temp->type == 3 && temp->level == level)
            {
                printf("Error: variable %s already exists\n", name);
                continue;
            }
            insertFunction(name, level, returnType, arg0_type, arg0_name, arg1_type, arg1_name, arg2_type, arg2_name, arg3_type, arg3_name);
        }
        else if (strcmp(str, "intArray") == 0)
        {
            char name[20];
            scanf("%s", name);
            int length;
            scanf("%d", &length);
            char funName[20];
            scanf("%s", funName);
            function *level;
            if (strcmp(funName, "0") == 0)
            {
                level = &globalVariable;
            }
            else
            {
                struct SymbolEntry *temp = findSymbol(funName);
                if (!temp)
                {
                    printf("Error: function %s not found\n", funName);
                    level = &globalVariable;
                    continue;
                }
                level = findSymbol(funName)->fun;
            }
            struct SymbolEntry *temp = findSymbol(name);
            if (temp && temp->type == 4 && temp->level == level)
            {
                printf("Error: variable %s already exists\n", name);
                continue;
            }
            insertIntArray(name, length, level);
        }
        else if (strcmp(str, "charArray") == 0)
        {
            char name[20];
            scanf("%s", name);
            int length;
            scanf("%d", &length);
            char funName[20];
            scanf("%s", funName);
            function *level;
            if (strcmp(funName, "0") == 0)
            {
                level = &globalVariable;
            }
            else
            {
                struct SymbolEntry *temp = findSymbol(funName);
                if (!temp)
                {
                    printf("Warning: function %s not found!! Used globalVariable instead.\n", funName);
                    level = &globalVariable;
                    continue;
                }
                level = findSymbol(funName)->fun;
            }
            struct SymbolEntry *temp = findSymbol(name);
            if (temp && temp->type == 5 && temp->level == level)
            {
                printf("Error: variable %s already exists\n", name);
                continue;
            }
            insertCharArray(name, length, level);
        }
        else if (strcmp(str, "constString") == 0)
        {
            char str[200];
            scanf("%s", str);
            int flag = 1;
            for (int i = 0; i < TABLE_SIZE; i++)
            {
                struct SymbolEntry *entry = symbolTable[i];
                while (entry != NULL)
                {
                    if (entry->constString != NULL && strcmp(entry->constString, str) == 0)
                    {
                        printf("Info: constString %s already exists\n", str);
                        flag = 0;
                        break;
                    }
                    entry = entry->next;
                }
            }
            if (flag)
            {
                insertConstString(str);
            }
        }
        else if(strcmp("//",str)==0){
            char c;
            while((c=getchar())!='\n'){
                continue;
            }
        }
        else
        {
            fprintf(stderr, "Error: %s\n", str);
            exit(1);
        }
    }
}

int main()
{
    initSymbolTable();
    readData();
    // printf("已经读取所有数据\n");
    printSymbolTable();
}
