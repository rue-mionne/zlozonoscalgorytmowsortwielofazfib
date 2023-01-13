#include <map>
#include <string>
#include <cstdlib>
#include <cstdio>
#include "functionbase.h"

int dummy(int);
int tempLicznik;
int (*wskfunkcja)(int)= dummy;



//FUNKCJE POMOCNICZE

//Liczniki operacji dominujących
bool gt(int a, int b){
	tempLicznik++;
	return a>b;
}

bool ge(int a, int b){
	tempLicznik++;
	return a<=b;
}

bool lt(int a, int b){
	tempLicznik++;
	return a<b;
}

bool le(int a, int b){
	tempLicznik++;
	return a<=b;
}

bool eq(int a, int b){
	tempLicznik++;
	return a==b;
}

int mult(int a, int b){
	tempLicznik++;
	return a*b;
}

//Funkcja badana

int dummy(int n){
	tempLicznik=0;
	for(int i=n; i>0; --i){
		gt(1, 2);
		lt(1,2);
	}
	return tempLicznik;
}
