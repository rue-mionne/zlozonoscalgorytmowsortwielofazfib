#include "itestable.h"

std::map<int, int*> Itestable::wynikiAlgorytmu; //mapa zbierające wyniki testów
int Itestable::id; //zmienna przechowująca id ostatniego testu w celu przydzielania kluczy do mapy


//
//funkcje operacji dominujących - wykonują daną operację i ją zliczają
//
bool Itestable::lt(int a, int b){//a mniejsze od b
	count++;
	return a<b;
}

bool Itestable::le(int a, int b){//a mniejsze równe b
	count++;
	return a<=b;
}

bool Itestable::gt(int a, int b){//a większe od b
	count++;
	return a>b;
}

bool Itestable::ge(int a, int b){//a większe równe b
	count++;
	return a>=b;
}

bool Itestable::eq(int a, int b){//a równe b
	count++;
	return a=b;
}

bool Itestable::ne(int a, int b){//a różne od b
	count++;
	return a!=b;
}

//
//funkcja zwracająca adres to mapy z wynikami
//
std::map<int, int*>* Itestable::zwrocWynikiAnalizyAlg(){
	return &wynikiAlgorytmu;
}

//
//zakończenie pojedynczego testu algorytmu
//
void Itestable::zakonczAlg(){
	int* tab= new int [2];//utwórz tablicę przechowującą liczbę elementów i ilość operacji dominujących
	tab[0]=n;
	tab[1]=count;
	wynikiAlgorytmu.emplace(id, tab);//umieść wyniki w mapie
	id++;//przyznaj nowy klucz
}
