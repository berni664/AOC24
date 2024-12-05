#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>

std::vector<std::string> get_input(const std::string& filename); 

int main(){
   std::vector<std::string> data = get_input("input");
   int result{0};
   for(const auto& line : data){
      for(size_t i{3}; i<line.length(); ++i){
            if(line[i-3] == 'X' && line[i-2] == 'M' && line[i-1] == 'A' && line[i] == 'S')
               ++result;
            if(line[i-3] == 'S' && line[i-2] == 'A' && line[i-1] == 'M' && line[i] == 'X')
               ++result;
         }
   }
   for(size_t i{3}; i < data.size(); ++i){
      for(size_t j{0}; j<data.at(i).length(); ++j){
         if(data.at(i-3)[j] == 'X' && data.at(i-2)[j] == 'M' && data.at(i-1)[j] == 'A' && data.at(i)[j] == 'S')
            ++result;
         if(data.at(i-3)[j] == 'S' && data.at(i-2)[j] == 'A' && data.at(i-1)[j] == 'M' && data.at(i)[j] == 'X')
            ++result;
      }
   }
   for(size_t i{3}; i < data.size(); ++i){
      for(size_t j{3}; j<data.at(i).length(); ++j){
         if(data.at(i-3)[j-3] == 'S' && data.at(i-2)[j-2] == 'A' && data.at(i-1)[j-1] == 'M' && data.at(i)[j] == 'X')
            ++result; 
         if(data.at(i-3)[j-3] == 'X' && data.at(i-2)[j-2] == 'M' && data.at(i-1)[j-1] == 'A' && data.at(i)[j] == 'S')
            ++result;
      }
   }
   for(size_t i{3}; i < data.size(); ++i){
      for(size_t j{0}; j<data.at(i).length()-3; ++j){
         if(data.at(i)[j] == 'S' && data.at(i-1)[j+1] == 'A' && data.at(i-2)[j+2] == 'M' && data.at(i-3)[j+3] == 'X')
            ++result;
         if(data.at(i)[j] == 'X' && data.at(i-1)[j+1] == 'M' && data.at(i-2)[j+2] == 'A' && data.at(i-3)[j+3] == 'S')
            ++result;
      }
   }
    std::cout << "Ergebnis: " << result << std::endl;
    return 0;
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