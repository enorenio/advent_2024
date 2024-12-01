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
    
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());
    
    int sum = std::inner_product(left.begin(), left.end(), right.begin(), 0, std::plus<>(),
        [](int a, int b) { return std::abs(a - b); });

    std::cout << "Sum: " << sum << '\n';

    return 0;
}