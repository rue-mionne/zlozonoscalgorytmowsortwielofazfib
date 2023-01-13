#ifndef REGRESJA_H
#define REGRESJA_H
#include <cstdlib>
#include <string>

class Regresja{
	private:
		std::string data;
		std::string script;
	public:
		Regresja(std::string data, std::string script):data(data),script(script){}
		void wyslijDoGnuplot();

};

#endif
