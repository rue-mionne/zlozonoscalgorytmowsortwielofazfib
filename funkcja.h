#ifndef FUNKCJA_H
#define FUNKCJA_H

#include <string>
#include <map>


class IFunkcja{
	public:
		virtual void dodajWynik(int, int)=0;
		virtual void usunWynik(int)=0;
		virtual std::string wypiszWyniki()=0;
};

class Funkcja:public IFunkcja{
	protected:
		int (*cialo)(int);
		std::map<int, int> wynikiDlaFunkcji;
	public:
		std::string nazwa;
		Funkcja(int(*wsk)(int), std::string name):cialo(wsk), nazwa(name){}

		void dodajWynik(int, int) override;
		void usunWynik(int) override;
		std::string wypiszWyniki() override;
};


#endif
