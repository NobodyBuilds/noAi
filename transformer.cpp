#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <utility>
#include <random>

bool loadtokenizer(std::map<std::pair<int, int>, int> &mergeRules, std::vector<std::pair<int, int>> &mergeidx)
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

void basic_embedding(std::vector<int> &tokens, const std::vector<float> &table, std::vector<float> &output, int dim)
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

void positon_embeddings(
    std::vector<float> &output,
    const std::vector<float> &posTable,
    int dim)
{
    int seq_len = output.size() / dim;

    for (int t = 0; t < seq_len; t++)
    {
        for (int d = 0; d < dim; d++)
        {

            output[t * dim + d] += posTable[t * dim + d];
        }
    }
}

void calculateQ(
    const std::vector<float>& output,
    const std::vector<float>& Wq,
    std::vector<float>& Q,
    int dim)
{
    int seq_len = output.size() / dim;

    Q.resize(seq_len * dim);

    for (int t = 0; t < seq_len; t++) {
        for (int j = 0; j < dim; j++) {
            float sum = 0;

            for (int k = 0; k < dim; k++) {
                sum+= output[t*dim+k]*Wq[k * dim + j];
            }

            Q[t * dim + j] = sum;
        }
    }
}

void embeddings(std::vector<int> &tokens, std::vector<float> &output, int dim, int vocab_size)
{
    std::vector<float> postable;
    std::vector<float> table;

    std::mt19937 rng(42);
    std::mt19937 rng2(43);
    std::uniform_real_distribution<float> dist(-0.1f, 0.1f);
    size_t n = vocab_size * dim;
    table.resize(n);
    postable.resize(n);
    output.clear();
    for (size_t i = 0; i < table.size(); i++)
    {
        table[i] = dist(rng);
        postable[i] = dist(rng2);
    }

    basic_embedding(tokens, table, output, dim);
    positon_embeddings(output, postable, dim);
}
