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

		std::vector<int> FibTab[4];
		void wyliczRzad();
		void wyliczFibSume();
};

#endif
