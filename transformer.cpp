#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <utility>
#include <random>



bool loadtokenizer(std::map<std::pair<int, int>, int>& mergeRules,std::vector<std::pair<int, int>>& mergeidx)
{
    std::ifstream file("tokenizer.txt");

    if (!file.is_open())
    {
        std::cout << "Failed to load tokenizer\n";
        return false;
    }
    int a, b, id;
    char plus, equal;
    mergeidx.clear();
    mergeRules.clear();
    while (file >> a >> plus >> b >> equal >> id)
    {

        mergeidx.push_back({a, b});
        mergeRules[{a, b}] = id;
    }
    return true;
}
void embedding(const std::vector<int> &tokens, const std::vector<float> &table, std::vector<float> &output, int dim)
{

    output.resize(tokens.size() * dim);

    for (int t = 0; t < tokens.size(); t++)
    {
        for (size_t d = 0; d < dim; d++)
        {
            output[t * dim + d] = table[tokens[t] * dim + d];
        }
    }
}

void initilize_embeddings(std::vector<float>& table,int dim,int vocab_size){

    std::mt19937 rng(42);
    std::uniform_real_distribution<float> dist(-0.1f,0.1f);

    table.resize(vocab_size*dim);

    for (size_t i = 0; i < table.size(); i++)
    {
       table[i]=dist(rng);
    }
    


}

