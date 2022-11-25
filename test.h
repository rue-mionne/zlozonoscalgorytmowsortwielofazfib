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
		void wykonajTest();
		void usunWynik(std::string, int);
};

#endif
