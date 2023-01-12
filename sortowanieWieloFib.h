#ifndef SORTOWANIEWIELOFIB_H
#define SORTOWANIEWIELOFIB_H

#include <string>
#include <vector>
#include "itestable.h"
#include "fileHandler.h"

class SortowanieWieloFib:public Itestable{
	public: 
		SortowanieWieloFib(int, std::string*);
		void dystrybuj();
		int sortuj();
		void start()override;
	private:
		std::string* pliki;
		FileHandler* opiekunowie[4];
		FileHandler* pusty;
		FileHandler* zrodlo1;
		FileHandler* zrodlo2;
		FileHandler* zrodlo3;
		FileHandler* temp;

		std::vector<int> FibTab[4];
		void wyliczRzad();
		void wyliczFibSume();
		int* wyliczPodzial(); //uwaga, alokuje tablice
		void przydzielPartie(int* , int);
};

#endif
