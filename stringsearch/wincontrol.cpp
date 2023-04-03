#include<stdio.h>
#include<time.h>
#include<Windows.h>
#include "wincontrol.h"
#include "stringsearch.h"
#include<algorithm>
#include <stdlib.h>
#define EMPTY   printf("  ");

void MoveCursor(int x, int y)
{
    COORD pos = { x ,y };
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);//获得 标准输出的句柄   
    SetConsoleCursorPosition(output, pos); //设置控制台光标位置
}

void SetColour(int c)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

char* InputContext() {
    printf("Please enter the context:");
    char* context = new char;
    int length=scanf("%s", context);
    return context;
}

int InputPattern(const char* context, const char* matchstr){
    printf("Please enter the algorithm:");
    char* pattern= new char;
    int length = scanf("%s", pattern);
    if (strcmp(pattern,"BF")==0) {
        system("cls");
        HideCursor(TRUE);
        int judgementnode=BF(context, matchstr);
        HideCursor(FALSE);
        return judgementnode;
    }
    if(strcmp(pattern, "KMP") == 0) {
        system("cls");
        HideCursor(TRUE);
        int judgementnode = KMP(context, matchstr);
        HideCursor(FALSE);
        return judgementnode;
    }
    if (strcmp(pattern, "BM") == 0) {
        system("cls");
        HideCursor(TRUE);
        int judgementnode = BM(context, matchstr);
        HideCursor(FALSE);
        return judgementnode;
    }
    return -1;
}

char* InputMatchString() {
    printf("Please enter the matchstring:");
    char* matchstr= new char;
    int length = scanf("%s", matchstr);
    return matchstr;
}

void DrawContext(const char* context, const bool* list, const int color) {
    for (int i = 0; i < strlen(context); i++) {
        MoveCursor(i*2, 1); 
        char temp = context[i];
        SetColour(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        if (list!=NULL) {
            if (list[i]) {
                SetColour(color);
            }
        }
        printf("%c", temp);
        SetColour(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
    
}

void DrawMatchstr(const char* matchstr, const int location, const bool* list,const int color) {
    for (int i = 0; i < strlen(matchstr); i++) {
        MoveCursor((location+i) * 2, 3);
        char temp = matchstr[i];
        SetColour(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        if (list != NULL) {
            if (list[i]) {
                SetColour(color);
            }
        }
        printf("%c", temp);
        SetColour(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
    
}

void clearMatchstr(const char* matchstr, const int location) {
    SetColour(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    for (int i = 0; i < strlen(matchstr); i++) {
        MoveCursor((location + i) * 2, 3);
        EMPTY
    }
}

void HideCursor(bool Visible)
{
    CONSOLE_CURSOR_INFO Cursor;
    Cursor.bVisible = !Visible;
    Cursor.dwSize = sizeof(Cursor);
    HANDLE Hand = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorInfo(Hand, &Cursor);
}

int* getSizeofwindow() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int* size = new int[2];//size[0]=columns,size[1]=rows;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    size[0] = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    size[1] = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    return size;
}