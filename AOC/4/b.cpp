#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>

std::vector<std::string> get_input(const std::string& filename); 

int main(){
   std::vector<std::string> data = get_input("input");
   int result{0};
   for(size_t y{2}; y < data.size(); ++y){
      for(size_t x{2}; x < data.at(y).length(); ++x){
         if(data.at(y-1)[x-1] =='A' && data.at(y)[x] =='S' && data.at(y-2)[x-2] =='M' && data.at(y-2)[x] =='S' && data.at(y)[x-2] =='M') /**/
            result++;
         if(data.at(y-1)[x-1] =='A' && data.at(y)[x] =='M' && data.at(y-2)[x-2] =='S' && data.at(y-2)[x] =='M' && data.at(y)[x-2] =='S') /**/
            result++;
         if(data.at(y-1)[x-1] =='A' && data.at(y)[x] =='M' && data.at(y-2)[x-2] =='S' && data.at(y-2)[x] =='S' && data.at(y)[x-2] =='M') /**/
            result++;
         if(data.at(y-1)[x-1] =='A' && data.at(y)[x] =='S' && data.at(y-2)[x-2] =='M' && data.at(y-2)[x] =='M' && data.at(y)[x-2] =='S') /**/
            result++;
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