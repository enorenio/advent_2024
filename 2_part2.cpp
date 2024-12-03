#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <string>
#include <sstream>
#include <algorithm>

// Define aliases for better readability
typedef long long ll;

// Debugging macro
#define debug(x) \
    (std::cerr << #x << ": " << (x) << '\n')

// Helper function to check if the sequence is safe
bool isSequenceSafe(const std::vector<int>& levels) {
    bool isDecreasing = false;
    bool isIncreasing = false;

    for (size_t i = 1; i < levels.size(); ++i) {
        int diff = std::abs(levels[i] - levels[i - 1]);
        
        // Check for consistent increasing or decreasing trends
        if (levels[i] > levels[i - 1]) {
            if (isDecreasing) return false;
            isIncreasing = true;
        } else if (levels[i] < levels[i - 1]) {
            if (isIncreasing) return false;
            isDecreasing = true;
        }

        // Check if the difference is within the valid range
        if (diff < 1 || diff > 3) return false;
    }

    return true;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int count_of_safe_reports = 0;
    std::vector<int> levels;

    std::ifstream infile("/home/reni/Documents/advent_2024/2.txt");
    if (!infile) {
        std::cerr << "Error: Could not open file.\n";
        return 1;
    }

    std::string line;
    while (std::getline(infile, line)) {
        levels.clear();

        // Parse the line into a vector of integers
        std::istringstream iss(line);
        int num;
        while (iss >> num) {
            levels.push_back(num);
        }

        // Check if the sequence is safe
        if (isSequenceSafe(levels)) {
            ++count_of_safe_reports;
        } else {
            // Try removing each level and rechecking
            bool is_safe = false;
            for (size_t i = 0; i < levels.size(); ++i) {
                // Create a copy of levels without the current element
                std::vector<int> levels_copy = levels;
                levels_copy.erase(levels_copy.begin() + i);

                if (isSequenceSafe(levels_copy)) {
                    is_safe = true;
                    break;
                }
            }
            if (is_safe) {
                ++count_of_safe_reports;
            }
        }

        // Print the sequence
        for (int level : levels) {
            std::cout << level << ' ';
        }
        std::cout << '\n';
    }

    infile.close();

    // Print the count of safe reports
    std::cout << "Count of safe reports: " << count_of_safe_reports << '\n';

    return 0;
}
