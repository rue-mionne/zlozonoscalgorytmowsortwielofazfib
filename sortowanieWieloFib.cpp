#include "sortowanieWieloFib.h"
#include "dystrybucja.h"
#include "fileHandler.h"
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <ios>
#include <iostream>
#include <ostream>

//
//Konstruktor: przypisanie n, inicjacja obiektu odpowiadajacego za dystrybucje danych, zapisanie nazw plikow w obiekcie na dane dzielone, zainicjowanie liczby operacji dominujacych
//

SortowanieWieloFib::SortowanieWieloFib(int n, std::string* pliki):dystrybucja(n, &pojemniczek){
	this->n=n;
	pojemniczek.pliki=pliki;
	count = 0;

}

//
//Dekonstruktor; pusty
//


SortowanieWieloFib::~SortowanieWieloFib(){
}

//
//Start algorytmu
//

void SortowanieWieloFib::start(){
	dystrybucja.dzialaj();	//uruchomienie dystrybucji wartosci miedzy plikami
	sortuj(); //wywolanie funkcji sortujacej
	zakonczAlg(); //zapisanie liczby sortowanych elementow i operacji dominujacych w mapie
}

//
//Funkcja zbierajaca trzy etapy sortowania; ze wzgledu na czytelnosc
//
void SortowanieWieloFib::sortuj(){
	przygotujDoSortowania();
	sortowaniePrzezScalanie();//rdzen scalania wielofazowego; nazwa troche mylaca
	przepisz();//przepisanie posortowanego ciagu do pliku "plikZWynikami.txt"
}

//
//Funkcje pomocnicze sortowania
//

//
//Przypisanie opiekunow plikow do etykiet sterujacych, ustawienie poczatkowej wartosci bloku i dlugosci pliku liczonej w elementach
//
void SortowanieWieloFib::przygotujDoSortowania(){
	zrodlo1=pojemniczek.opiekunowie[0];
	zrodlo2=pojemniczek.opiekunowie[1];
	zrodlo3=pojemniczek.opiekunowie[2];
	pusty=pojemniczek.opiekunowie[3];
	
	for(int i = 0; i<3; i++){
		pojemniczek.opiekunowie[i]->setWielkoscBloku(1); //poczatkowo wszystkie bloki maja wielkosc 1
		pojemniczek.opiekunowie[i]->setDlugoscPliku(pojemniczek.FibTab[i].back());//dlugosc kazdego pliku jest zapisana w tablicy list wyliczonej przez dystrybucje
	}
}

//
//Po wykonanym sortowaniu nalezy wyznaczyc nowy plik zapisu
//
void SortowanieWieloFib::zmianaPlikow(){ 	
	temp=pusty; //zapisanie adresu pliku, ktory byl plikiem zapisu w poprzedniej iteracji
	int liczbaBlokow[3];
	FileHandler* tempHandlery[3]; //tymczasowe miejsca na adresy
	tempHandlery[0]=zrodlo2;
	liczbaBlokow[0]=zrodlo2->getDlugoscPliku()/zrodlo2->getWielkoscBloku();
	//kazdy plik poza plikiem, ktory w poprzedniej iteracji mial najmniejsza ilosc blokow (bedzie kolejnym plikiem zapisu w aktualnej iteracji) zostaje podpiety pod tymczasowe miejsce a w tablicy zapisana zostaje jego wyliczona ilosc blokow
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
	pusty=zrodlo1; //plik bez blokow (wszystkie jego bloki zostaly posortowane w poprzedniej iteracji) zostaje oznaczony jako pusty plik do zapisu
	zrodlo1=tempHandlery[min];//plik zrodel zostaje posortowane rosnaco wedlug liczby blokow
	zrodlo2=tempHandlery[mid];
	zrodlo3=tempHandlery[max];

}

//
//rdzen sortowania, tu proces jest dzielony na fazy i powtarzany
//
void SortowanieWieloFib::sortowaniePrzezScalanie(){
	int wielkoscBloku=0; //zmienna przechowujaca najwieksza wielkos bloku
	while(wielkoscBloku<n){ //algorytm konczy sie, kiedy blok jest rowny liczbie elementow: calosc jest posortowana
		petla=zrodlo1->getDlugoscPliku()/zrodlo1->getWielkoscBloku();//liczba sortowan zalezy od ilosci blokow pliku, ktory ma ich najmniej
		sortujPrzezScalanieFaza1(); //sortowanie przez scalanie blokow z plikow 1 i 2
		sortujPrzezScalanieFaza2(); //sortowanie przez scalanie scalonych w fazie 1 blokow z blokami pliku3
		wielkoscBloku = pusty->getWielkoscBloku(); //aktualizacja wielkosci najwiekszego bloku
		zmianaPlikow(); //zmiana rol plikow

	}
}

void SortowanieWieloFib::sortujPrzezScalanieFaza1(){
	zrodlo1->przesunZapisNaKoniec(); //przygotowanie zapisu scalonego ciągu na końcu najkrótszego pliku
	sortowaniePrzezScalaniePlik(zrodlo1, zrodlo2, zrodlo1); //opis funkcji nizej
	zrodlo1->setWielkoscBloku(zrodlo1->getWielkoscBloku()+zrodlo2->getWielkoscBloku()); //wielkosc bloku pliku 1 zostaje ustawiona jako wielkosc bloku scalonego z 1 i 2
	zrodlo2->setDlugoscPliku(zrodlo2->getDlugoscPliku()-(zrodlo2->getWielkoscBloku()*petla));//dlugosc pliku 2 staje sie mniejsza o ilosc posortowanych elementow
	zrodlo1->odswiez(); //funkcje stworzone z przymusu, wiecej informacji w pliku fileHandler.cpp
}

void SortowanieWieloFib::sortujPrzezScalanieFaza2(){
	pusty->resetuj();//przygotowanie celu pod zapis, wskazniki odczytu i zapisu wracaja na poczatek
	sortowaniePrzezScalaniePlik(zrodlo1, zrodlo3, pusty);
	zrodlo3->setDlugoscPliku(zrodlo3->getDlugoscPliku()-zrodlo3->getWielkoscBloku()*petla);//dlugosc pliku 3 staje sie mniejsza o ilosc posortowanych elementow
	pusty->resetuj();//przygotowanie nowo zapisanego pliku pod odczyt
	pusty->setWielkoscBloku(zrodlo1->getWielkoscBloku()+zrodlo3->getWielkoscBloku());//wielkosc bloku jest suma blokow plikow 1 (ktory jest suma plikow 1 i 2) i 3 
	pusty->setDlugoscPliku(petla*pusty->getWielkoscBloku());//ilosc elementow jest rowna iloczynowi posortowanych blokow i dlugosci bloku

}

//
//sortowanie przez scalanie na trzech plikach: dwoch zrodlach i jednym celu
//
void SortowanieWieloFib::sortowaniePrzezScalaniePlik(FileHandler* zrodlo1, FileHandler* zrodlo2, FileHandler* cel){
	for(int i = 0; i < petla; i++){ //dla kazdego bloku najmniejszego pliku
		sortowaniePrzezScalanieBlok(zrodlo1, zrodlo2, cel);//scal bloki
	}
	}
//
//sortowanie przez scalanie bloku
//
void SortowanieWieloFib::sortowaniePrzezScalanieBlok(FileHandler* zrodlo1, FileHandler* zrodlo2, FileHandler* cel){
	int i=0;
	int j=0;
	int a, b;
	zrodlo1->strumienIn >> a; //pobierz po elemencie z plikow
	zrodlo2->strumienIn >> b;
	while(i<zrodlo1->getWielkoscBloku()&&j<zrodlo2->getWielkoscBloku()){//dopoki w ktoryms bloku nie dojdzie sie do konca
		if(le(a,b)){//le=lesser equal, operacja dominujaca mniejsze rowne
			cel->strumienOut << a << " "; //jesli a jest mniejsze, zapisz je w pliku docelowymm
			i++; //zaktualizuj pozycje w bloku zrodle 1
			if(i<zrodlo1->getWielkoscBloku()){ //jesli cos jeszcze w bloku zostalo
				zrodlo1->strumienIn >> a; //pobierz kolejny element
			}
		}
		else{
			cel->strumienOut << b << " ";//jesli b jest mniejsze, zapisz je w pliku docel
			j++; //zaktualizuj pozycje w zrodle 2
			if(j<zrodlo2->getWielkoscBloku())//jesli cos w bloku zostalo
				zrodlo2->strumienIn >> b;//pobierz kolejny element
		}
	}
	if(i==zrodlo1->getWielkoscBloku()){//jesli w bloku zrodla 1 skonczyly sie elementy
		for(j; j<zrodlo2->getWielkoscBloku();j++){//przepisz pozostale elementy bloku zrodla 2
			cel->strumienOut << b << " ";
			if(j<zrodlo2->getWielkoscBloku()-1)
				zrodlo2->strumienIn >> b;
		}
	}
	else{//jesli w bloku zrodla 2 skonczyly sie elementy
		for(i; i<zrodlo1->getWielkoscBloku(); i++){//przepisz pozostale elementy bloku zrodla 1
			cel->strumienOut << a << " ";
			if(i<zrodlo1->getWielkoscBloku()-1)
				zrodlo1->strumienIn >> a;
		}
	}	
}

//
//Wyodrebnienie posortowanego ciagu do osobnego pliku
//

void SortowanieWieloFib::przepisz(){
	std::fstream wyniki;
	int liczba;
	temp->resetuj();//przygotowanie pliku z posortowanym ciagiem do odczytu
	wyniki.open("plikZWynikami.txt", std::ios_base::out|std::ios_base::binary);//otwarcie pliku z wynikami
	for(int i=0; i<n;i++){
		temp->strumienIn >> liczba;//odczytanie z pliku elementu
		wyniki << liczba << " ";//zapisanie elementu w pliku docelowym
	}
	for(int i=0; i<4;i++){
		pojemniczek.opiekunowie[i]->zakoncz();//zamkniecie plikow uzywanych do sortowania
		delete pojemniczek.opiekunowie[i];//zwolnienie miejsca przez opiekonow plikow
	}

}
