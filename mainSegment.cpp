#include <iostream>
#include <cstdlib>
#include <ctime>
#include "test.h"
#include "regresja.h"

int main(){
	srand((unsigned)time(NULL));
	int odpowiedz;
	std::cout << "Witaj w programie testującym algorytm sortowania zewnętrznego wielofazowego z wykorzystaniem czterech plików, wariant wykorzystujący dystrybucję opartą na ciągu Fibonacchiego\n"
		<< "Wybierz opcję testu, wpisując odpowiedni numer:\n"
		<< "1. Pojedynczy test\n"
		<< "2. Seria testów\n";
	std::cin >> odpowiedz;
	switch(odpowiedz){
		case 1:{
			std::cout << "Podaj liczbę elementów sortowanego ciągu: \n";
			std::cin >> odpowiedz;
			Test* test = new Test(0,0,0);
			test->wykonajTest(odpowiedz);
			std::cout << "Wyniki testu: " << test->wyswietlWyniki() <<std::endl;
			break;
		}
		case 2:{
			int begin, end, repeat;
			std::cout << "Uwaga: licznik działa poprawnie jedynie dla zakresu 100-10000, w celu wprowadzenia liczb poniżej 100 lub powyżej 10000 należy zmodyfikować kod źródłowy licznika\n";
			std::cout << "Podaj początkową liczbę elementów: \n";
			std::cin >> begin;
			std::cout << "Podaj końcową liczbę elementów: \n";
			std::cin >> end;
			std::cout << "Podaj liczbę powtórzeń: \n";
			std::cin >> repeat;
			Test* test = new Test(begin, end, repeat);
			test->rozpocznijSerię();
			test->eksportujWyniki("wynikiTestu.txt");
			Regresja* regr = new Regresja("wynikiTestu.txt", "script.gnu");
			regr->wyslijDoGnuplot();
			break;
		}
		default:{

			break;
		}
	}
	return 0;
}
