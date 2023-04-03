#pragma once
#ifndef WINCONTROL
#define	WINCONTROL
void MoveCursor(int x, int y);//设置光标位置
void SetColour(int c);//API函数可以改变控制台颜色
char* InputContext();//输入需要被匹配的文章
int InputPattern(const char* context, const char* matchstr);//输入需要匹配的模式
char* InputMatchString();//输入用于匹配的字符串
void DrawContext(const char* context, const bool* list, const int color);//用于绘制context
void DrawMatchstr(const char* matchstr, const int location, const bool* list, const int color);//用于绘制Matchstr
void clearMatchstr(const char* matchstr, const int location);//清空匹配
void HideCursor(bool Visible);
int* getSizeofwindow();//获取屏幕尺寸
#endif // !WINCONTROL
