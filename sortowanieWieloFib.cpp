#include "sortowanieWieloFib.h"
#include "fileHandler.h"
#include <cstdint>
#include <cstdio>
#include <cstdlib>

SortowanieWieloFib::SortowanieWieloFib(int n, std::string* pliki){
	this->n=n;
	this->pliki=pliki;
	count = 0;

}

int SortowanieWieloFib::sortuj(){
	
	return 0; //placeholder
}

//
//Funkcje pomocnicze sortowania
//

void SortowanieWieloFib::przygotujDoSortowania(){
	zrodlo1=opiekunowie[0];
	zrodlo2=opiekunowie[1];
	zrodlo3=opiekunowie[2];
	pusty=opiekunowie[3];
	
	for(int i = 0; i<3; i++){
		opiekunowie[i]->setWielkoscBloku(1);
		opiekunowie[i]->setDlugoscPliku(FibTab[i].back());
	}
}

void SortowanieWieloFib::zmianaPlikow(){
	temp=pusty;
	pusty=zrodlo1;
	zrodlo1=zrodlo2;
	zrodlo2=zrodlo3;
	zrodlo3=temp;
}

void SortowanieWieloFib::sortujPrzezScalanieFaza1(){
	zrodlo1->resetuj(); //przesuwanie wskaźników zapisu i odczytu na początek
	zrodlo2->resetuj();
	zrodlo1->przesunZapisNaKoniec(); //przygotowanie zapisu scalonego ciągu na końcu najkrótszego pliku
	sortowaniePrzezScalanie();
}

void SortowanieWieloFib::sortujPrzezScalanieFaza2(){
	zrodlo1
}
