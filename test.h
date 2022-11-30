#ifndef TEST_H
#define TEST_H

#include <cstdlib>
#include <string>
#include "funkcja.h"

class Test{
	private:
		int n;
		Funkcja* funkcja;
	public:
		Test(std::string);
		void wykonajTest();
		void usunWynik(std::string);
		void inicjujTest(int);
};

#endif
