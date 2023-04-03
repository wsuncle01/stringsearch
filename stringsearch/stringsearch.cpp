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
        // ƥ�����
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

	//������ɫ����
	bool* contextlist = new bool[lenS];
	for (int i = 0; i < lenS; i++) {
		contextlist[i] = FALSE;
	}
	bool* matchstrlist = new bool[lenM];
	for (int i = 0; i < lenS; i++) {
		matchstrlist[i] = FALSE;
	}
	int location = 0;

	//��ͼ
	DrawContext(s, contextlist, FOREGROUND_GREEN);
	DrawMatchstr(m, location, matchstrlist, FOREGROUND_GREEN);

	//���matchstr��contextС���˳��㷨
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
				//��ͼ����ǵ�ǰ��
				matchstrlist[k] = TRUE;
				contextlist[i + k] = TRUE;
				DrawContext(s, contextlist, FOREGROUND_GREEN);
				DrawMatchstr(m, location, matchstrlist, FOREGROUND_GREEN);
				Sleep(1000);

				//��Ҫ�߼�
				k += 1;
			}
			else {
				if (next[k - 1] > 0) {
					if (next[k - 1] != -1) {
						//��ͼ����ǵ�ǰ��
						matchstrlist[k] = TRUE;
						contextlist[i + k] = TRUE;
						DrawContext(s, contextlist, FOREGROUND_RED);
						DrawMatchstr(m, location, matchstrlist, FOREGROUND_RED);
						Sleep(1000);

						//��Ҫ�߼�
						i += next[k - 1] + 1;
						k = next[k - 1];
						break;
					}
				}
				else {
					//��ͼ����ǵ�ǰ��
					matchstrlist[k] = TRUE;
					contextlist[i + k] = TRUE;
					DrawContext(s, contextlist, FOREGROUND_RED);
					DrawMatchstr(m, location, matchstrlist, FOREGROUND_RED);
					Sleep(1000);

					//��Ҫ�߼�
					k = 0;
					i += 1;
					break;
				}
			}
		}
		if (k == lenM) {
			return i;
		}
		//������ɫ����
		for (int p = 0; p < lenS; p++) {
			contextlist[p] = FALSE;
		}
		for (int p = 0; p < lenS; p++) {
			matchstrlist[p] = FALSE;
		}

		//���»�ͼ
		Sleep(2000);
		DrawContext(s, contextlist, FOREGROUND_RED);
		clearMatchstr(m, location);
		Sleep(1000);
	}
	return -2;
}

void cal_next(const char* str, int* next, int len) {
	next[0] = -1;//next[0]��ʼ��Ϊ-1��-1��ʾ��������ͬ�����ǰ׺������׺
	int k = -1;//k��ʼ��Ϊ-1
	for (int q = 1; q <= len - 1; q++)
	{
		while (k > -1 && str[k + 1] != str[q])//�����һ����ͬ����ôk�ͱ��next[k]��ע��next[k]��С��k�ģ�����kȡ�κ�ֵ��
		{
			k = next[k];//��ǰ����
		}
		if (str[k + 1] == str[q])//�����ͬ��k++
		{
			k = k + 1;
		}
		next[q] = k;//����ǰ����k��ֵ��������ͬ�����ǰ׺������׺��������next[q]
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

//2.�ú�׺����Ľ���,suffixΪ��׺�ַ���Ӧǰ���λ�ã�prefix�洢���Ƿ����ƥ���ǰ׺�ִ�
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
		int j = i;//�ӵ�һ���ַ���ʼ������str[j]
		int k = 0;//���һ���ַ��ı仯����Ӧ�����str[n - 1 - k]
		while (j >= 0 && str[j] == str[n - 1 - k])//�����һ���ַ��Աȣ���������ڶ���
		{
			j--;
			k++;
			suffix[k] = j + 1;//���k=1������һ���ַ����ȵĺ�׺��Ӧƥ��λ�õ�ֵ
		}
		if (j == -1)//˵����ǰ׺�ַ���Ӧ
			prefix[k] = true;
	}

}

//3.���غú�׺�ƶ��Ĵ���,indexΪ���ַ�λ��-�������Ǻú�׺��sizeΪstr��С
int getGsMove(int* suffix, bool* prefix, int index, int size)
{
	int len = size - index - 1;//���ַ��ĳ��ȣ���ΪindexΪ���ַ�λ�ã�����Ҫ���1
	if (suffix[len] != -1)//��ǰlen���ȵĺ�׺���ַ���ǰ����ƥ����ַ�
	{
		return index + 1 - suffix[len];//����λ�� = �ú�׺��λ��(index + 1) - �������е���һ�γ���λ��
	}

	//indexΪ���ַ���index+1Ϊ�ú�׺��index+2Ϊ�Ӻú�׺
	for (int i = index + 2; i < size; i++)
	{
		if (prefix[size - i])//��Ϊprefix��1��ʼ
			return i;//�ƶ���ǰλ����ǰ׺λ�ã�acba-��Ӧa�ƶ�3
	}

	return 0;

}




//4.�����ҵ�ƥ���ַ�����ͷ�����򷵻�-1
int BM(const char* str, const char* pattern)
{
	int lenS = strlen(str);
	int lenM = strlen(pattern);
	int* bc=new int[ASIZE];//���ַ�����
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
	//��ͼ
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
			}//�Ӻ���ǰƥ��str��pattern
			matchstrlist[j] = TRUE;
			contextlist[i + j] = TRUE;
			DrawContext(str, contextlist, FOREGROUND_GREEN);
			DrawMatchstr(pattern, location, matchstrlist, FOREGROUND_GREEN);
			Sleep(1000);
		}
		if (j < 0)//ƥ�����
			return i;
		else
		{
			int numBc = j - bc[str[i + j]];//bc�ƶ���λ��
			int numGs = 0;
			if (j < lenM - 1)//���һ���ַ����ǻ��ַ��������жϺ��ַ�
			{
				numGs = getGsMove(suffix, prefix, j, lenM);//Gs�ƶ���λ��
			}
			i += numBc > numGs ? numBc : numGs;
		}
		//������ɫ����
		for (int p = 0; p < lenS; p++) {
			contextlist[p] = FALSE;
		}
		for (int p = 0; p < lenS; p++) {
			matchstrlist[p] = FALSE;
		}

		//���»�ͼ
		Sleep(2000);
		DrawContext(str, contextlist, FOREGROUND_RED);
		clearMatchstr(pattern, location);
		Sleep(1000);
	}
	return -2;
}
