#include "test.h"
#include "functionbase.h"

#include "itestable.h"
#include "licznik.h"
#include <istream>
#include <iterator>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>

Test::Test(){
	//this->algorytm=new Algorytm(wskfunkcja, "test");
}



void Test::wykonajTest(){
	algorytm->start();

}

void Test::inicjujTest(int start, int koniec, int repeats){
	licznik=new Timer(start,koniec, repeats);
}

void Test::rozpocznijSerię(){
	try{
		while(true){
			//algorytm=new Itestable(licznik->getRangeCount());//placeholder
			licznik->stepRange();
			try{
				while(true){
					algorytm->start();
					licznik->stepRepeat();
				}
			}
			catch(EndOfRepeatCycle){
			
			}
		}
	}
	catch(EndOfRangeExc){
	
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
	strumien >> wyniki;
	return wyniki;
}


void Test::eksportujWyniki(std::string sciezka){
	std::fstream zapis(sciezka);
	zapis << wyswietlWyniki();
}
