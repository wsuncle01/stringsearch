#pragma once
#ifndef WINCONTROL
#define	WINCONTROL
void MoveCursor(int x, int y);//���ù��λ��
void SetColour(int c);//API�������Ըı����̨��ɫ
char* InputContext();//������Ҫ��ƥ�������
int InputPattern(const char* context, const char* matchstr);//������Ҫƥ���ģʽ
char* InputMatchString();//��������ƥ����ַ���
void DrawContext(const char* context, const bool* list, const int color);//���ڻ���context
void DrawMatchstr(const char* matchstr, const int location, const bool* list, const int color);//���ڻ���Matchstr
void clearMatchstr(const char* matchstr, const int location);//���ƥ��
void HideCursor(bool Visible);
int* getSizeofwindow();//��ȡ��Ļ�ߴ�
#endif // !WINCONTROL
