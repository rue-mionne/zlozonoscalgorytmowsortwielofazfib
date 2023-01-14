#ifndef SORTOWANIEWIELOFIB_H
#define SORTOWANIEWIELOFIB_H

#include <string>
#include <vector>
#include "itestable.h"
#include "fileHandler.h"
#include "zmiennePomSortowania.h"
#include "dystrybucja.h"


class SortowanieWieloFib:public Itestable{
	public: 
		SortowanieWieloFib(int, std::string*);
		int sortuj();
		void start()override;
	private:
		ZmiennePomSortowania pojemniczek;

		Dystrybucja dystrybucja;

		std::vector<int> FibTab[4]; //wektor<T>: struktura przypominająca listę dwustronnie łączoną w implementacji tablicowej, jej zaletą, którą projekt wykorzystuje jest szybki dostęp do ostatniego elementu i jej duża elastyczność, ponadto ewentualne zmiany wymagajace dostepu do innych elementow nie wplyna negatywnie na wydajnosc (w przeciwienstwie do list<T>, bedacej lista w implementacji wskaznikowej)
		FileHandler* pusty;
		FileHandler* zrodlo1;
		FileHandler* zrodlo2;
		FileHandler* zrodlo3;
		FileHandler* temp;

		void wyliczRzad();
		void wyliczFibSume();
		int* wyliczPodzial(); //uwaga, alokuje tablice
		void przydzielPartie(int* , int);
		
		void przygotujDoSortowania();
		void zmianaPlikow();
		void sortowaniePrzezScalanie();
		void sortujPrzezScalanieFaza1();
		void sortujPrzezScalanieFaza2();
		void sortowaniePrzezScalaniePlik(FileHandler*, FileHandler*, FileHandler*);
		void sortowaniePrzezScalanieBlok(FileHandler*, FileHandler*, FileHandler*);
};


#endif
