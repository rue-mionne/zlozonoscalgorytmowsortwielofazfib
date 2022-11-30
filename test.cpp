#include "test.h"
#include "functionbase.h"
#include "funkcja.h"
#include <string>
#include <cstdlib>

Test::Test(){
	this->funkcja=new Funkcja(wskfunkcja, "test");
}

/*&This Test::operator=(Test*){
	
}*/

void Test::wykonajTest(){
	funkcja->wykonajFunkcje(n);

}


