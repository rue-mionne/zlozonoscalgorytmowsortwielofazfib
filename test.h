#ifndef TEST_H
#define TEST_H

#include <cstdlib>
#include <string>
#include "itestable.h"
#include "licznik.h"

class Test{
	private:
		std::string pliki[4];
		int n;
		Itestable* algorytm;
		Timer* licznik;
		void prepareData(int);
		void losuj(int);
	
  public:
		Test(int, int, int);
		void wykonajTest(int);
		void inicjujTest(int, int, int);
		void rozpocznijSerię();
		std::string wyswietlWyniki();
		void eksportujWyniki(std::string sciezka);
};

#endif
