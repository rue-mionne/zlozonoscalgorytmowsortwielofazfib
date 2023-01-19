#include "test.h"
#include "fileHandler.h"
#include "itestable.h"
#include "licznik.h"
#include "sortowanieWieloFib.h"
#include <cstdio>
#include <ios>
#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>

Test::Test(int start, int koniec, int repeats):licznik(new Timer(start, koniec, repeats)){
	pliki[0] = "pliki/plik1";
	pliki[1] = "pliki/plik2";
	pliki[2] = "pliki/plik3";
	pliki[3] = "pliki/plik4";
}

void Test::wykonajTest(int n){
	prepareData(n);
	algorytm= new SortowanieWieloFib(n, pliki);
	algorytm->start();
	delete algorytm;

}

void Test::prepareData(int n){
	std::fstream egzekutor;
	for(int i=0;i<4;i++){
		egzekutor.open(pliki[i], std::ios_base::out | std::ios_base::trunc);
		egzekutor.close();
	}
	int liczbaPseudoLosowa;
	egzekutor.open(pliki[3], std::ios_base::out|std::ios_base::binary);
	for(int i=0;i<n;i++){
		liczbaPseudoLosowa =((rand())%1000);
		egzekutor << liczbaPseudoLosowa << " ";
	}
	egzekutor.close();
}

void Test::rozpocznijSerię(){
	try{
		while(true){
			std::cout << "step range\n";
			try{
				while(true){
					algorytm=new SortowanieWieloFib(licznik->getRangeCount(),pliki);	
					prepareData(licznik->getRangeCount());
					algorytm->start();
					licznik->stepRepeat();
					delete algorytm;
				}
			}
			catch(EndOfRepeatCycle* e){
			}
			licznik->stepRange();
		}
	}
	catch(EndOfRangeExc* e){
		std::cout << "Koniec zakresu\n";
	}
}

std::string Test::wyswietlWyniki(){
	std::map<int, int*>* temp = algorytm->zwrocWynikiAnalizyAlg();
	std::map<int,int*>::iterator it;
	std::string wyniki;
	std::stringstream strumien;
	for(it=temp->begin(); it!=temp->end(); it++){
		int* tab=it->second;
		strumien << tab[0] << " " << tab[1] << "\n";
	}
	std::getline(strumien,wyniki,',');
	//strumien >> wyniki;
	return wyniki;
}


void Test::eksportujWyniki(std::string sciezka){
	std::fstream zapis(sciezka);
	zapis << wyswietlWyniki();
}
