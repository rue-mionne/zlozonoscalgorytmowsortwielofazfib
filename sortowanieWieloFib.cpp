#include "sortowanieWieloFib.h"
#include "dystrybucja.h"
#include "fileHandler.h"
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ostream>

SortowanieWieloFib::SortowanieWieloFib(int n, std::string* pliki):dystrybucja(n, &pojemniczek){
	std::cout << "\nKonstr sort";
	this->n=n;
	pojemniczek.pliki=pliki;
	count = 0;

}

//TODO: ukoncz start
void SortowanieWieloFib::start(){
	std::cout << "\nstart";
	dystrybucja.dzialaj();	
	sortuj();

}

int SortowanieWieloFib::sortuj(){
	std::cout <<"\nsortuj";
	przygotujDoSortowania();
	sortowaniePrzezScalanie();
	return 0; //placeholder
}

//
//Funkcje pomocnicze sortowania
//

void SortowanieWieloFib::przygotujDoSortowania(){
	std::cout << "\nprzygotuj\n" ;
	zrodlo1=pojemniczek.opiekunowie[0];
	zrodlo2=pojemniczek.opiekunowie[1];
	zrodlo3=pojemniczek.opiekunowie[2];
	pusty=pojemniczek.opiekunowie[3];
	
	for(int i = 0; i<3; i++){
		pojemniczek.opiekunowie[i]->setWielkoscBloku(1);
		pojemniczek.opiekunowie[i]->setDlugoscPliku(FibTab[i].back());
	}
}

void SortowanieWieloFib::zmianaPlikow(){ //konieczne wyznaczenie plikow o najmniejszej i najwiekszej ilosci blokow: kolejnym celem jest zawsze ten o najmniejszej ilosci, ale sam algorytm nie przesuwa sie cyklicznie
	std::cout << "zmiana\n";
	
	temp=pusty;
	int liczbaBlokow[3];
	FileHandler* tempHandlery[3];
	tempHandlery[0]=zrodlo2;
	liczbaBlokow[0]=zrodlo2->getDlugoscPliku()/zrodlo2->getWielkoscBloku();
	tempHandlery[1]=zrodlo3;
	liczbaBlokow[1]=zrodlo3->getDlugoscPliku()/zrodlo3->getWielkoscBloku();
	tempHandlery[2]=temp;
	liczbaBlokow[2]=temp->getDlugoscPliku()/temp->getWielkoscBloku();
	int max=0, min=0, mid=0;
	for(int i=1;i<3;i++){  //wyliczenie pozycji plikow dla 4 plikow WAZNE! dla wiekszej ilosci potrzebny dodatkowy algorytm dla podzialu - w tym przypadku bylby to jednak przyrost formy nad trescia
		if(liczbaBlokow[max]<liczbaBlokow[i]){
			mid=max;
			max=i;
		}
		if(liczbaBlokow[min]>liczbaBlokow[i]){
			mid=min;
			min=i;
		}
		if(max!=i&&min!=i)
			mid=i;
	}
	pusty=zrodlo1;
	zrodlo1=tempHandlery[min];
	zrodlo2=tempHandlery[mid];
	zrodlo3=tempHandlery[max];

}

void SortowanieWieloFib::sortowaniePrzezScalanie(){
	std::cout << "sortmain\n";
	int wielkoscBloku=0;
	while(wielkoscBloku<n){
		sortujPrzezScalanieFaza1();
		sortujPrzezScalanieFaza2();
		zmianaPlikow();

	}
}

void SortowanieWieloFib::sortujPrzezScalanieFaza1(){
	std::cout << "sorfaza1\n";
	
	zrodlo1->przesunZapisNaKoniec(); //przygotowanie zapisu scalonego ciągu na końcu najkrótszego pliku
	sortowaniePrzezScalaniePlik(zrodlo1, zrodlo2, zrodlo1);
	zrodlo1->setWielkoscBloku(zrodlo1->getWielkoscBloku()+zrodlo2->getWielkoscBloku());
	zrodlo1->setDlugoscPliku(zrodlo1->getDlugoscPliku()*2);
	zrodlo1->odswiez();
	zrodlo2->odswiez();
}

void SortowanieWieloFib::sortujPrzezScalanieFaza2(){
	std::cout << "sortfaza2\n";
	pusty->resetuj();//przygotowanie celu pod zapis
	sortowaniePrzezScalaniePlik(zrodlo1, zrodlo3, pusty);
}

void SortowanieWieloFib::sortowaniePrzezScalaniePlik(FileHandler* zrodlo1, FileHandler* zrodlo2, FileHandler* cel){
	std::cout << "sortplik\n";
	int petla=zrodlo1->getDlugoscPliku()/zrodlo1->getWielkoscBloku();
	for(int i = 0; i < petla; i++){
		zrodlo1->strumienIn.clear();
		sortowaniePrzezScalanieBlok(zrodlo1, zrodlo2, cel);
	}
	pusty->resetuj();
	pusty->setWielkoscBloku(zrodlo1->getWielkoscBloku()+zrodlo3->getWielkoscBloku());
	pusty->setDlugoscPliku(petla*pusty->getWielkoscBloku());
}

void SortowanieWieloFib::sortowaniePrzezScalanieBlok(FileHandler* zrodlo1, FileHandler* zrodlo2, FileHandler* cel){
	std::cout << "sortblok\n";
	int i=0;
	int j=0;
	int a, b;
	zrodlo1->strumienIn >> a;
	zrodlo2->strumienIn >> b;
	if(zrodlo1->strumienIn.eof()){
		std::cout << "No kurwa\n";
	}
	while(i<zrodlo1->getWielkoscBloku()&&j<zrodlo2->getWielkoscBloku()){
		if(le(a,b)){
			cel->strumienOut << a << " ";
			i++;
			if(i<zrodlo1->getWielkoscBloku()){
				zrodlo1->strumienIn >> a;
				zrodlo1->strumienIn.clear();
			}
			std::cout << a << "a wieksze\n";
		}
		else{
			cel->strumienOut << b << " ";
			j++;
			if(j<zrodlo2->getWielkoscBloku())
				zrodlo2->strumienIn >> b;
			std::cout << b <<"b wieksze\n";
		}
	}
	if(i==zrodlo1->getWielkoscBloku()){
		for(j; j<zrodlo2->getWielkoscBloku();j++){
			cel->strumienOut << b << " ";
			if(j<zrodlo2->getWielkoscBloku()-1)
				zrodlo2->strumienIn >> b;
			std::cout << "wyrownanie b\n";
		}
	}
	else{
		for(i; i<zrodlo1->getWielkoscBloku(); i++){
			cel->strumienOut << a << " ";
			if(i<zrodlo1->getWielkoscBloku()-1)
				zrodlo1->strumienIn >> a;
			std::cout << "wyrownanie a\n";
		}
	}	
}


