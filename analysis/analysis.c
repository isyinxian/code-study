#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include<stdlib.h>
#include <ctype.h>
#include <string.h>
#include<errno.h>

int main() {
    int start = 0; // ��ʼ
    int scan = 0; // ɨ��
    char word[10]; //���ַ���
    char num[6]; //������
    char oper[3]; //�����
    int numScan = scan + 1;//ģ�ⳬǰ������һλ,�������һλ
    char* str;
    char keywords[][10] = { "int", "main", "while", "for" ,
        "do","return","break","continue"}; // �ؼ�������
    
    FILE* filep;
    fopen_s(&filep, ".\\string.txt", "r");//���ļ�����ȡ���ݻ���ַ�������С
    fseek(filep, 0, SEEK_END);
    long stringSize = ftell(filep);
    rewind(filep); 
    str = (char*)malloc(stringSize);
    size_t read = fread(str,sizeof(char),stringSize,filep);
    str[read] = '\0';
    fclose(filep);   
    
    while (str[scan] != '\0') {
        if (isalpha(str[scan])) { // ��ĸ����
            start = scan;
            while (isalpha(str[scan])) {
                scan++;
            }
            int wordLen = scan - start;
            memmove(word, &str[start], wordLen);
            word[wordLen] = '\0';
            int find = 0;

            // �ж��Ƿ�Ϊ�ؼ��� ���ַ��ͷ�keyboardֱ�����
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
        else if (isdigit(str[scan])) { // ���ִ���
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
            ) { // ��������� 
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
        { // �������
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
