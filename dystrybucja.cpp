#include "dystrybucja.h"
#include "fileHandler.h"
#include "zmiennePomSortowania.h"
#include <cstdint>
#include <ios>
#include <istream>
#include <vector>
#include <limits>
#include <iostream> //debugging

Dystrybucja::Dystrybucja(int size, ZmiennePomSortowania* pojemnik):n(size){
	this->pojemnik=pojemnik;
	std::cout << "\nDystrkonstr";
}

void Dystrybucja::dzialaj(){
	//otwarcie plikow
	for(int i=0; i<4; i++){
		pojemnik->opiekunowie[i]=new FileHandler(pojemnik->pliki[i]);
		pojemnik->opiekunowie[i]->otworzPlik();
	}
	int suma=0;
	//faza wyliczenia przydziału
	int * tablicaPodzialu = wyliczPodzial();
	while(suma<n){
		przydzielPartie(tablicaPodzialu);	
		delete tablicaPodzialu;	
		tablicaPodzialu = wyliczPodzial(); 
		suma = pojemnik->FibTab[3].back(); 
		std::cout <<suma << "\n";
	}
	pojemnik->opiekunowie[3]->strumienOut.seekp(-1, std::ios_base::end);	
	pojemnik->opiekunowie[3]->strumienOut << " ";
	for(int i=suma-n; i>0; i--){
		pojemnik->opiekunowie[3]->strumienOut << std::numeric_limits<int>::max() << " ";
	}
	pojemnik->opiekunowie[3]->odswiez();
	przydzielPartie(tablicaPodzialu);
	delete tablicaPodzialu;

	for(int i=0; i<4; i++){
		pojemnik->opiekunowie[i]->odswiez();
	}

}

void Dystrybucja::wyliczRzad(){

	std::cout << "\nRząd";

	if(pojemnik->FibTab[0].empty()){
		pojemnik->FibTab[0].emplace_back(1);
		pojemnik->FibTab[1].emplace_back(1);
		pojemnik->FibTab[2].emplace_back(2);
		wyliczSume();
	}
	else{
		pojemnik->FibTab[0].emplace_back(pojemnik->FibTab[1].back());
		pojemnik->FibTab[1].emplace_back(pojemnik->FibTab[2].back());
		pojemnik->FibTab[2].emplace_back(pojemnik->FibTab[0].back()+pojemnik->FibTab[1].back());
		wyliczSume();
	}
}

void Dystrybucja::wyliczSume(){
	std::cout << "\nSuma";


	pojemnik->FibTab[3].emplace_back(pojemnik->FibTab[0].back()+pojemnik->FibTab[1].back()+pojemnik->FibTab[2].back());
}

int* Dystrybucja::wyliczPodzial(){
	std::cout << "\nPodzial";
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
		std::cout << tablicaRoznicy[0][i]<<std::endl;
	}
	wyliczRzad();
	for(int i = 0; i<4; i++){
		tablicaRoznicy[1][i]=pojemnik->FibTab[i].back();
		std::cout << tablicaRoznicy[1][i]<<std::endl;
	}
	int * tablicaPodzialu = new int [4];
	for(int i=0; i<4; i++){
		tablicaPodzialu[i]=tablicaRoznicy[1][i] - tablicaRoznicy[0][i];
		std::cout << tablicaPodzialu[i] << std::endl;
	}
	return tablicaPodzialu;
}

void Dystrybucja::przydzielPartie(int* tablicaPodzialu){
	std::cout << "rozdziel\n";
	for(int i = 0; i<3; i++){
		for(int j = 0; j<tablicaPodzialu[i]; j++){
			int temp;
			pojemnik->opiekunowie[3]->strumienIn >> temp;
			std::cout << temp << std::endl;
			pojemnik->opiekunowie[i]->strumienOut << temp << " ";
		}
	}
}
