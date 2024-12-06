//schlecht Lösung

#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <set>
#include <unordered_map>
#include <tuple>
#include <chrono> 

std::vector<std::string> get_input(const std::string& filename);
std::pair<int,int> get_starting_position(const std::vector<std::string>& mace);
std::vector<std::tuple<int,int>> get_path(const std::vector<std::string>& mace);
bool is_loop(const std::vector<std::string>& mace);

int main(){
   auto start = std::chrono::high_resolution_clock::now();

   std::vector<std::string> mace = get_input("input");
   int counter{0}, progress{0};
   std::vector<std::tuple<int,int>> path = get_path(mace), path_unique;
   
   for(size_t i{0}; i < path.size(); ++i){
      bool unique{true};
      for(size_t j{0}; j < i; ++j){
         if(std::get<0>(path.at(i)) == std::get<0>(path.at(j)) && std::get<1>(path.at(i)) == std::get<1>(path.at(j))){
            unique = false;   
         }
      }
      if(unique)
         path_unique.push_back(path.at(i));
   }

   for(auto& line: path_unique){
      std::cout << "Progress: " << progress << "/" << path_unique.size()-1 << std::endl;
      std::vector<std::string> mace_copy{mace};
         mace_copy[std::get<1>(line)][std::get<0>(line)] = '#';
         if(is_loop(mace_copy)){
           counter++;
         }
      progress++;
   }

   std::cout << "You could place obstacles in " << counter << " different ways to create a loop!" <<std::endl;
   auto end = std::chrono::high_resolution_clock::now();
   std::chrono::duration<double> elapsed_seconds = end - start;
   std::cout << "This took: " << elapsed_seconds.count() << " seconds\n";

   return 0;
}

bool is_loop(const std::vector<std::string>& mace){
   int x{get_starting_position(mace).first}, y{get_starting_position(mace).second};
   std::unordered_map<std::string, int> lookup;
   int direction{0};
   int counter{0};
   std::vector<std::vector<int>> tracker;
   while(x >= 0 && x < mace.at(0).length() && y >= 0 && y < mace.size()){
      std::vector<int> coordiantes{x,y,direction};
      if(direction == 0){ //going up
         if(y == 0)
            return false;
         if(mace[y-1][x] != '#'){
            y--;
            std::string position = std::to_string(x) + "x" +std::to_string(y) + std::to_string(direction);
            if(lookup.count(position)){
               return true;
            }
            lookup[position]++;
         }
         else{
            direction = (direction + 1)%4;
         }
      }
      else if(direction == 1){ //going right
         if(x == mace.size()-1)
            return false;
         if(mace[y][x+1] != '#'){
            x++;
            std::string position = std::to_string(x) + "x" +std::to_string(y) + std::to_string(direction);
            if(lookup.count(position)){
               return true;
            }
            lookup[position]++;
         }
         else{
            direction = (direction + 1)%4;
         }
      }
      else if(direction == 2){ //going down
         if(y == mace.size()-1)
            return false;
         if(mace[y+1][x] != '#'){
            y++;
            std::string position = std::to_string(x) + "x" +std::to_string(y) + std::to_string(direction);
            if(lookup.count(position)){
               return true;
            }
            lookup[position]++;
         }
         else{
            direction = (direction + 1)%4;
         }
      }
      else if(direction == 3){ //going left
         if(y == 0)
            return false;
         if(mace[y][x-1] != '#'){
            x--;
            std::string position = std::to_string(x) + "x" +std::to_string(y) + std::to_string(direction);
            if(lookup.count(position)){
               return true;
            }
            lookup[position]++;
         }
         else{
            direction = (direction + 1)%4;
         }
      }
   }
   return false;
}


std::vector<std::tuple<int,int>> get_path(const std::vector<std::string>& mace){
   int x{get_starting_position(mace).first}, y{get_starting_position(mace).second};
   int direction{0};
   std::vector<std::tuple<int,int>> tracker;
   while(x >= 0 && x < mace.at(0).length() && y >= 0 && y < mace.size()){
      if(direction == 0){ //going up
         if(y == 0)
            return tracker;
         if(mace[y-1][x] != '#'){
            y--;
            tracker.push_back(std::make_tuple(x,y));
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
            tracker.push_back(std::make_tuple(x,y));
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
            tracker.push_back(std::make_tuple(x,y));
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
            tracker.push_back(std::make_tuple(x,y));
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


