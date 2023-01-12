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

void SortowanieWieloFib::dystrybuj(){
	//otwarcie plików
	for(int i=0; i<4; i++){
		opiekunowie[i]= new FileHandler(pliki[i]);
		opiekunowie[i]->otworzPlik();
	}
	int suma=0;
	//faza wyliczenia przydziału
	wyliczRzad();
	int * tablicaPodzialu = wyliczPodzial();
	while(suma<n){
		przydzielPartie(tablicaPodzialu, suma);//faza podziału
		}
	opiekunowie[3]->przesunZapisNaKoniec();
	for(int i = suma-n; i>0; i--){
		opiekunowie[3]->strumien << INT16_MAX << " "; 
	}
	przydzielPartie(tablicaPodzialu, suma);
}

void SortowanieWieloFib::wyliczRzad(){
	if(FibTab[0].empty()){
		FibTab[0].emplace_back(1);
		FibTab[1].emplace_back(1);
		FibTab[2].emplace_back(2);
		wyliczFibSume();
	}
	else{
		FibTab[0].emplace_back(FibTab[1].back());
		FibTab[1].emplace_back(FibTab[2].back());
		FibTab[2].emplace_back(FibTab[0].back()+FibTab[1].back());
		wyliczFibSume();
	}
}

void SortowanieWieloFib::wyliczFibSume(){
	FibTab[3].emplace_back(FibTab[0].back()+FibTab[1].back()+FibTab[2].back());
}

int* SortowanieWieloFib::wyliczPodzial(){
	if(FibTab[0].size()==1){
		int* tab = new int [4];
		for(int i=0;i<4;i++){
			tab[i]=FibTab[i].back();
		}
		return tab;
	}
	int tablicaRoznicy[2][4];
	for(int i=0;i<4;i++){
		tablicaRoznicy[0][i]=FibTab[i].back();
	}
	wyliczRzad();
	for(int i=0;i<4;i++){
		tablicaRoznicy[1][i]=FibTab[i].back();
	}
	int *tablicaPodzialu = new int [4];
	for(int i=0; i<4; i++){
		tablicaPodzialu[i]=tablicaRoznicy[1][i]-tablicaRoznicy[0][i];
	}
	return tablicaPodzialu;
}

void SortowanieWieloFib::przydzielPartie(int* tablicaPodzialu, int suma){
	for(int i=0;i<3;i++){
		for(int j=0;j<tablicaPodzialu[i]; j++){
			int temp;
			char waste;
			opiekunowie[3]->strumien >> temp;
			opiekunowie[3]->strumien.get(waste);
			opiekunowie[i]->strumien << temp << " ";
		}
	}
	suma=FibTab[3].back();

}
