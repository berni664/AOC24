#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <unordered_map>

std::vector<std::string> get_input(const std::string& filename);
std::pair<int,int> get_starting_position(const std::vector<std::string>& mace);
std::vector<std::pair<int,int>> get_path(const std::vector<std::string>& mace);
int get_unique_pairs(std::vector<std::pair<int,int>> tracker);

int main(){
   std::vector<std::string> mace = get_input("input");
   std::vector<std::pair<int,int>> tracker = get_path(mace);
   std::cout << get_unique_pairs(tracker) << std::endl;
   return 0;
}

int get_unique_pairs(std::vector<std::pair<int,int>> tracker){
   int counter{0};
   for(size_t i{0}; i < tracker.size(); ++i){
      bool is_unique{true};
      for(size_t j{0}; j < i; ++j){
         if(tracker.at(i) == tracker.at(j))
            is_unique = false;
      }
      if(is_unique)
         counter++;
   }
   return counter;
}

std::vector<std::pair<int,int>> get_path(const std::vector<std::string>& mace){
   int x{get_starting_position(mace).first}, y{get_starting_position(mace).second};
   int direction{0};
   std::vector<std::pair<int,int>> tracker;
   while(x >= 0 && x < mace.at(0).length() && y >= 0 && y < mace.size()){
      if(direction == 0){ //going up
         if(y == 0)
            return tracker;
         if(mace[y-1][x] != '#'){
            y--;
            tracker.push_back(std::make_pair(x,y));
         }
         else{
            direction = (direction + 1)%4;
         }
      }
      else if(direction == 1){ //going right
         if(x == mace.size()-1)
            return tracker;
         if(mace[y][x+1] != '#'){
            x++;
            tracker.push_back(std::make_pair(x,y));
         }
         else{
            direction = (direction + 1)%4;
         }
      }
      else if(direction == 2){ //going down
         if(y == mace.size()-1)
            return tracker;
         if(mace[y+1][x] != '#'){
            y++;
            tracker.push_back(std::make_pair(x,y));
         }
         else{
            direction = (direction + 1)%4;
         }
      }
      else if(direction == 3){ //going left
         if(y == 0)
            return tracker;
         if(mace[y][x-1] != '#'){
            x--;
            tracker.push_back(std::make_pair(x,y));
         }
         else{
            direction = (direction + 1)%4;
         }
      }
   }
   return tracker;
}

std::pair<int,int> get_starting_position(const std::vector<std::string>& mace){
   int x{0}, y{0};
   for(size_t i{0}; i < mace.size(); ++i){
      for(size_t j{0}; j < mace.at(i).length(); ++j){
         if(mace[i][j] == '^'){
            x = j;
            y = i;
         }
      }
   }
   return std::make_pair(x,y);
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