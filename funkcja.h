#ifndef FUNKCJA_H
#define FUNKCJA_H

#include <string>
#include <map>


class IFunkcja{
	protected:
		virtual void dodajWynik(int, int)=0;
	public:
		virtual int wykonajFunkcje(int)=0;
		virtual void usunWynik(int)=0;
		virtual std::string wypiszWyniki()=0;
};

class Funkcja:public IFunkcja{
	protected:
		int (*cialo)(int);
		std::map<int, int> wynikiDlaFunkcji;
		void dodajWynik(int, int) override;
	public:
		std::string nazwa;
		Funkcja(int(*wsk)(int), std::string name):cialo(wsk), nazwa(name){}
		
		int wykonajFunkcje(int) override;
		void usunWynik(int) override;
		std::string wypiszWyniki() override;
};


#endif
