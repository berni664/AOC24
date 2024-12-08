#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <unordered_map>

std::vector<std::string> get_input(const std::string& filename);
std::unordered_map<char, std::vector<std::pair<size_t,size_t>>> get_antenna_positions(const std::vector<std::string>& map);

int main(){
   std::vector<std::string> map = get_input("input");
   std::unordered_map<std::string, int> counter;
   std::unordered_map<char, std::vector<std::pair<size_t,size_t>>> tracker = get_antenna_positions(map);
   for(const auto& entry : tracker){
      for(size_t a{0}; a < entry.second.size(); ++a){
         for(size_t b{0}; b < entry.second.size(); ++b){
            if(a!=b){
               int x = entry.second.at(a).first - entry.second.at(b).first;
               int y = entry.second.at(a).second - entry.second.at(b).second;
               x += entry.second.at(a).first;
               y += entry.second.at(a).second;
               if(x >= 0 && x < map.size() && y >= 0 && y < map.at(0).size())
                  counter[std::to_string(x) + "+" + std::to_string(y)]++;
            }
         }
      }
   }
   for(const auto& value : counter){
      std::cout << value.first << std::endl;
   }
   std::cout << counter.size() << std::endl;

   return 0;
}

std::unordered_map<char, std::vector<std::pair<size_t,size_t>>> get_antenna_positions(const std::vector<std::string>& map){
   std::unordered_map<char, std::vector<std::pair<size_t,size_t>>> result;
   for(size_t i{0}; i < map.size(); ++i){
      for(size_t j{0}; j < map.at(i).length(); ++j){
         if(map[i][j] != '.'){
            char ant_pos = map[i][j];
            result[ant_pos].push_back(std::make_pair(i,j));
         }   
      }
   }
   return result;
}

std::vector<std::string> get_input(const std::string& filename){
   std::ifstream input;
   input.open(filename);
   if (!input){
      std::cerr << "Unable to open file: " << filename << std::endl;
      exit(1);
   }
   std::vector<std::string> result; 
   std::string line_int;
   while(getline(input, line_int)){
      result.push_back(line_int);
   }
   input.close();
   return result;
}