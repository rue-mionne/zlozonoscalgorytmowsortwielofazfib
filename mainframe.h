#ifndef MAINF_H
#define MAINF_H

#include <cstdlib>
#include <cstdio>
#include <string>
#include <map>
#include "test.h"

class Mainframe{
	private:
		std::map<std::string, Test> testBase;
	public:
		void startMainframe();
		void addTest(std::string, int);
		void menuGlowne();
		
};

#endif
