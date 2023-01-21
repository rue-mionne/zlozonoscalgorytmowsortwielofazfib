#include "licznik.h"
#include <iostream>

//
//konstruktor: inicjacja zmiennych zakresu i ilości powtórzeń
//
Timer::Timer(int min_n, int max_n, int repeats){
	range.count=min_n;
	range.start=min_n; 
	range.end=max_n; 
	repeat.amount=repeats;
	repeat.count=1;
}

//
//funkcja kontrolująca poruszanie się po zakresie
//
int Timer::stepRange(){
	if(range.count>=range.end){//jeśli liczba elementów wyszła poza zakres
		throw new EndOfRangeExc;//natychmiast przerwij iteracje po ilości elementów
	}
	if(range.count<1000){//jeśli liczba elementów 100-1000
		range.count+=100;//iteruj 
	}
	else if(range.count<10000)//jeśli liczba elementów 1000-10000
		range.count+=1000;//iteruj
	return range.count;//zwróć aktualną liczbę elementów
}

//
//funkcja kontrolująca powtórzenia testów dla tej samej liczby elementów
//
int Timer::stepRepeat(){
	if(repeat.count>=repeat.amount){//jeśli numer próby wykracza poza zakres
		repeat.count=1;//zresetuj liczbę prób
		throw new EndOfRepeatCycle;//natychmiast przerwij powtarzanie
	}
	repeat.count++;//zwiększe liczbę prób
	return repeat.count;//zwróć liczbę prób
}
