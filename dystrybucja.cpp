#include "dystrybucja.h"
#include "fileHandler.h"
#include <cstdint>
#include <vector>

Dystrybucja::Dystrybucja(int size):n(size){}

std::vector<int> * Dystrybucja::dzialaj(){
	//otwarcie plikow
	for(int i=0; i<4; i++){
		pojemnik->opiekunowie[i]=new FileHandler(pojemnik->pliki[i]);
		pojemnik->opiekunowie[i]->otworzPlik();
	}
	int suma=0;
	//faza wyliczenia przydziału
	wyliczRzad();
	int * tablicaPodzialu = wyliczPodzial();
	while(suma<n){
		przydzielPartie(tablicaPodzialu);
		delete tablicaPodzialu;
		tablicaPodzialu = wyliczPodzial();
		suma = FibTab[3].back();
	}
	pojemnik->opiekunowie[3]->przesunZapisNaKoniec();
	for(int i=suma-n; i>0; i--){
		pojemnik->opiekunowie[3]->strumien << INT16_MAX << " ";
	}
	przydzielPartie(tablicaPodzialu);
	delete tablicaPodzialu;
	return FibTab;
}

void Dystrybucja::wyliczRzad(){
	if(FibTab[0].empty()){
		FibTab[0].emplace_back(1);
		FibTab[1].emplace_back(1);
		FibTab[2].emplace_back(2);
		wyliczSume();
	}
	else{
		FibTab[0].emplace_back(FibTab[1].back());
		FibTab[1].emplace_back(FibTab[2].back());
		FibTab[2].emplace_back(FibTab[0].back()+FibTab[1].back());
		wyliczSume();
	}
}

void Dystrybucja::wyliczSume(){
	FibTab[3].emplace_back(FibTab[0].back()+FibTab[1].back()+FibTab[2].back());
}

int* Dystrybucja::wyliczPodzial(){
	if(FibTab[0].size()==1){
		int* tab = new int [4];
		for(int i = 0; i<4; i++){
			tab[i]=FibTab[i].back();
		}
		return tab;
	}
	int tablicaRoznicy[2][4];
	for(int i = 0; i<4; i++){
		tablicaRoznicy[0][i]=FibTab[i].back();
	}
	wyliczRzad();
	for(int i = 0; i<4; i++){
		tablicaRoznicy[1][i]=FibTab[i].back();
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
			char waste;
			pojemnik->opiekunowie[3]->strumien >> temp;
			pojemnik->opiekunowie[3]->strumien.get(waste);
			pojemnik->opiekunowie[i]->strumien << temp << " ";
		}
	}
}
