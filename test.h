#ifndef TEST_H
#define TEST_H

#include <cstdlib>
#include <string>
#include "itestable.h"
#include "licznik.h"

class Test{
	private:
		int n;
		Itestable* algorytm;
		Timer* licznik;
	public:
		Test();
		void wykonajTest();
		void inicjujTest(int, int, int);
		void rozpocznijSerię();
		std::string wyswietlWyniki();
		void eksportujWyniki(std::string sciezka);
};

#endif
