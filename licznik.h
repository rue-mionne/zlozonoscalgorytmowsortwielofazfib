#ifndef TIMER_H
#define TIMER_H

#include <iostream>


class Timer{
	struct {
		int start;
		int end;
		int count;
	}range;
	struct{
		int amount;
		int count;
	}repeat;
	public:
		Timer(int, int, int);
		int stepRepeat();
		int stepRange();
		int getRangeCount(){return range.count;}
};

class EndOfRangeExc:public std::exception{
	public:
		char const *what(){
			return "Iteration through samples ended";
		}
};

class EndOfRepeatCycle:public std::exception{
	public:
		char const *what(){
			return "Repeats ended";
		}
};

#endif
