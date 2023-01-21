#include "test.h"
#include "fileHandler.h"
#include "itestable.h"
#include "licznik.h"
#include "sortowanieWieloFib.h"
#include <cstdio>
#include <ios>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <ctime>

//
//konstruktor testu: inicjacja licznika i plików docelowych
//
Test::Test(int start, int koniec, int repeats):licznik(new Timer(start, koniec, repeats)){
	pliki[0] = "pliki/plik1";
	pliki[1] = "pliki/plik2";
	pliki[2] = "pliki/plik3";
	pliki[3] = "pliki/plik4";
}
//
//funkcja wywołująca pojedynczy test
//
void Test::wykonajTest(int n){
	prepareData(n);//przygotuj pliki pod test
	algorytm= new SortowanieWieloFib(n, pliki);//inicjacja algorytmu
	algorytm->start();//rozpoczęcie algorytmu
	delete algorytm;//zwolnij miejsce po obiekcie algorytmu

}

//
//funkcja przygotowująca pliki pod test algorytmu
//
void Test::prepareData(int n){
	std::fstream egzekutor;//strumień kasujący poprzednią zawartość pliku i zapełniający losowymi liczbami
	for(int i=0;i<4;i++){
		egzekutor.open(pliki[i], std::ios_base::out | std::ios_base::trunc);//otwarcie pliku w trypie kasującym zawartość
		egzekutor.close();//zamknij pliki
	}
	int liczbaPseudoLosowa;//pojemnik na wylosowaną liczbę
	egzekutor.open(pliki[3], std::ios_base::out|std::ios_base::binary);//otwórz czwarty plik do zapisu
	for(int i=0;i<n;i++){
		liczbaPseudoLosowa =((rand())%1000);//wylosuj liczbę z zakresu 0-1000
		egzekutor << liczbaPseudoLosowa << " ";//zapisz wylosowaną liczbę do pliku
	}
	egzekutor.close();//zamknij plik
}

//
//funkcja zapewniająca obsługę serii testów
//
void Test::rozpocznijSerię(){
	try{
		while(true){//nieskończona pętla, sterowana licznikiem
			try{
				while(true){
					algorytm=new SortowanieWieloFib(licznik->getRangeCount(),pliki);	//inicjuj algorytm dla danej liczby elementów
					prepareData(licznik->getRangeCount());//przygotuj pliki dla danej ilości elementów
					algorytm->start();//wykonaj algorytm
					delete algorytm;//usuń obiekt algorytmu
					licznik->stepRepeat();//przejdź do kolejnego powtórzenia lub bezwględnie przerwij
				}
			}
			catch(EndOfRepeatCycle* e){//punkt wyjścia z pętli powtórzeń
			}
			licznik->stepRange();//przejdź do kolejnej liczby elementów lub bezwględnie przerwij
		}
	}
	catch(EndOfRangeExc* e){//punkt wyjścia z pętli ilości elementów testowanych
	}
}

//
//funkcja zwracająca wyniki testów w wersji tekstowej
//
std::string Test::wyswietlWyniki(){
	std::map<int, int*>* temp = Itestable::zwrocWynikiAnalizyAlg();//pobierz mapę z wynikami
	std::map<int,int*>::iterator it;//iterator(wskaźnik) poruszający się po mapie
	std::string wyniki;//tekst wynikowy
	std::stringstream strumien; //strumień łączący wyniki w tekst
	for(it=temp->begin(); it!=temp->end(); it++){//przejdź przez całą mapę
		int* tab=it->second;//pobierz tablicę będącą drugim elementem mapy
		strumien << tab[0] << " " << tab[1] << "\n";//zapisz jej elementy w formacie testowym
	}
	std::getline(strumien,wyniki,',');//przepisz całą zawartość strumienia do zmiennej tekstowej
	return wyniki;//zwróć tekst wynikowy
}

//
//zapisz wyniki testów do pliku
//
void Test::eksportujWyniki(std::string sciezka){
	std::fstream zapis(sciezka,std::ios_base::out|std::ios_base::trunc);//otwórz plik do zapisu
	zapis << wyswietlWyniki();//zapisz wyniki w formie tekstowej do pliku
}
