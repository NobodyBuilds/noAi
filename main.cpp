#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <utility>
#include <random>
#include "tokenizer.h"
#include "transformer.h"

std::map<std::pair<int, int>, int> mergeRules;
std::vector<std::pair<int, int>> mergeidx;
std::vector<int> tokens;
std::vector<float> table;

int main()
{
 int vocab_size=0;
    get_tokens(tokens);

    if(!loadtokenizer(mergeRules,mergeidx)){

         vocab_size =bpe(tokens, mergeRules, mergeidx);
    }else{
       vocab_size= encode(tokens,mergeRules,mergeidx);
    }

    initilize_embeddings(table,8,vocab_size);
    std::vector<float>output;
   embedding(tokens,table,output,8);

    
}