#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <unordered_map>


struct Node {
  int value{0};
  bool is_empty{false};
};

std::vector<Node> get_input(const std::string& filename);
std::vector<Node> defragment(const std::vector<Node>& input);
size_t add_up(std::vector<Node> input);

int main(){
   std::vector<Node> data = get_input("input");
   data = defragment(data);
   std::cout << add_up(data) <<std::endl;
   return 0;
}

size_t add_up(std::vector<Node> input){
   size_t result{0};
   for(size_t i{0}; i < input.size(); ++i){
      if(!input.at(i).is_empty)
         result += input.at(i).value*i;
   }
   return result;
}

std::vector<Node> defragment(const std::vector<Node>& input){
   size_t i{0}, j{input.size()-1};
   std::vector<Node> result = input;
   while(i < j){
      while(!result.at(i).is_empty)
         ++i; 
      while(result.at(j).is_empty)
         --j;
      if(i < j){
         std::swap(result.at(i), result.at(j));
      }
         
   }
   return result;
}

std::vector<Node> get_input(const std::string& filename){
   std::ifstream input;
   input.open(filename);
   if (!input){
      std::cerr << "Unable to open file: " << filename << std::endl;
      exit(1);
   }
   std::vector<Node> result; 
   std::string line_int;
   getline(input, line_int);
   int tracker{0};
   for(size_t j{0}; j < line_int.length(); ++j){
      for(size_t i{0}; i < line_int[j] - '0'; ++i){
         Node help;
         help.value = tracker;
         help.is_empty = (j%2 != 0);
         result.push_back(help);
      }
      if(j%2 == 0)
      tracker++;
   }
   input.close();
   return result;
}