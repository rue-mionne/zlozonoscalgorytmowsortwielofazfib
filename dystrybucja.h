#ifndef DYSTRYBUCJA_H
#define DYSTRYBUCJA_H

#include "sortowanieWieloFib.h"
#include <vector>

class Dystrybucja{
	public:
		ZmiennePomSortowania * pojemnik;	
		std::vector<int> * dzialaj();
		int n;
	private:
		Dystrybucja(int size);
		std::vector<int> FibTab[4];
		void wyliczRzad();
		void wyliczSume();
		int* wyliczPodzial(); // uwaga alokuje tablice
		void przydzielPartie(int*);

};

#endif
