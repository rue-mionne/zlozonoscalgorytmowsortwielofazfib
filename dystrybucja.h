#ifndef DYSTRYBUCJA_H
#define DYSTRYBUCJA_H

#include "zmiennePomSortowania.h"
#include <vector>

class Dystrybucja{
	public:
		Dystrybucja(int size, ZmiennePomSortowania* pojemnik);
		ZmiennePomSortowania * pojemnik;	
		void dzialaj();
		int n;
	//private:
		void wyliczRzad();
		void wyliczSume();
		int* wyliczPodzial(); // uwaga alokuje tablice
		void przydzielPartie(int*);

};

#endif
