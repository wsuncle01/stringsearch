#include "stringsearch.h"
#include "wincontrol.h"
#include <string.h>
#include<stdio.h>
#include<time.h>
#include<Windows.h>
#define ASIZE 256


int BF(const char* s="", const char* m="") {
    const int lenS = strlen(s);
    const int lenM = strlen(m);
	bool* contextlist = new bool[lenS];
	for (int i = 0; i < lenS; i++) {
		contextlist[i] = FALSE;
	}
	bool* matchstrlist = new bool[lenM];
	for (int i = 0; i < lenS; i++) {
		matchstrlist[i] = FALSE;
	}
	int location = 0;
	DrawContext(s, contextlist, FOREGROUND_GREEN);
	DrawMatchstr(m, location, matchstrlist, FOREGROUND_GREEN);
    if (!lenS || !lenM || lenS < lenM) {
        return -1;
    }
    for (int pos = 0; pos < lenS - lenM + 1; pos++) {
		location = pos;
        int j = 0;
        while (j < lenM && s[pos + j] == m[j]) {
			matchstrlist[j] = TRUE;
			contextlist[pos + j] = TRUE;
			DrawContext(s, contextlist, FOREGROUND_GREEN);
			DrawMatchstr(m, location, matchstrlist, FOREGROUND_GREEN);
			Sleep(1000);
            j++;
        }
        // 匹配完成
        if (j == lenM) {
            return pos;
        }
		else {
			matchstrlist[j] = TRUE;
			contextlist[pos + j] = TRUE;
			DrawContext(s, contextlist, FOREGROUND_RED);
			DrawMatchstr(m, location, matchstrlist, FOREGROUND_RED);
		}
		for (int i = 0; i < lenS; i++) {
			contextlist[i] = FALSE;
		}
		for (int i = 0; i < lenS; i++) {
			matchstrlist[i] = FALSE;
		}
		Sleep(2000);
		DrawContext(s, contextlist, FOREGROUND_RED);
		clearMatchstr(m, location);
		Sleep(1000);
    }
    return -2;
}

int KMP(const char* s ="",const char* m = "") {
    const int lenS = strlen(s);
    const int lenM = strlen(m);

	//创建颜色数组
	bool* contextlist = new bool[lenS];
	for (int i = 0; i < lenS; i++) {
		contextlist[i] = FALSE;
	}
	bool* matchstrlist = new bool[lenM];
	for (int i = 0; i < lenS; i++) {
		matchstrlist[i] = FALSE;
	}
	int location = 0;

	//绘图
	DrawContext(s, contextlist, FOREGROUND_GREEN);
	DrawMatchstr(m, location, matchstrlist, FOREGROUND_GREEN);

	//如果matchstr比context小，退出算法
	if (!lenS || !lenM || lenS < lenM) {
		return -1;
	}
	int* next = new int[lenM];
	cal_next(m, next, lenM);
	int k = 0;
	int i = 0;
	while (i <= lenS - lenM) {
		location = i;
		if (k > 0) {
			for (int count = 0; count < k; count++) {
				matchstrlist[count] = TRUE;
				contextlist[i + count] = TRUE;
			}
		}
		while (k < lenM) {
			if (m[k] == s[i + k]) {
				//绘图，标记当前点
				matchstrlist[k] = TRUE;
				contextlist[i + k] = TRUE;
				DrawContext(s, contextlist, FOREGROUND_GREEN);
				DrawMatchstr(m, location, matchstrlist, FOREGROUND_GREEN);
				Sleep(1000);

				//主要逻辑
				k += 1;
			}
			else {
				if (next[k - 1] > 0) {
					if (next[k - 1] != -1) {
						//绘图，标记当前点
						matchstrlist[k] = TRUE;
						contextlist[i + k] = TRUE;
						DrawContext(s, contextlist, FOREGROUND_RED);
						DrawMatchstr(m, location, matchstrlist, FOREGROUND_RED);
						Sleep(1000);

						//主要逻辑
						i += next[k - 1] + 1;
						k = next[k - 1];
						break;
					}
				}
				else {
					//绘图，标记当前点
					matchstrlist[k] = TRUE;
					contextlist[i + k] = TRUE;
					DrawContext(s, contextlist, FOREGROUND_RED);
					DrawMatchstr(m, location, matchstrlist, FOREGROUND_RED);
					Sleep(1000);

					//主要逻辑
					k = 0;
					i += 1;
					break;
				}
			}
		}
		if (k == lenM) {
			return i;
		}
		//清理颜色数组
		for (int p = 0; p < lenS; p++) {
			contextlist[p] = FALSE;
		}
		for (int p = 0; p < lenS; p++) {
			matchstrlist[p] = FALSE;
		}

		//重新绘图
		Sleep(2000);
		DrawContext(s, contextlist, FOREGROUND_RED);
		clearMatchstr(m, location);
		Sleep(1000);
	}
	return -2;
}

void cal_next(const char* str, int* next, int len) {
	next[0] = -1;//next[0]初始化为-1，-1表示不存在相同的最大前缀和最大后缀
	int k = -1;//k初始化为-1
	for (int q = 1; q <= len - 1; q++)
	{
		while (k > -1 && str[k + 1] != str[q])//如果下一个不同，那么k就变成next[k]，注意next[k]是小于k的，无论k取任何值。
		{
			k = next[k];//往前回溯
		}
		if (str[k + 1] == str[q])//如果相同，k++
		{
			k = k + 1;
		}
		next[q] = k;//这个是把算的k的值（就是相同的最大前缀和最大后缀长）赋给next[q]
	}
}


void generateBC(const char* str, int* bc)
{
	for (int i = 0; i < ASIZE; i++)
	{
		bc[i] = -1;
	}

	for (int i = 0; i < strlen(str); i++)
	{
		bc[str[i]] = i;
	}
}

//2.好后缀数组的建立,suffix为后缀字符对应前面的位置，prefix存储：是否存在匹配的前缀字串
void generateGS(const char* str, int* suffix, bool* prefix)
{
	int n = strlen(str);
	for (int i = 0; i < n - 1; i++)
	{
		suffix[i] = -1;
		prefix[i] = false;
	}

	for (int i = 0; i < n - 1; i++)
	{
		int j = i;//从第一个字符开始遍历，str[j]
		int k = 0;//最后一个字符的变化，对应下面的str[n - 1 - k]
		while (j >= 0 && str[j] == str[n - 1 - k])//和最后一个字符对比，相等则倒数第二个
		{
			j--;
			k++;
			suffix[k] = j + 1;//如果k=1，则是一个字符长度的后缀对应匹配位置的值
		}
		if (j == -1)//说明有前缀字符对应
			prefix[k] = true;
	}

}

//3.返回好后缀移动的次数,index为坏字符位置-其后面就是好后缀，size为str大小
int getGsMove(int* suffix, bool* prefix, int index, int size)
{
	int len = size - index - 1;//好字符的长度，因为index为坏字符位置，所以要多减1
	if (suffix[len] != -1)//当前len长度的后缀坏字符串前边有匹配的字符
	{
		return index + 1 - suffix[len];//后移位数 = 好后缀的位置(index + 1) - 搜索词中的上一次出现位置
	}

	//index为坏字符，index+1为好后缀，index+2为子好后缀
	for (int i = index + 2; i < size; i++)
	{
		if (prefix[size - i])//因为prefix从1开始
			return i;//移动当前位置离前缀位置，acba-对应a移动3
	}

	return 0;

}




//4.返回找到匹配字符串的头，否则返回-1
int BM(const char* str, const char* pattern)
{
	int lenS = strlen(str);
	int lenM = strlen(pattern);
	int* bc=new int[ASIZE];//坏字符数组
	int* suffix = new int[lenM];
	bool* prefix = new bool[lenM];
	bool* contextlist = new bool[lenS];
	for (int i = 0; i < lenS; i++) {
		contextlist[i] = FALSE;
	}
	bool* matchstrlist = new bool[lenM];
	for (int i = 0; i < lenS; i++) {
		matchstrlist[i] = FALSE;
	}
	int location = 0;
	if (!lenS || !lenM || lenS < lenM) {
		return -1;
	}
	//绘图
	DrawContext(str, contextlist, FOREGROUND_GREEN);
	DrawMatchstr(pattern, location, matchstrlist, FOREGROUND_GREEN);

	generateBC(pattern, bc);
	generateGS(pattern, suffix, prefix);

	int i = 0;
	while (i <= lenS - lenM)
	{
		location = i;
		int j = 0;
		for (j = lenM - 1; j >= 0; j--)
		{
			if (pattern[j] != str[i + j]) {
				matchstrlist[j] = TRUE;
				contextlist[i + j] = TRUE;
				DrawContext(str, contextlist, FOREGROUND_RED);
				DrawMatchstr(pattern, location, matchstrlist, FOREGROUND_RED);
				Sleep(1000);
				break;
			}//从后往前匹配str和pattern
			matchstrlist[j] = TRUE;
			contextlist[i + j] = TRUE;
			DrawContext(str, contextlist, FOREGROUND_GREEN);
			DrawMatchstr(pattern, location, matchstrlist, FOREGROUND_GREEN);
			Sleep(1000);
		}
		if (j < 0)//匹配结束
			return i;
		else
		{
			int numBc = j - bc[str[i + j]];//bc移动的位数
			int numGs = 0;
			if (j < lenM - 1)//最后一个字符就是坏字符，无需判断好字符
			{
				numGs = getGsMove(suffix, prefix, j, lenM);//Gs移动的位数
			}
			i += numBc > numGs ? numBc : numGs;
		}
		//清理颜色数组
		for (int p = 0; p < lenS; p++) {
			contextlist[p] = FALSE;
		}
		for (int p = 0; p < lenS; p++) {
			matchstrlist[p] = FALSE;
		}

		//重新绘图
		Sleep(2000);
		DrawContext(str, contextlist, FOREGROUND_RED);
		clearMatchstr(pattern, location);
		Sleep(1000);
	}
	return -2;
}
