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
		void start()override;
		~SortowanieWieloFib();

	private:

		int petla;

		Dystrybucja dystrybucja;
		ZmiennePomSortowania pojemniczek;

		FileHandler* pusty;
		FileHandler* zrodlo1;
		FileHandler* zrodlo2;
		FileHandler* zrodlo3;
		FileHandler* temp;

		void wyliczRzad();
		void wyliczFibSume();
		int* wyliczPodzial();
		void przydzielPartie(int* , int);
		
		void sortuj();
		void przygotujDoSortowania();
		void zmianaPlikow();
		void sortowaniePrzezScalanie();
		void sortujPrzezScalanieFaza1();
		void sortujPrzezScalanieFaza2();
		void sortowaniePrzezScalaniePlik(FileHandler*, FileHandler*, FileHandler*);
		void sortowaniePrzezScalanieBlok(FileHandler*, FileHandler*, FileHandler*);
		void przepisz();
};


#endif
