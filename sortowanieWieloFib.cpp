#include "sortowanieWieloFib.h"
#include "fileHandler.h"
#include <cstdint>
#include <cstdio>
#include <cstdlib>

SortowanieWieloFib::SortowanieWieloFib(int n, std::string* pliki){
	this->n=n;
	//this->pliki=pliki;
	count = 0;

}

int SortowanieWieloFib::sortuj(){
	
	return 0; //placeholder
}

//
//Funkcje pomocnicze sortowania
//

void SortowanieWieloFib::przygotujDoSortowania(){
	zrodlo1=pojemniczek.opiekunowie[0];
	zrodlo2=pojemniczek.opiekunowie[1];
	zrodlo3=pojemniczek.opiekunowie[2];
	pusty=pojemniczek.opiekunowie[3];
	
	for(int i = 0; i<3; i++){
		pojemniczek.opiekunowie[i]->setWielkoscBloku(1);
		pojemniczek.opiekunowie[i]->setDlugoscPliku(FibTab[i].back());
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
	sortowaniePrzezScalanie(zrodlo1, zrodlo2, zrodlo1);
}

void SortowanieWieloFib::sortujPrzezScalanieFaza2(){
	zrodlo3->resetuj();
	pusty->resetuj();
	sortowaniePrzezScalanie(zrodlo1, zrodlo3, pusty);
}

void SortowanieWieloFib::sortowaniePrzezScalanie(FileHandler* zrodlo1, FileHandler* zrodlo2, FileHandler* cel){
	int petla=zrodlo1->getDlugoscPliku()/zrodlo1->getWielkoscBloku();
	for(int i = 0; i < petla; i++){
		sortowaniePrzezScalanieBlok(zrodlo1, zrodlo2, cel);
	}
}

void SortowanieWieloFib::sortowaniePrzezScalanieBlok(FileHandler* zrodlo1, FileHandler* zrodlo2, FileHandler* cel){
	int i=0;
	int j=0;
	int a, b;
	zrodlo1->strumien >> a;
	zrodlo2->strumien >> b;
	while(i<zrodlo1->getWielkoscBloku()&&j<zrodlo2->getWielkoscBloku()){
		if(le(a,b)){
			cel->strumien << a << " ";
			i++;
			if(i<zrodlo1->getWielkoscBloku())
				zrodlo1->strumien >> a;
		}
		else{
			cel->strumien << b << " ";
			j++;
			if(j<zrodlo2->getWielkoscBloku())
				zrodlo2->strumien >> b;
		}
	}
	if(i==zrodlo1->getWielkoscBloku()){
		for(j; j<zrodlo2->getWielkoscBloku();j++){
			cel->strumien << b;
			if(j<zrodlo2->getWielkoscBloku())
				zrodlo2->strumien >> b;
		}
	}
	else{
		for(i; i<zrodlo1->getWielkoscBloku(); i++){
			cel->strumien << a;
			if(i<zrodlo1->getWielkoscBloku())
				zrodlo1->strumien >> a;
		}
	}	
}
