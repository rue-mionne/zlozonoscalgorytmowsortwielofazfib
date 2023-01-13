#ifndef SORTOWANIEWIELOFIB_H
#define SORTOWANIEWIELOFIB_H

#include <string>
#include <vector>
#include "itestable.h"
#include "fileHandler.h"

class ZmiennePomSortowania{
	public:
	FileHandler* opiekunowie[4];
		std::string* pliki;

};

class SortowanieWieloFib:public Itestable{
	public: 
		SortowanieWieloFib(int, std::string*);
		void dystrybuj();
		int sortuj();
		void start()override;
	private:
		ZmiennePomSortowania pojemniczek;
		//
	// TODO: wydzielić części sortowania i dystrybucji na klasy w celu zmniejszenia rozmiaru plików
	//
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
		void przesunWolneBloki();
};


#endif
