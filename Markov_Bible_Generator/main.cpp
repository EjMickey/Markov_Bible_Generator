#include <iostream>
#include "file_loader.h"
#include <set>

using namespace std;

int main()
{
	std::set<std::string> s = readFile("C:\\Users\\Miko³aj\\source\\repos\\Markov_Bible_Generator\\Markov_Bible_Generator\\Bible.txt");
	for (auto i = s.begin(); i != s.end(); i++) {
		std::cout << *i << endl;
	}
	return 0;
}