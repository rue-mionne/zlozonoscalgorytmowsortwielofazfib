#include "licznik.h"

Timer::Timer(int min_n, int max_n, int repeats){
	range.count=min_n;
	range.start=min_n; 
	range.end=max_n; 
	repeat.amount=repeats;
	repeat.count=0;
}

int Timer::stepRange(){
	if(range.count>=range.end){
		throw new EndOfRangeExc;
	}
	range.count+=100; 
	return range.count;
}

int Timer::stepRepeat(){
	if(repeat.count>=repeat.amount){
		repeat.count=0;
		throw new EndOfRepeatCycle;
	}
	repeat.count++;
	return repeat.count;
}
