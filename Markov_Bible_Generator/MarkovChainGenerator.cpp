#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include "MarkovChainGenerator.h"

std::map<std::string, double*> generateMarkovChain()
{
	std::string whole_text{ "" };
	std::map<std::string, double*> markov_chain;
	std::map<std::string, int> word_list = generateWordList(whole_text);
	std::string first_word, second_word;
	int first_word_pos, second_word_pos;
	std::stringstream ss(whole_text);

	for (auto it = word_list.begin(); it != word_list.end(); it++)
	{
		double* probs = new double[word_list.size()];
		for (int i = 0; i < word_list.size(); i++) probs[i] = 0;
		markov_chain.insert(std::pair<std::string, double*>(it->first, probs));
	}
	ss >> first_word;
	while (ss >> second_word)
	{
		int i = 0;
		for (auto it = markov_chain.begin(); it != markov_chain.end(); it++)
		{
			if (it->first == second_word) break;
			i++;
		}
		markov_chain.find(first_word)->second[i]++;
		first_word = second_word;
	}

	std::map<std::string, int>::iterator jt = word_list.begin();
	for (auto it = markov_chain.begin(); it != markov_chain.end(); it++, jt++)
	{
		for (int i = 0; i < markov_chain.size(); i++) it->second[i] /= jt->second;
	}
	return markov_chain;
}

std::map<std::string, int> generateWordList(std::string& whole_text)
{
	std::fstream file;
	std::string word, line;
	std::stringstream ss;
	std::string txt_path = "C:\\Users\\Miko³aj\\source\\repos\\Markov_Bible_Generator\\Markov_Bible_Generator\\Bible.txt";
	std::map<std::string, int> word_list;

	file.open(txt_path);
	if (file.good()) {
		std::map<std::string, int>::iterator it;
		while (getline(file, line))
		{
			formatText(line);
			ss = std::stringstream(line);
			
			while (ss >> word)
			{
				whole_text.append(word + ' ');
				it = word_list.find(word);
				if (it == word_list.end()) word_list.insert(std::pair<std::string, int>(word, 1));
				else it->second++;
			}
		}
		it->second--;
	}
	else {
		std::cout << "Failed to load file: " << txt_path << std::endl;
	}
	file.close();
	return word_list;
}

void formatText(std::string& text)
{
	for (int i = 0; i < text.length(); i++) {
		if (text[i] >= 'A' && text[i] <= 'Z') text[i] = tolower(text[i]); //Making lowercases
		if (text[i] >= '!' && text[i] <= '@') {//Deleting non-letters
			text.erase(text.begin() + i);
			i--;
		}
	}
}