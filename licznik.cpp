#include "licznik.h"
#include <iostream>

Timer::Timer(int min_n, int max_n, int repeats){
	range.count=min_n;
	range.start=min_n; 
	range.end=max_n; 
	repeat.amount=repeats;
	repeat.count=1;
}

int Timer::stepRange(){
	if(range.count>=range.end){
		throw new EndOfRangeExc;
	}
	if(range.count<1000){
		range.count+=100;
		std::cout << "up\n";
	}
	else if(range.count<10000)
		range.count+=1000;
	return range.count;
}

int Timer::stepRepeat(){
	if(repeat.count>=repeat.amount){
		repeat.count=1;
		throw new EndOfRepeatCycle;
	}
	repeat.count++;
	return repeat.count;
}
