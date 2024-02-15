#include "file_loader.h"
#include <fstream>

std::map<std::string, int> readFile(std::string txtPath)
{
	std::fstream file;
	std::string whole_text, line;
	std::map<std::string, int> markov_set;

	file.open(txtPath);
	if (file.good()){
		while (!file.eof()) {
			file >> line;
			formatText(line);
			markov_set.insert(line);
		}
	}
	else {
		std::cout << "Failed to load file: " << txtPath << std::endl;
	}
	return markov_set;
}

void formatText(std::string &text)
{
	for (auto i = text.begin(); i < text.end(); i++) {
		if (*i >= 'A' && *i <= 'Z') *i += 32;
		else if (*i >= '!' && *i <= '/') {
			text.pop_back();
			i--;
		}
	}
}