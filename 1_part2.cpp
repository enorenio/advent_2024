typedef long long ll;
#define debug(x) \
    (std::cerr << #x << ": " << (x) << '\n')

#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <fstream>
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::vector<int> left(1000);
    std::vector<int> right(1000);

    // read input from 1.txt into left and right
    std::ifstream infile("/home/reni/Documents/advent_2024/1.txt");
    for (int i = 0; i < 1000 && infile; ++i) {
        infile >> left[i] >> right[i];
    }
    infile.close();
    
    int sum = 0;
    for (auto integer : left) {
        int similarity_score = integer * std::count(right.begin(), right.end(), integer);
        sum += similarity_score;
    }

    std::cout << "Sum: " << sum << '\n';

    return 0;
}