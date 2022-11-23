#ifndef FAMEW
#define FAMEW
#include <cstdlib>
#include <cstdio>

class Framework{
	private:
	int n;
	int operacje;
	Framework(int ile):n(ile){
		operacje=0;
	}
	public:
	void Testuj(int (*funkcja)(int));
	int ZwrocWynik(){return n;}
};
#endif
