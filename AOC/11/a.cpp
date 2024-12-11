#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <chrono> 

std::vector<size_t> blink( std::vector<size_t>& input);

int main(){
   std::vector<size_t> input_data{77, 515, 6779622, 6, 91370, 959685, 0, 9861};
   for(size_t i{0}; i < 25; ++i){
      std::cout << i << std::endl;
      input_data = blink(input_data);
   }
   std::cout <<"Result: "<< input_data.size() << std::endl;
   return 0;
}

std::vector<size_t> blink( std::vector<size_t>& input){
   std::vector<size_t> result;
   for(size_t i{0}; i < input.size(); ++i){
      if(input.at(i) == 0){
         result.push_back(1);
         continue;
      }
      if(std::to_string(input.at(i)).length()%2 == 0){
         std::string substr1, substr2;
         substr1 = std::to_string(input.at(i)).substr(0, std::to_string(input.at(i)).length()/2);
         substr2 = std::to_string(input.at(i)).substr(std::to_string(input.at(i)).length()/2, std::to_string(input.at(i)).length()/2);
         result.push_back(stoi(substr1));
         result.push_back(stoi(substr2));
         continue;
      }
      else{
         result.push_back(input.at(i)*2024);
      }
   }
   return result;
}