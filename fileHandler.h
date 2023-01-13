#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <fstream>
#include <string>

class FileHandler{
	private:
		std::string sciezka;
		int dlugoscPliku;
		int wielkoscBloku;
	public:
		std::fstream strumien;
		FileHandler(std::string);
		void otworzPlik();
		void przesunOdczytOJeden(); //prawdopodobnie niepotrzebna funkcja! zajrzeć do sympfonii i sprawdzić jak operatory << >> traktują niepasujące dane
		void przesunZapisNaKoniec();
		void resetuj();
		void zakoncz();
		void setDlugoscPliku(int dlugosc){dlugoscPliku=dlugosc;}
		void setWielkoscBloku(int wielkosc){wielkoscBloku=wielkosc;}
		int getDlugoscPliku(){return dlugoscPliku;}
		int getWielkoscBloku(){return wielkoscBloku;}
};

#endif
