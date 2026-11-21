#pragma once 
#include <iostream>
#include <vector>
#include <map>


inline bool loadtokenizer(std::map<std::pair<int, int>, int>& mergeRules,std::vector<std::pair<int, int>>& mergeidx);



inline void embeddings(std::vector<int> &tokens, std::vector<float> &output, int dim, int vocab_size);

