#include <cstdlib>
#include <cstdio>
#include <ios>
#include <iterator>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "functionbase.h"
#include "funkcja.h"

void Funkcja::dodajWynik(int n, int wynik){
	wynikiDlaFunkcji.emplace(n, wynik);
}

void Funkcja::usunWynik(int n){
	wynikiDlaFunkcji.erase(n);
}

std::string Funkcja::wypiszWyniki(){
	std::string wyniki;
	std::string szablonLinijki = "|           |\n";
	std::map<int, int>::iterator it;
	wyniki.append("Wyniki funkcji: " + nazwa + "\n");
	for(it=wynikiDlaFunkcji.begin(); it!=wynikiDlaFunkcji.end(); ++it){
		wyniki.append(12,'-');
		wyniki.append("\n");
		std::string tempLinijka = szablonLinijki;
		std::ostringstream n;
		n<<(it->first) << "|" << (it->second);
		tempLinijka.replace(1,10,n.str());
		wyniki.append(tempLinijka);
		tempLinijka.erase();

	}
	return wyniki;
}

int Funkcja::wykonajFunkcje(int n){
	int temp=cialo(n);
	dodajWynik(n, temp);
	return temp;
}

void Funkcja::eksportujWyniki(std::string sciezka){
	std::fstream outstream(sciezka);
	for(std::map<int, int>::iterator it = wynikiDlaFunkcji.begin(); it != wynikiDlaFunkcji.end(); ++it){
		outstream << it->first << " " << it->second << "\n";
	}
	outstream.close();
}
