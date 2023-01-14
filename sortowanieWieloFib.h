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

//SERIA ZMIENNYCH TYMCZASOWO PUBLICZNYCH
		int petla;

		Dystrybucja dystrybucja;
		ZmiennePomSortowania pojemniczek;
		private:


		FileHandler* pusty;
		FileHandler* zrodlo1;
		FileHandler* zrodlo2;
		FileHandler* zrodlo3;
		FileHandler* temp;

		void wyliczRzad();
		void wyliczFibSume();
		int* wyliczPodzial(); //uwaga, alokuje tablice
		void przydzielPartie(int* , int);
		
	public:	
		void przygotujDoSortowania();
		void zmianaPlikow();
		void sortowaniePrzezScalanie();
		void sortujPrzezScalanieFaza1();
		void sortujPrzezScalanieFaza2();
		void sortowaniePrzezScalaniePlik(FileHandler*, FileHandler*, FileHandler*);
		void sortowaniePrzezScalanieBlok(FileHandler*, FileHandler*, FileHandler*);
};


#endif
