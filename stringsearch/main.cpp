#include "wincontrol.h"
#include "stringsearch.h"
#include<stdio.h>
#include <stdlib.h>
#include <iostream>
#include <Windows.h> 


int main() {
	while (true) {
		const char* context = InputContext();
		const char* matchstr = InputMatchString();
		system("cls");
		int x = InputPattern(context, matchstr);
		printf("\n");
		if (x >= 0) {
			printf("Find Match String at %d",x);
		}
		else {
			if (x == -1) {
				printf("[Error]Match String is longer than Context!!!!!");
			}
			if (x==-2) {
				printf("Sorry, No Match String Found in the Context.");
			}
		}
		printf("\n");
		system("pause");
		system("cls");
	}
	return 0;
}