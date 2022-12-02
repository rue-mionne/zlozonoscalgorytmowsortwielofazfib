#include "test.h"
#include "functionbase.h"
#include "funkcja.h"
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <iostream>

Test::Test(){
	this->funkcja=new Funkcja(wskfunkcja, "test");
}


Test& Test::operator=(Test& wzor){
	if(&wzor==this) return *this;
	funkcja=wzor.funkcja;
	int n;
	std::cout << "Podaj liczbę elementów:";
	std::cin >> n;
	inicjujTest(n);
	return *this;
}

void Test::wykonajTest(){
	funkcja->wykonajFunkcje(n);

}

void Test::inicjujTest(int n){
	this->n = n;
}
