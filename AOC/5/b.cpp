#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <string>

std::vector<int> parse_string_to_vector(const std::string& input_string);
std::unordered_map<int, std::vector<int>> get_input_order(const std::string& filename);
std::vector<std::vector<int>> get_input_rows(const std::string& filename);
bool is_ordered(std::vector<int> line, const std::unordered_map<int, std::vector<int>> lookup);
bool comparator(int a, int b, std::unordered_map<int, std::vector<int>> lookup);

int main(){
   std::vector<std::vector<int>> data_rows = get_input_rows("input_rows");
   std::unordered_map<int, std::vector<int>> lookup = get_input_order("input_order");
   int result{0};
   for(auto& line : data_rows){
      if(!is_ordered(line,lookup)){
         std::sort(line.begin(), line.end(), [lookup](int a, int b){
            return comparator(a, b, lookup);         
         });
         result += line.at((line.size()-1)/2);
      }
   }
   std::cout << "Ergebnis: " << result << std::endl;
   return 0;
}

bool comparator(int a, int b, std::unordered_map<int, std::vector<int>> lookup){
   for(const auto& value : lookup.at(a)){
      if(b == value)
         return true;
   }
   return false;
}

bool is_ordered(std::vector<int> line, std::unordered_map<int, std::vector<int>> lookup){
   bool is_ordered{true};
   std::vector<int> compare{line};
   std::sort(compare.begin(), compare.end(), [lookup](int a, int b){
      return comparator(a, b, lookup);         
   });
   for(size_t i{0}; i < compare.size(); ++i){
      if(compare.at(i) != line.at(i))
         return false;
   }
   return true;  
}

std::vector<int> parse_string_to_vector(const std::string& csv) {
   std::vector<int> values;
   size_t start = 0;
   size_t end = csv.find(",");

   while (end != std::string::npos) {
      values.push_back(std::stoi(csv.substr(start, end - start)));
      start = end + 1;
      end = csv.find(",", start);
   }
   values.push_back(std::stoi(csv.substr(start)));
   return values;
}

std::vector<std::vector<int>> get_input_rows(const std::string& filename){
   std::ifstream input;
   input.open(filename);
   if (!input){
      std::cerr << "Unable to open file: " << filename << std::endl;
      exit(1);
   }
   std::vector<std::vector<int>> result; 
   std::string line_int;
   while(getline(input, line_int)){
      result.push_back(parse_string_to_vector(line_int));
   }
   input.close();
   return result;
}
 
std::unordered_map<int, std::vector<int>> get_input_order(const std::string& filename){
   std::ifstream input;
   input.open(filename);
   if(!input){
      std::cerr << "Unable to open file: " << filename << std::endl;
      exit(1);
   }
   std::unordered_map<int, std::vector<int>> result; 
   std::string line_int;
   while(getline(input, line_int)){
      std::string x, y;
      x = line_int.substr(0,2); 
      y = line_int.substr(3,4);  
      result[stoi(x)].push_back(stoi(y));
   }
   input.close();
   return result;
}
