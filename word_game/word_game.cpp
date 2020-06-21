// word_game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <random>
#include <algorithm>

bool vector_contains_string(const std::vector<std::string>& string_vector, const std::string& string)
{
    for (std::string s : string_vector)
    {
        if (s == string)
        {
            return true;
        }
    }
    return false;
}

std::vector<int> get_buffets(const std::string& word)
{
    std::vector<int> buffet(26,0);
    for (char c : word)
    {
        buffet[c - 'a']++;
    }
    return buffet;
}



int calculate_score(const std::string& word1, const std::string& word2)
{
    int score = 0;
    std::vector<int> buffet1 = get_buffets(word1);
    std::vector<int> buffet2 = get_buffets(word2);
    
    for (int i = 0; i < 26; i++)
    {
        score += std::min(buffet1[i], buffet2[i]);
    }
    
    for (int i = 0; i < 5; i++)
    {
        if (word1[i] == word2[i])
        {
            score++;
        }
    }  
    
    return score;
}


int main()
{
    std::vector<std::string> five_words;
    std::vector<std::string> common_words;
    {
        // load the file
        std::ifstream five_words_file("sgb-words.txt");
        for (std::string line; getline(five_words_file, line);)
        {
            five_words.push_back(line);
        }
    }
    {
        std::ifstream common_words_file("20k.txt");
        for (std::string line; std::getline(common_words_file, line);)
        {
            if (line.size() == 5)
            {
                common_words.push_back(line);
            }
        }
    }


    // Get the word 
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int>dist(0, five_words.size());
    std::string goal;

    do 
    {
          goal = five_words[dist(rng) - 1]; 
         std::cout << goal << std::endl;
    }while( !(vector_contains_string(common_words, goal)) );

    while (1)
    {
        std::string input;
        std::cout << "Enter 5 letter word..   ";
        std::cin >> input;

        if (input.size() != 5)
        {
            std::cout << "Write 5 letters you fucken mongul.." << std::endl << std::endl;
            continue;
        }

        if (!vector_contains_string(five_words, input))
        {
            std::cout << "That's not a fucken word , bitch!" << std::endl << std::endl;
            continue;
        }

       const int score = calculate_score(goal, input);
       if (score == 10)
       {
           std::cout << "Wow.. You did it!" << std::endl;
           break;
       }
       std::cout << "Score is ..  " << score << "  Nice try.." << std::endl;
     
    }


    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.clear();
    getchar();
}

