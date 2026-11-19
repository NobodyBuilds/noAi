#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <utility>
#include <random>
#include "tokenizer.h"

std::map<std::pair<int, int>, int> mergeRules;
std::vector<std::pair<int, int>> mergeidx;
std::vector<int> tokens;
std::vector<float> table;

int main()
{

    get_tokens(tokens);

    int vocab_size =bpe(tokens, mergeRules, mergeidx);

    save_tokenizer(mergeRules,mergeidx);

    
}