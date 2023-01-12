#include "sortowanieWieloFib.h"
#include "fileHandler.h"

SortowanieWieloFib::SortowanieWieloFib(int n, std::string* pliki){
	this->n=n;
	this->pliki=pliki;
	count = 0;

}

void SortowanieWieloFib::dystrybuj(){
	for(int i=0; i<4; i++){
		opiekunowie[i]= new FileHandler(pliki[i]);
		opiekunowie[i]->otworzPlik();
	}

	
}

void SortowanieWieloFib::wyliczRzad(){
	FibTab[0].emplace_back(1);
	FibTab[1].emplace_back(1);
	FibTab[2].emplace_back(2);

}

void SortowanieWieloFib::wyliczFibSume(){
	FibTab[3].emplace_back(FibTab[0].back()+FibTab[1].back()+FibTab[2].back());
}
