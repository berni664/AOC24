#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <gmpxx.h>

struct Node {
  mpz_class value{0};
  bool is_empty{false};
  bool moved{false};
};

std::vector<std::vector<Node>> get_input(const std::string& filename);
std::vector<Node> defragment(std::vector<std::vector<Node>>& input);
mpz_class add_up(std::vector<Node> input);
void print(std::vector<std::vector<Node>>& input);

int main(){
   std::vector<std::vector<Node>> data = get_input("input");
   std::vector<Node> result = defragment(data);
   std::cout << "Ergebnis: " << add_up(result) << std::endl;
   std::cout << std::endl;
   return 0;
}

mpz_class add_up(std::vector<Node> input){
   mpz_class result{0};
   for(size_t i{0}; i < input.size(); ++i){
      if(!input.at(i).is_empty)
         result += input.at(i).value*i;
   }
   return result;
}

std::vector<Node> defragment(std::vector<std::vector<Node>>& input){
   for(size_t i{(input.size()-1)}; i > 0; --i){
      for(size_t j{0}; j < i; ++j){
         if(input.at(j).empty() || input.at(i).empty())
            continue;
         if(input.at(i).size() <= input.at(j).size() && input.at(j).at(0).is_empty && !input.at(i).at(0).is_empty && !input.at(i).at(0).moved){
            size_t dif = input.at(j).size()-input.at(i).size();
            input.at(i).at(0).moved = true;
            input.insert(input.begin() + j, input.at(i));
            for(auto& val : input.at(i+1)){
               val.is_empty = true;
            }
            while(input.at(j+1).size()>dif){
               input.at(j+1).pop_back();
            }     
            break;
         }
      }
   }
   std::vector<Node> result;
   for(const auto& vec : input){
      for(const auto& val : vec){
         result.push_back(val);
      }
   }
   return result;
}

std::vector<std::vector<Node>> get_input(const std::string& filename){
   std::ifstream input;
   input.open(filename);
   if (!input){
      std::cerr << "Unable to open file: " << filename << std::endl;
      exit(1);
   }
   std::vector<std::vector<Node>> result; 
   std::string line_int;
   getline(input, line_int);
   int tracker{0};
   for(size_t j{0}; j < line_int.length(); ++j){
      std::vector<Node> piece;
      for(size_t i{0}; i < line_int[j] - '0'; ++i){
         Node help;
         help.value = tracker;
         help.is_empty = (j%2 != 0);
         piece.push_back(help);
      }
      result.push_back(piece);
      if(j%2 == 0)
         tracker++;
   }
   input.close();
   return result;
}

void print(std::vector<std::vector<Node>>& input){
   for(const auto& vec : input){
      for(const auto& val : vec){
         if(val.is_empty)
            std::cout << ".";
         else
            std:: cout << val.value;
      }
   }
   std::cout << std::endl;
}