#ifndef DYSTRYBUCJA_H
#define DYSTRYBUCJA_H

#include "zmiennePomSortowania.h"
#include <vector>

class Dystrybucja{
	public:
		Dystrybucja(int size);
		ZmiennePomSortowania * pojemnik;	
		std::vector<int> * dzialaj();
		int n;
	private:
		std::vector<int> FibTab[4];
		void wyliczRzad();
		void wyliczSume();
		int* wyliczPodzial(); // uwaga alokuje tablice
		void przydzielPartie(int*);

};

#endif
