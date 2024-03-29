#include <cstdlib>
#include <ios>
#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include "regresja.h"

//
//funkcja wykorzystująca gnuplot do wyprodukowania wykresu
//
void Regresja::wyslijDoGnuplot(){
	std::fstream skryptOut(script, std::ios_base::out);//otwórz strumień
	skryptOut << "set terminal postscript eps color solid enhanced font \"Times-Roman, 22\"\n" 
		<< "set ylabel \"Liczba operacji dominujacych\"\n"
		<< "set xlabel \"Liczba elementow (n)\"\n"
		  << "set output \"statystykaTest.ps\"\n"
		  << "f(x) = a*x*log(b*x)/log(2)\n"
		  << "g(x) = x*log(x)/log(2)\n"
		  << "fit f(x) \"" << data << "\" u 1:2 via a,b\n"
		  << "plot g(x) title \'zlozonosc podrecznikowa\' w lines,\\\n"
		  << " 	   f(x) w lines, \"" << data << "\" u 1:2 w points t \'stat\'";
	//zapisz skrypt w pliku
	skryptOut.close();//zamknij plik
	pid_t pid;//wywołanie nowego procesu - uruchomienie skryptu
	pid = fork();
	if(pid == 0){
		execlp("gnuplot", "-c", script.c_str());
	}
	else{
		std::cout << "Wykreślanie wykresu rozpoczęte. Wyniki dostępne w pliku \"statystykaTest.png\"";
	}

}
