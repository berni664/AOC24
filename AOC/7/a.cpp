//g++ a.cpp -lgmp -lgmpxx

#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <gmpxx.h>
#include <chrono> 

std::vector<std::vector<mpz_class>> get_input(const std::string& filename);
void generatePermutations(std::vector<std::string>& results, std::string current, int n);
std::vector<std::string> getAllPermutations(int n);
bool is_valid(const std::vector<mpz_class>& input);

int main(){
   auto start = std::chrono::high_resolution_clock::now();
   std::vector<std::vector<mpz_class>> equations = get_input("input");
   std::vector<std::string> perms = getAllPermutations(10);
   mpz_class counter {0};
   int progress{1};
   for(auto& line : equations){
      std::cout << "Progress: " << progress << "/" << equations.size() << std::endl;
      ++progress;
      if(is_valid(line))
         counter += line.at(0);
   }
   std::cout << "Result: " << counter << std::endl;
   auto end = std::chrono::high_resolution_clock::now();
   std::chrono::duration<double> elapsed_seconds = end - start;
   std::cout << "This took: " << elapsed_seconds.count() << " seconds\n";
   return 0;
}

bool is_valid(const std::vector<mpz_class>& input){
   mpz_class target = input.at(0);
   std::vector<std::string> perms = getAllPermutations(input.size()-2);

   for(const auto& perm : perms){
      mpz_class current{input.at(1)};
      size_t j{2};
      for(size_t i{0}; i < perm.length(); ++i){
         if(perm[i] == '*')
            current *= input.at(j); 
         if(perm[i] == '+')
            current += input.at(j);
         j++; 
         if(current > target)
            break;
      }
      if(current == target)
         return true;
   }
   return false;
}

std::vector<std::vector<mpz_class>> get_input(const std::string& filename){
   std::vector<std::vector<mpz_class>> result;
   std::string line;
   std::ifstream input;
   input.open(filename);
   while (std::getline(input, line)) {
      std::istringstream iss(line);
      std::string temp;
      std::vector<mpz_class> row;
      mpz_class firstNum;
      char colon;
      iss >> firstNum >> colon;
      row.push_back(firstNum);
      mpz_class num;
      while (iss >> num) {
         row.push_back(num);
      }
      result.push_back(row);
    }

   return result;
}

void generatePermutations(std::vector<std::string>& results, std::string current, int n) {
    if (current.length() == n) {
        results.push_back(current);
        return;
    }

    generatePermutations(results, current + "+", n);
   
    generatePermutations(results, current + "*", n);
}


std::vector<std::string> getAllPermutations(int n) {
    std::vector<std::string> results;
    generatePermutations(results, "", n);
    return results;
}
