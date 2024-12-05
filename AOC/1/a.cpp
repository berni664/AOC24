#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>


std::pair<std::vector<int>, std::vector<int>> get_input(std::string filename); 

int main(){
    std::vector<int> left{get_input("input").first}, right{get_input("input").second};
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());
    int result{0};
    for(size_t i{0}; i < left.size(); ++i){
        int dif = left.at(i) - right.at(i);
        if(dif < 0)
            dif *= -1;
        result += dif;
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