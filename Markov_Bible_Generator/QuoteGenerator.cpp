#include <time.h>
#include <vector>
#include <map>

#include "QuoteGenerator.h"
#include "MarkovChainGenerator.h"

void generateQuote(std::string first_word, int length)
{
	std::string current_word = first_word;
	std::cout << current_word << ' ';
	srand(time(NULL));

	std::map<std::string, double*> markov_chain = generateMarkovChain();
	
	for (int i = 0; i < length; i++) //generating whole Quote
	{
		double roll = (double)rand() / (double)RAND_MAX;
		double chance=0;
		int j = 0;
		while (chance < roll) //generating word
		{
			chance += markov_chain.find(current_word)->second[j];
			j++;
		}
		j--;
		auto it = markov_chain.begin();
		for (int i = 0; i < j; i++) it++;
		std::cout << it->first << ' ';
		current_word = it->first;
	}
}