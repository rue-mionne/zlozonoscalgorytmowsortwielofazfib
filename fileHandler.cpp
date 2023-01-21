#include <string>
#include "fileHandler.h"

//
//konstruktor; przypisanie nazwy pliku do obiektu
//
FileHandler::FileHandler(std::string sciezka){
	this->sciezka=sciezka;
}

//
//otwarcie pliku: stworzenie i ustawienie strumieni zapisu i odczytu
//
void FileHandler::otworzPlik(){
	strumienIn.open(sciezka, std::ios_base::in | std::ios_base::binary);//otwórz strumień odczytu
	strumienOut.open(sciezka, std::ios_base::out |std::ios_base::in| std::ios_base::ate| std::ios_base::binary);//otwórz strumień zapisu
	strumienOut.seekp(0);//ustaw wskaźnik zapisu na początek pliku
	strumienIn.seekg(0);//ustaw wskaźnik odczytu na początek pliku
}
//
//funkcja ustawiająca zapis w pliku na "koniec", to znaczy za ostatni znaczący element, w celu nadpisania "śmieci" - pozostałości po poprzednich zapisach
//
void FileHandler::przesunZapisNaKoniec(){
	int start = strumienIn.tellg();//odczytaj pozycję wskaźnika odczytu
	std::fstream seeker(sciezka);//otwórz dodatkowy strumień, który namierzy i odda pozycję wskaźnika zapisu
	int trash;//zmienna "informująca" strumień, jakie elementy pobiera
	seeker.seekg(start);//ustaw wskaźnik strumienia przeszukującego na początek pliku
	for(int i=0; i<dlugoscPliku;i++){//dopóki nie dotrzesz do ostatniego znaczącego elementu
		seeker >> trash;//pobierz kolejny element i nic z nim nie rób
	}
	int pozycja = seeker.tellg();//pobierz pozycję wskaźnika odczytu strumienia przeszukującego
	seeker.seekp(pozycja);//ustaw na tą pozycję wskaźnik zapisu tego strumienia
	pozycja = seeker.tellp();//pobierz pozycję (tak, z jakiegoś powodu kompilator nie pozwoli zrobić tego prościej) wskaźnika zapisu
	seeker.close(); //zamknij strumień zapisu
	strumienOut.seekp(pozycja+1);//ustaw pozycję wskaźnika zapisu w strumieniu zapisu na "puste" miejsce za ostatnim elementem
}
//
//funkcja stworzona z powodu problemow z zapisem do pliku: funkcja flush() nie spełnia funkcji, przez co żeby treść pliku została zapisana na dysku, strumienie trzeba zamknąć i ponownie otworzyć
//
void FileHandler::odswiez(){
	int temp1 = strumienIn.tellg();//pobierz aktualne pozycje strumieni
	int temp2 = strumienOut.tellp();
	strumienIn.close();//zamknij strumienie
	strumienOut.close();
	otworzPlik();//otwórz strumienie na nowo
	strumienIn.seekg(temp1);//przywróć pozycje wskaźników
	strumienOut.seekp(temp2);
}

//
//funkcja cofająca wskaźniki zapisu i odczytu na początek i resetująca ewentualny wskaźnik błędu końca pliku
//
void FileHandler::resetuj(){
	strumienOut.seekp(0, std::ios_base::beg);//przesuniecie wskaznikow odczytu i zapisu na poczatek
	strumienIn.seekg(0, std::ios_base::beg);
	strumienIn.clear(); //usuniecie ewentualnej flagi konca pliku
}
//
//zamknięcie plików po zakończeniu pracy
//
void FileHandler::zakoncz(){
	strumienIn.close();
	strumienOut.close();
}
