#include "test.h"
#include "functionbase.h"
#include "itestable.h"
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <iostream>

Test::Test(){
	//this->algorytm=new Algorytm(wskfunkcja, "test");
}


Test& Test::operator=(Test& wzor){
	if(&wzor==this) return *this;
	//funkcja=wzor.funkcja;
	int n;
	std::cout << "Podaj liczbę elementów:";
	std::cin >> n;
	inicjujTest(n);
	return *this;
}

void Test::wykonajTest(){
	algorytm->start();

}

void Test::inicjujTest(int n){
	//this->n = n;
}
