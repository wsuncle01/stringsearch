#pragma once
#ifndef STRINGSEARCH
#define STRINGSEARCH
int BF(const char* s, const char* m);//BF�㷨

int KMP(const char* s, const char* m);//KMP�㷨
void cal_next(const char* str, int* next, int len);

int BM(const char* str, const char* pattern);//BM�㷨
void generateGS(const char* str, int* suffix, bool* prefix);
void generateBC(const char* str, int* bc);
int getGsMove(int* suffix, bool* prefix, int index, int size);


#endif // !STRINGSEARCH
