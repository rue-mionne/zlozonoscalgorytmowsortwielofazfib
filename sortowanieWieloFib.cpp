#include "sortowanieWieloFib.h"
#include "fileHandler.h"
#include <cstdint>
#include <cstdio>
#include <cstdlib>

SortowanieWieloFib::SortowanieWieloFib(int n, std::string* pliki){
	this->n=n;
	pojemniczek.pliki=pliki;
	count = 0;

}

int SortowanieWieloFib::sortuj(){
	przygotujDoSortowania();
	sortowaniePrzezScalanie();
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

void SortowanieWieloFib::zmianaPlikow(){ //konieczne wyznaczenie plikow o najmniejszej i najwiekszej ilosci blokow: kolejnym celem jest zawsze ten o najmniejszej ilosci, ale sam algorytm nie przesuwa sie cyklicznie
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
	int wielkoscBloku=0;
	while(wielkoscBloku<n){
		sortujPrzezScalanieFaza1();
		sortujPrzezScalanieFaza2();
		zmianaPlikow();

	}
}

void SortowanieWieloFib::sortujPrzezScalanieFaza1(){
	zrodlo1->przesunZapisNaKoniec(); //przygotowanie zapisu scalonego ciągu na końcu najkrótszego pliku
	sortowaniePrzezScalaniePlik(zrodlo1, zrodlo2, zrodlo1);
}

void SortowanieWieloFib::sortujPrzezScalanieFaza2(){
	pusty->resetuj();//przygotowanie celu pod zapis
	sortowaniePrzezScalaniePlik(zrodlo1, zrodlo3, pusty);
}

void SortowanieWieloFib::sortowaniePrzezScalaniePlik(FileHandler* zrodlo1, FileHandler* zrodlo2, FileHandler* cel){
	int petla=zrodlo1->getDlugoscPliku()/zrodlo1->getWielkoscBloku();
	for(int i = 0; i < petla; i++){
		sortowaniePrzezScalanieBlok(zrodlo1, zrodlo2, cel);
	}
	pusty->resetuj();
	pusty->setWielkoscBloku(zrodlo1->getWielkoscBloku()+zrodlo2->getWielkoscBloku()+zrodlo3->getWielkoscBloku());
	pusty->setDlugoscPliku(petla*pusty->getWielkoscBloku());
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


