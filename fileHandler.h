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
		std::fstream strumienIn;
		std::fstream strumienOut;
		FileHandler(std::string);
		void otworzPlik();
		void przesunZapisNaKoniec();
		void resetuj();
		void zakoncz();
		void setDlugoscPliku(int dlugosc){dlugoscPliku=dlugosc;}
		void setWielkoscBloku(int wielkosc){wielkoscBloku=wielkosc;}
		int getDlugoscPliku(){return dlugoscPliku;}
		int getWielkoscBloku(){return wielkoscBloku;}
};

#endif
