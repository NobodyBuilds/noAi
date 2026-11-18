#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <utility>

using namespace std;

std::map<std::pair<int, int>, int> mergeRules;
std::vector<std::pair<int, int>> mergeidx;

void pairing(vector<int> &tokens)
{
    std::map<std::pair<int, int>, int> counts;
    for (size_t r = 0; r < 5; r++)
    {
        if (tokens.size() < 2)
            break;

        int m_id = 256 + r;

        counts.clear();
        for (size_t i = 0; i + 1 < tokens.size(); i++)
        {
            int a = tokens[i];
            int b = tokens[i + 1];

            counts[std::make_pair(a, b)]++;
        }

        int maxcount = 0;
        std::pair<int, int> bestPair = {0, 0};

        for (const auto &entry : counts)
        {
            if (entry.second > maxcount)
            {
                maxcount = entry.second;
                bestPair = entry.first;
            }
        }
        if (maxcount < 2)
            break;
        mergeRules[bestPair] = m_id;
        mergeidx.push_back(bestPair);
        // merging
        std::vector<int> merged;

        for (size_t i = 0; i < tokens.size(); i++)
        {
            int a = tokens[i];

            bool doesnt_exists = i + 1 >= tokens.size();
            int b = (!doesnt_exists) ? tokens[i + 1] : 0;

            if (a == bestPair.first && b == bestPair.second && !doesnt_exists)
            {
                merged.push_back(m_id);
                i++;
            }
            else
            {
                merged.push_back(a);
            }
        }

        tokens = merged;
    }
}

void encode(std::vector<int> &tokens)
{
    for (int m = 0; m < mergeidx.size(); m++)
    {
        std::pair<int, int> m_pair = {mergeidx[m].first, mergeidx[m].second};

        std::vector<int> merged;
        for (size_t i = 0; i < tokens.size(); i++)
        {

            int a = tokens[i];

            bool out_of_bound = i + 1 >= tokens.size();
            int b = out_of_bound ? 0 : tokens[i + 1];
            std::pair<int, int> t_pair = {a, b};
            if (t_pair == m_pair && !out_of_bound)
            {
                int id = mergeRules.at({a, b});
                merged.push_back(id);
                i++;
            }
            else
            {
                merged.push_back(a);
            }
        }
        tokens = merged;
    }
}

void decode(std::vector<int> &tokens)
{
    for (int m = static_cast<int>(mergeidx.size()) - 1; m >= 0; m--)
    {
        std::pair<int, int> m_pair = {mergeidx[m].first, mergeidx[m].second};

        int id = mergeRules[m_pair];

        std::vector<int> dmerge;

        for (int i = 0; i < tokens.size(); i++)
        {
            int a = tokens[i];

            if (a == id)
            {
                dmerge.push_back(mergeidx[m].first);
                dmerge.push_back(mergeidx[m].second);
            }
            else
            {
                dmerge.push_back(a);
            }
        }
        tokens = dmerge;
    }
}
int main()
{

    ifstream file("data.txt", std::ios::binary);

    if (!file.is_open())
    {
        printf("failed to open files \n");
        return 1;
    }
    string text;
    string line;

    while (std::getline(file, line))
    {
        text += line;
        text += '\n';
    }

    vector<int> tokens;
    for (size_t i = 0; i < text.size(); i++)
    {
        int id = static_cast<unsigned char>(text[i]);
        tokens.push_back(id);
    }
    for (size_t i = 0; i < text.size(); i++)
    {
        std::cout << text[i];
    }
    pairing(tokens);
    encode(tokens);
    for (size_t i = 0; i < tokens.size(); i++)
    {
        std::cout << tokens[i] << '\n';
    }
    std::cout << "decoded \n";
    decode(tokens);

    std::string d_text = "";
    for (int id : tokens)
    {
        d_text += static_cast<char>(id);
    }
    for (size_t i = 0; i < d_text.size(); i++)
    {
        std::cout << d_text[i];
    }
}