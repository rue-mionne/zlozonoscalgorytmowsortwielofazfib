#ifndef BAZA_F_H
#define BAZA_F_H

#include <cstdlib>
#include <string>
#include <map>

extern std::map<std::string, int(*)()> baza_funkcji;

void inicjujBazeFunkcji();

#endif
