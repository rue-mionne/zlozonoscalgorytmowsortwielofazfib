#ifndef ITESTABLE_H
#define ITESTABLE_H

#include <map>

class Itestable{
	protected:
		static std::map<int,int*> wynikiAlgorytmu;
		static int id;
		int count;
		int n;
		bool lt(int, int);
		bool le(int, int);
		bool gt(int, int);
		bool ge(int, int);
		bool eq(int, int);
		bool ne(int, int);
		void zakonczAlg();
	public:
		virtual void start()=0;
		int getn(){return n;}
		int getCount(){return count;}
		static std::map<int,int*>* zwrocWynikiAnalizyAlg();
};

#endif
