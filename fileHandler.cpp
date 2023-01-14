#include <ios>
#include <string>
#include "fileHandler.h"

FileHandler::FileHandler(std::string sciezka){
	this->sciezka=sciezka;
}

void FileHandler::otworzPlik(){
	strumienIn.open(sciezka, std::ios_base::in | std::ios_base::binary);
	strumienOut.open(sciezka, std::ios_base::out |std::ios_base::in| std::ios_base::ate| std::ios_base::binary);
	strumienOut.seekp(0);
	strumienIn.seekg(0);
}

void FileHandler::przesunZapisNaKoniec(){
	std::streampos zapis = strumienIn.tellg();
	strumienOut.seekp(-1, std::ios_base::end);
	strumienIn.seekg(zapis);
}

void FileHandler::resetuj(){
	strumienOut.seekp(0, std::ios_base::beg);//przesuniecie wskaznikow odczytu i zapisu na poczatek
	strumienIn.seekg(0, std::ios_base::beg);
	strumienIn.clear(); //usuniecie ewentualnej flagi konca pliku
}

void FileHandler::zakoncz(){
	strumienIn.close();
	strumienOut.close();
}
