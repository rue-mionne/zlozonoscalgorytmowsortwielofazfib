#ifndef ZMIENNEPOM_H
#define ZMIENNEPOM_H

#include "fileHandler.h"
#include <string>
#include <vector>


class ZmiennePomSortowania{
	public:
		FileHandler* opiekunowie[4];
		std::string* pliki;
		std::vector<int> FibTab[4];
};

#endif
