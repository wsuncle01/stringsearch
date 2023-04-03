#pragma once
#ifndef STRINGSEARCH
#define STRINGSEARCH
int BF(const char* s, const char* m);//BFÀ„∑®

int KMP(const char* s, const char* m);//KMPÀ„∑®
void cal_next(const char* str, int* next, int len);

int BM(const char* str, const char* pattern);//BMÀ„∑®
void generateGS(const char* str, int* suffix, bool* prefix);
void generateBC(const char* str, int* bc);
int getGsMove(int* suffix, bool* prefix, int index, int size);


#endif // !STRINGSEARCH
