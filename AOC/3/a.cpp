#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>

std::string get_input(const std::string& filename); 
std::vector<int> get_mults(std::string line);

int main(){
    int result{0};
    std::string inputs = get_input("input");
    std::vector<int> mults = get_mults(inputs);
    for(size_t i{0}; i < mults.size(); i+=2){
      result += mults.at(i) * mults.at(i+1);
    }
    std::cout << "Ergebnis: " << result << std::endl;
    return 0;
}

std::string get_input(const std::string& filename){
    std::ifstream input;
    input.open(filename);
    if (!input){
        std::cerr << "Unable to open file: " << filename << std::endl;
        exit(1);
    }
    std::string line_int, line_result;
    while(getline(input, line_int)){
        line_result += line_int; 
    }
    line_result = line_result + "            ";
    input.close();
    return line_result;
}

std::vector<int> get_mults(std::string line){
   std::vector<int> result;
      for(std::string::size_type i = 3; i < line.size()-4; ++i) {
         bool is_enabled{true};
         if(line[i-3] == 'm' && line[i-2] == 'u' && line[i-1] == 'l' && line[i] == '(' && is_enabled){
            size_t j{1};
            std::string x, y;
            bool is_valid{true};
            while('0' <= line[i+j] && line[i+j] <= '9' && j < 4 && i+j < line.size()){
               x = x+line[i+j];
               j++;
            }
            if(line[i+j] != ','){
               is_valid = false;
            }
            j++;
            while('0' <= line[i+j] && line[i+j] <= '9' && j < 8 && i+j < line.size()){
               y = y+line[i+j];
               j++;
            }
            if(line[i+j] != ')'){
               is_valid = false;
            }
            if(is_valid && y.length() != 0){
               result.push_back(stoi(x));
               result.push_back(stoi(y));
            }
         }       
      }
   
   return result;
}