#include <map>
#include <string>
#include <cstdlib>
#include <cstdio>
#include "functionbase.h"

/*Dodane funkcje MUSZĄ się znaleźć w mapie, żeby mogły być wykorzystane w programie.*/

//Nie usuwaj tych linijek!
std::map<std::string, int(*)()> baza_funkcji;
int tempLicznik;

//Dodawaj funkcje według wzoru
void inicjujBazeFunkcji(){
//	baza_funkcji.emplace("przykład", nazwafunkcji)
}

/*Jak dodawać funkcje:
 *
 * Sposób 1:
 * Każda funkcja ma osobny plik cpp, który #include zbiorczy nagłówek z nazwami funkcji
 * Zapisz funkcję, następnie zadeklaruj ją w nagłówku, po czym dodaj ją w tym pliku do bazy funkcji (linijka 12) 
 *
 * Sposób 2: 
 * Zadeklaruj funkcję nad funkcją w linijce 12, po czym napisz jej ciało gdziekolwiek poniżej funkcji pomocniczych.*
 * Dodaj ją do bazy funkcji*/

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
