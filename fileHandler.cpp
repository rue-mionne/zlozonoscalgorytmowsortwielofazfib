#include <ios>
#include <string>
#include "fileHandler.h"

FileHandler::FileHandler(std::string sciezka){
	this->sciezka=sciezka;
}

void FileHandler::otworzPlik(){
	strumien.open(sciezka, std::ios_base::in | std::ios_base::out | std::ios_base::binary);
	strumien.seekp(0);
	strumien.seekg(0);
}

void FileHandler::przesunZapisNaKoniec(){
	strumien.seekp(0, std::ios_base::end);
}

void FileHandler::resetuj(){
	strumien.seekp(0, std::ios_base::beg);//przesuniecie wskaznikow odczytu i zapisu na poczatek
	strumien.seekg(0, std::ios_base::beg);
	strumien.clear(); //usuniecie ewentualnej flagi konca pliku
}

void FileHandler::zakoncz(){
	strumien.close();
}
