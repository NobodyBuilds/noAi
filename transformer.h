#pragma once 
#include <iostream>
#include <vector>
#include <map>


inline bool loadtokenizer(std::map<std::pair<int, int>, int>& mergeRules,std::vector<std::pair<int, int>>& mergeidx);



inline void embedding(const std::vector<int> &tokens, const std::vector<float> &table, std::vector<float> &output, int dim);


inline void initilize_embeddings(std::vector<float>& table,int dim,int vocab_size);
