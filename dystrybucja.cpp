#include "dystrybucja.h"
#include "fileHandler.h"
#include "zmiennePomSortowania.h"
#include <cstdint>
#include <ios>
#include <istream>
#include <vector>
#include <limits>

//
//konnstruktor obiektu: inicjalizacja liczby elementow i podpiecie obiektu z dzielonymi zmiennymi
//

Dystrybucja::Dystrybucja(int size, ZmiennePomSortowania* pojemnik):n(size){
	this->pojemnik=pojemnik;
}

void Dystrybucja::dzialaj(){
	//otwarcie plikow
	for(int i=0; i<4; i++){
		pojemnik->opiekunowie[i]=new FileHandler(pojemnik->pliki[i]);//stworzenie opiekunow plikow
		pojemnik->opiekunowie[i]->otworzPlik();//opiekunowie otwieraja swoje pliki
	}
	int suma=0;
	//faza wyliczenia przydziału
	int * tablicaPodzialu = wyliczPodzial(); //wyliczenie pierwszego przydzialu
	while(suma<n){//dopoki nie zostalu rodzielone wszystkie elementy
		przydzielPartie(tablicaPodzialu);	//przydziel elementy wedlug ilosci wyliczonej w tablicy
		delete tablicaPodzialu;	 //zwolnij miejsce po niepotrzebnej tablicy
		tablicaPodzialu = wyliczPodzial(); //wylicz kolejny podzial
		suma = pojemnik->FibTab[3].back(); //zaktualizuj liczbe przydzielonych elementow
	}
	pojemnik->opiekunowie[3]->strumienOut.seekp(-1, std::ios_base::end); //ustaw wskaznik zapisu na przedostatnie miejsce pliku 4
	for(int i=suma-n; i>0; i--){//az do momentu kiedy ilosc elementow nie bedzie sie zgadzala z ciagiem fibonacchiego
		pojemnik->opiekunowie[3]->strumienOut << std::numeric_limits<int>::max() << " ";//dodaj na koniec maksymalna wartosc int, odpowiednik plus nieskonczonosci
	}
	pojemnik->opiekunowie[3]->odswiez();//upewnij sie, ze warotsci zostaly zapisane w pliku, a nie utknely w buforze
	przydzielPartie(tablicaPodzialu);//dokonaj ostatniego podzialu
	delete tablicaPodzialu;//zwolnij miejsce po tablicy podzialu

	for(int i=0; i<4; i++){
		pojemnik->opiekunowie[i]->odswiez();//upewnij sie ze kazdy plik zostal zapisany
	}

}

//
//funkcja wyliczajaca kolejne rzedy tablicy slozacej do wyznaczania przydzialu
//
void Dystrybucja::wyliczRzad(){


	if(pojemnik->FibTab[0].empty()){//jesli to jest pierwszy rzad
		pojemnik->FibTab[0].emplace_back(1); //zainicjuj tablice wartosciami 1, 1, 2
		pojemnik->FibTab[1].emplace_back(1);
		pojemnik->FibTab[2].emplace_back(2);
		wyliczSume(); //uzupenij ostatni vector o sume
	}
	//
	//rzedy wyliczane wedlug	|f1|f2|f3|
	//				|f2|f3|f2+f3|
	//
	else{
		pojemnik->FibTab[0].emplace_back(pojemnik->FibTab[1].back()); 
		pojemnik->FibTab[1].emplace_back(pojemnik->FibTab[2].back());
		pojemnik->FibTab[2].emplace_back(pojemnik->FibTab[0].back()+pojemnik->FibTab[1].back());
		wyliczSume();
	}
}

void Dystrybucja::wyliczSume(){


	pojemnik->FibTab[3].emplace_back(pojemnik->FibTab[0].back()+pojemnik->FibTab[1].back()+pojemnik->FibTab[2].back());
}

int* Dystrybucja::wyliczPodzial(){
	if(pojemnik->FibTab[0].size()==0){
		wyliczRzad();
		int* tab = new int [4];
		for(int i = 0; i<4; i++){
			tab[i]=pojemnik->FibTab[i].back();
		}
		return tab;
	}
	int tablicaRoznicy[2][4];
	for(int i = 0; i<4; i++){
		tablicaRoznicy[0][i]=pojemnik->FibTab[i].back();
	}
	wyliczRzad();
	for(int i = 0; i<4; i++){
		tablicaRoznicy[1][i]=pojemnik->FibTab[i].back();
	}
	int * tablicaPodzialu = new int [4];
	for(int i=0; i<4; i++){
		tablicaPodzialu[i]=tablicaRoznicy[1][i] - tablicaRoznicy[0][i];
	}
	return tablicaPodzialu;
}

void Dystrybucja::przydzielPartie(int* tablicaPodzialu){
	for(int i = 0; i<3; i++){
		for(int j = 0; j<tablicaPodzialu[i]; j++){
			int temp;
			pojemnik->opiekunowie[3]->strumienIn >> temp;
			pojemnik->opiekunowie[i]->strumienOut << temp << " ";
		}
	}
}
