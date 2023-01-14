#include "itestable.h"

std::map<int, int*> Itestable::wynikiAlgorytmu;
int Itestable::id;

bool Itestable::lt(int a, int b){
	count++;
	return a<b;
}

bool Itestable::le(int a, int b){
	count++;
	return a<=b;
}

bool Itestable::gt(int a, int b){
	count++;
	return a>b;
}

bool Itestable::ge(int a, int b){
	count++;
	return a>=b;
}

bool Itestable::eq(int a, int b){
	count++;
	return a=b;
}

bool Itestable::ne(int a, int b){
	count++;
	return a!=b;
}

std::map<int, int*>* Itestable::zwrocWynikiAnalizyAlg(){
	return &wynikiAlgorytmu;
}

void Itestable::zakonczAlg(){
	int* tab= new int [2];
	tab[0]=n;
	tab[1]=count;
	wynikiAlgorytmu.emplace(id, tab);
}
