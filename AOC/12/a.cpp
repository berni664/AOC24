#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <chrono> 

std::vector<std::unordered_set<int>> get_adj_lists(const std::string& filename);
bool dfs(const std::vector<std::vector<int>>& adj_list, int current, int target, std::unordered_set<int>& visited);
bool are_nodes_connected(const std::vector<std::vector<int>>& adj_list, int start, int target);
std::vector<std::string> get_input(const std::string& filename);
std::vector<std::vector<int>> get_adj_list_whole(const std::vector<std::string>& mace);
int get_fence_count(int coordinate, std::vector<std::string> map);



int main(){
   std::vector<std::unordered_set<int>> adj_lists = get_adj_lists("input");
   std::vector<std::string> map = get_input("input");
   int cost{0};
   for(const auto& set : adj_lists){
      int fence_count{0};
      for(const auto& entry : set){
         fence_count += get_fence_count(entry, map);
      }
      cost += set.size()*fence_count;
   }
   std::cout <<"Result: " << cost << std::endl;
   return 0;
}

std::vector<std::unordered_set<int>> get_adj_lists(const std::string& filename){
   std::vector<std::string> map = get_input(filename);
   std::vector<std::vector<int>> adj_list = get_adj_list_whole(map);
   std::unordered_set<int> lookup_all;
   std::vector<std::unordered_set<int>> result;
   for(int i{0}; i < adj_list.size(); ++i){
      std::cout << i << "/" << adj_list.size() << std::endl;
      std::unordered_set<int> subgraph;
      if(!lookup_all.count(i)){
         for(int j{0}; j < adj_list.size(); ++j){
            if(are_nodes_connected(adj_list, i, j)){
               subgraph.insert(i);
               subgraph.insert(j);
               lookup_all.insert(i);
               lookup_all.insert(j);
            }
         }
      }
      result.push_back(subgraph);
   }
   return result;
}

int get_fence_count(int coordinate, std::vector<std::string> map){
   int horizontal, vertikal;
   horizontal = coordinate % map.at(0).length(); 
   vertikal = coordinate / map.at(0).length(); 
   int counter{0};
   for(int offset_v{-1}; offset_v < 2; ++ offset_v){
      for(int offset_h{-1}; offset_h < 2; ++ offset_h){
         int new_v{vertikal + offset_v}, new_h{horizontal+ offset_h};
         if(new_h >= 0 && new_h < map.at(0).size() && new_v >= 0 && new_v < map.size() && (offset_v + offset_h == 1 || offset_v + offset_h == -1)){
            if(map[vertikal][horizontal] != map[new_v][new_h])
               counter++;
         }
      }
   }
   if(vertikal == 0 || vertikal == map.size()-1)
      counter++;
   if(horizontal == 0 || horizontal == map.at(0).size()-1)
      counter++;
   return counter;
}

std::vector<std::vector<int>> get_adj_list_whole(const std::vector<std::string>& mace){
   std::vector<std::vector<int>> result;
   for(int vertical{0}; vertical < mace.size(); ++vertical){
      for(int horizontal{0}; horizontal < mace.at(vertical).size(); ++horizontal){
         std::vector<int> adj;
         for(int offset_v{-1}; offset_v < 2; ++ offset_v){
            for(int offset_h{-1}; offset_h < 2; ++ offset_h){
               int new_v{vertical + offset_v}, new_h{horizontal+ offset_h};
               if(new_h >= 0 && new_h < mace.at(vertical).size() && new_v >= 0 && new_v < mace.size() && (offset_v + offset_h == 1 || offset_v + offset_h == -1)){
                  if(mace[vertical][horizontal] == mace[new_v][new_h])
                     adj.push_back(new_v*mace.at(vertical).size()+new_h);
               }
            }
         }
         result.push_back(adj);
      }
   }
   std::cout << "check adj_list\n";
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
   std::string line;
   while(getline(input, line)){
      result.push_back(line);
   }
   return result;
}

bool dfs(const std::vector<std::vector<int>>& adj_list, int current, int target, std::unordered_set<int>& visited) {
   if (current == target) 
      return true;
   visited.insert(current);
   for(int neighbor : adj_list.at(current)){
      if(visited.find(neighbor) == visited.end()){ 
         if(dfs(adj_list, neighbor, target, visited)) 
            return true;
      }
   }
   return false;
}

bool are_nodes_connected(const std::vector<std::vector<int>>& adj_list, int start, int target){
    std::unordered_set<int> visited;
    return dfs(adj_list, start, target, visited);
}