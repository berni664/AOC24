#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>

std::vector<std::vector<int>> get_input(const std::string& filename);
std::vector<std::vector<int>> get_adj_list(const std::vector<std::vector<int>>& mace);
void count_paths_dfs(const std::vector<std::vector<int>>& adj_list, int current, int target, std::unordered_set<int>& visited, int& path_count);
int count_distinct_paths(const std::vector<std::vector<int>>& adj_list, int start, int target);
std::vector<int> get_starting_pos(const std::vector<std::vector<int>>& mace);
std::vector<int> get_end_pos(const std::vector<std::vector<int>>& mace);


int main(){
   std::vector<std::vector<int>> mace = get_input("input");
   std::vector<std::vector<int>> adj_list = get_adj_list(mace);
   std::vector<int> start_pos{get_starting_pos(mace)}, end_pos{get_end_pos(mace)};
   int counter{0};
   for(auto& start : start_pos){
      for(auto& target : end_pos){
         counter += count_distinct_paths(adj_list, start, target);
      }
   }
   std::cout << "Result: " << counter << std::endl;

   return 0;
}

std::vector<std::vector<int>> get_input(const std::string& filename){
   std::ifstream input;
   input.open(filename);
   if (!input){
      std::cerr << "Unable to open file: " << filename << std::endl;
      exit(1);
   }
   std::vector<std::vector<int>> result; 
   std::string line_int;
   while(getline(input, line_int)){
      std::vector<int> help;
      for(const auto& num : line_int){
        help.push_back(num - '0'); 
      }
      result.push_back(help);
   }
   return result;
}

std::vector<std::vector<int>> get_adj_list(const std::vector<std::vector<int>>& mace){
   std::vector<std::vector<int>> result;
   for(int vertical{0}; vertical < mace.size(); ++vertical){
      for(int horizontal{0}; horizontal < mace.at(vertical).size(); ++horizontal){
         std::vector<int> adj;
         for(int offset_v{-1}; offset_v < 2; ++ offset_v){
            for(int offset_h{-1}; offset_h < 2; ++ offset_h){
               int new_v{vertical + offset_v}, new_h{horizontal+ offset_h};
               if(new_h >= 0 && new_h < mace.at(vertical).size() && new_v >= 0 && new_v < mace.size() && (offset_v + offset_h == 1 || offset_v + offset_h == -1)){
                  if(mace[vertical][horizontal] + 1 == mace[new_v][new_h])
                     adj.push_back(new_v*mace.at(vertical).size()+new_h);
               }
               
            }
         }
         result.push_back(adj);
      }
   }
   return result;
}

void count_paths_dfs(const std::vector<std::vector<int>>& adj_list, int current, int target, std::unordered_set<int>& visited, int& path_count) {
   if(current == target){
      path_count++;
      return;
   }
   visited.insert(current);
   for(int neighbor : adj_list.at(current)){
      if(visited.find(neighbor) == visited.end()){
         count_paths_dfs(adj_list, neighbor, target, visited, path_count);
      }
   }
   visited.erase(current);
}

int count_distinct_paths(const std::vector<std::vector<int>>& adj_list, int start, int target){
   std::unordered_set<int> visited;
   int path_count = 0;
   count_paths_dfs(adj_list, start, target, visited, path_count);
   return path_count;
}

std::vector<int> get_starting_pos(const std::vector<std::vector<int>>& mace){
   std::vector<int> result;
   for(size_t i{0}; i < mace.size(); ++i){
      for(size_t j{0}; j < mace.at(i).size(); ++j){
         if(mace.at(i).at(j) == 0)
            result.push_back(i*mace.at(i).size()+j);
      }
   }
   return result;
}

std::vector<int> get_end_pos(const std::vector<std::vector<int>>& mace){
   std::vector<int> result;
   for(size_t i{0}; i < mace.size(); ++i){
      for(size_t j{0}; j < mace.at(i).size(); ++j){
         if(mace.at(i).at(j) == 9)
            result.push_back(i*mace.at(i).size()+j);
      }
   }
   return result;
}