#ifndef TEST_H
#define TEST_H

#include <cstdlib>
#include <string>
#include "itestable.h"

class Test{
	private:
		int n;
		Itestable* algorytm;
	public:
		Test();
		void wykonajTest();
		void usunWynik(std::string);
		void inicjujTest(int);
		std::string wyswietlWyniki();
		Test& operator=(Test&);
		void eksportujWyniki(std::string sciezka);
};

#endif
