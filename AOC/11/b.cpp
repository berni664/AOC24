#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <chrono> 

std::vector<size_t> blink(size_t input);

int main(){
   std::vector<size_t> input_data{77, 515, 6779622, 6, 91370, 959685, 0, 9861};
   std::unordered_map<size_t, size_t> lookup;
   for(auto& value : input_data){
      lookup[value]++;
   }
   for(size_t i{0}; i < 75; ++i){
      std::unordered_map<size_t, size_t> lookup_new;
      for(auto it = lookup.begin(); it != lookup.end(); ++it){
         std::vector<size_t> help = blink(it->first);
         for(const auto& value : help){
           lookup_new[value] += lookup[it->first]; 
         }
      }
      lookup = lookup_new;
   }
   size_t counter{0};
   for(auto it = lookup.begin(); it != lookup.end(); ++it){
      counter += it->second;
   }
   std::cout <<"Result: " << counter << std::endl;
   return 0;
}

std::vector<size_t> blink(size_t input){
   std::vector<size_t> result;
   if(input == 0){
      result.push_back(1);
      return result;
   }
   if(std::to_string(input).length()%2 == 0){
      std::string substr1, substr2;
      substr1 = std::to_string(input).substr(0, std::to_string(input).length()/2);
      substr2 = std::to_string(input).substr(std::to_string(input).length()/2, std::to_string(input).length()/2);
      result.push_back(stoi(substr1));
      result.push_back(stoi(substr2));
      return result;
      }
      else{
         result.push_back(input*2024);
      }
   
   return result;
}