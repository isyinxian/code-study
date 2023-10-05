#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include<stdlib.h>
#include <ctype.h>
#include <string.h>
#include<errno.h>

int main() {
    int start = 0; // 开始
    int scan = 0; // 扫描
    char word[10]; //存字符串
    char num[6]; //存数字
    char oper[3]; //存算符
    int numScan = scan + 1;//模拟超前搜索加一位,查算符后一位
    char* str;
    char keywords[][10] = { "int", "main", "while", "for" ,
        "do","return","break","continue"}; // 关键字数组
    
    FILE* filep;
    fopen_s(&filep, ".\\string.txt", "r");//打开文件并读取内容获得字符串及大小
    fseek(filep, 0, SEEK_END);
    long stringSize = ftell(filep);
    rewind(filep); 
    str = (char*)malloc(stringSize);
    size_t read = fread(str,sizeof(char),stringSize,filep);
    str[read] = '\0';
    fclose(filep);   
    
    while (str[scan] != '\0') {
        if (isalpha(str[scan])) { // 字母处理
            start = scan;
            while (isalpha(str[scan])) {
                scan++;
            }
            int wordLen = scan - start;
            memmove(word, &str[start], wordLen);
            word[wordLen] = '\0';
            int find = 0;

            // 判断是否为关键字 单字符和非keyboard直接输出
            if (strlen(word)>2)
            {
                for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
                 if (strcmp(word, keywords[i]) == 0) {
                    printf("{1,\"%s\"}\n", keywords[i]); 
                    find=0;
                    break;
                 }
                 else
                 {
                    find=1;
                 }
                }
            }
            else
            {
                printf("{2,\"%s\"}\n", word);
            }
            if (find=='1')
            {
                printf("{2,\"%s\"}\n", word);
            }            
        }  
        else if (isdigit(str[scan])) { // 数字处理
            start = scan;
            while (isdigit(str[scan])) {
                scan++;
            }
            int numLen = scan - start;
            memmove(num, &str[start], numLen);
            num[numLen] = '\0';
            printf("{3,\"%s\"}\n", num);
        }
        else if (str[scan] == '+' || str[scan] == '-'|| str[scan] == '*'
            || str[scan] == '<' || str[scan] == '>'
            || str[scan] == '/' || str[scan] == '=' || str[scan] == ':'
            ) { // 运算符处理 
            start = scan;   
            if (str[numScan]=='*'|| str[numScan] == '=')
            {
                scan=scan+2;
                int operLen = scan-start;
                memmove(oper, &str[start], operLen);
                oper[operLen] = '\0';
                printf("{4,\"%s\"}\n", oper);               
            } 
            else
            {
                printf("{4,\"%c\"}\n", str[scan]);
                scan++;
            }            
        }
        else if (str[scan] == ','|| str[scan] == ';'||str[scan] == '{'||
            str[scan] == '}' || str[scan] == '(' || str[scan] == ')') 
        { // 界符处理
            printf("{5,\"%c\"}\n", str[scan]);
            scan++;
        }
        else if (isspace(str[scan]))
            {
              scan++;
              continue;
            }       
    }
    free(str);
    return 0;
}
