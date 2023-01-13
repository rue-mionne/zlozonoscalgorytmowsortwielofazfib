#include <cstdlib>
#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include "regresja.h"

void Regresja::wyslijDoGnuplot(){
	std::fstream skryptOut(script);
	skryptOut << "set terminal postscript eps color solid enhanced font \"Times-Roman, 26\"\n"
		  << "set output \"statystykaTest.ps\"\n"
		  << "f(x) = a*x\n"
		  << "fit f(x) \"" << data << "\" u 1:2 via a\n"
		  << "plot f(x) w lines, \"" << data << "\" u 1:2 w points t \'stat\'";
	skryptOut.close();
	pid_t pid;
	pid = fork();
	if(pid == 0){
		execlp("gnuplot", "-c", script.c_str());
	}
	else{
		std::cout << "Wykreślanie wykresu rozpoczęte. Wyniki dostępne w pliku \"statystykaTest.png\"";
	}

}
