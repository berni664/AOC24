#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>

std::vector<std::vector<int>> get_input(const std::string& filename); 
std::vector<int> parse_string_to_vector(const std::string& input_string);
bool is_safe(const std::vector<int>& line);

int main(){
    std::vector<std::vector<int>> data = get_input("input");
    int result{0};
    for(const auto& line : data){
        bool safe{false};
        for(size_t i{0}; i < line.size() && !safe; ++i){
            std::vector<int> line_new;
            for(size_t j{0}; j < line.size(); ++j){
                if(j != i)
                    line_new.push_back(line.at(j));
                }
            safe = is_safe(line_new);
        }
        result += safe;
    }
    std::cout << "Ergebnis: " << result << std::endl;
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
        result.push_back(parse_string_to_vector(line_int));
    }
    input.close();
    return result;
}

std::vector<int> parse_string_to_vector(const std::string& input_string) {
    std::vector<int> result;
    std::stringstream ss(input_string);
    int value;
    while (ss >> value) {
        result.push_back(value);
    }
    return result;
}

bool is_safe(const std::vector<int>& line){
    bool ascending{line.at(0) < line.at(1)};
    bool safe{true};
    for(size_t i{1}; i < line.size(); ++i){
        if((line.at(i) - line.at(i-1) > 3 || line.at(i) - line.at(i-1) < 1) && ascending)
            safe = false;
        if((line.at(i-1) - line.at(i) > 3 || line.at(i-1) - line.at(i) < 1) && !ascending)
            safe = false;
    }
    return safe;
}
