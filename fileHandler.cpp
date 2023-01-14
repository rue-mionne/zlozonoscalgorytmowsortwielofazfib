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
	std::fstream seeker(sciezka);
	int trash;
	for(int i=0; i<dlugoscPliku;i++){
		seeker >> trash;
	}
	int pozycja = seeker.tellg();
	seeker.seekp(pozycja);
	pozycja = seeker.tellp();
	seeker.close();
	strumienOut.seekp(pozycja+1);
}

void FileHandler::odswiez(){
	int temp1 = strumienIn.tellg();
	int temp2 = strumienOut.tellp();
	strumienIn.close();
	strumienOut.close();
	otworzPlik();
	strumienIn.seekg(temp1);
	strumienOut.seekp(temp2);
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
