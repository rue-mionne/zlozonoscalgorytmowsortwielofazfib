#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <fstream>
#include <string>

class FileHandler{
	private:
		std::string sciezka;
		std::fstream strumien;

		int dlugoscPliku;
		int wielkoscBloku;
	public:
		FileHandler(std::string);
		void otworzPlik();
		void przesunOdczytOJeden();
		void przesunZapisNaKoniec();
		void resetuj();
		void zakoncz();
		void setDlugoscPliku(int dlugosc){dlugoscPliku=dlugosc;}
		void setWielkoscBloku(int wielkosc){wielkoscBloku=wielkosc;}
};

#endif
