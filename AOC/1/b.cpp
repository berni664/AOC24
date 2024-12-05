#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <unordered_map>

std::pair<std::vector<int>, std::vector<int>> get_input(std::string filename);

int main(){
    std::vector<int> left{get_input("input").first}, right{get_input("input").second};
    std::unordered_map<int, int> rightMap;
    for(const auto& value : right)
        rightMap[value]++;
    int result{0};
    for(const auto& value : left){
        if(rightMap.count(value))
            result += rightMap.at(value) * value;
    }
    std::cout << "Ergebnis: " << result << std::endl;
    return 0;
}

std::pair<std::vector<int>, std::vector<int>> get_input(std::string filename){
    std::ifstream input;
    input.open(filename);
    if (!input){
        std::cerr << "Unable to open file: " << filename << std::endl;
        exit(1);
    }
    int x, y;
    std::vector<int> left, right; 
    while(input >> x){
        input >> y;
        left.push_back(x);
        right.push_back(y);
    }
    input.close();
    return std::make_pair(left, right);
}