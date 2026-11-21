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
std::vector<float>output_embeddings;

int main()
{
 int vocab_size=0;
    get_tokens(tokens);

    if(!loadtokenizer(mergeRules,mergeidx)){

         vocab_size =bpe(tokens, mergeRules, mergeidx);
    }else{
       vocab_size= encode(tokens,mergeRules,mergeidx);
    }

   embeddings(tokens,output_embeddings,8,vocab_size);
  

   
}