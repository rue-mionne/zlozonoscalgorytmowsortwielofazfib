#include <cstdlib>
#include <vector>

class FunctionAgr{
	private:
		static int operacje;
	public:
		static std::vector<int(*)()> database;
		
}

bool operator<=(int a, int b){
	operacje++;
	return a<=b;
}
