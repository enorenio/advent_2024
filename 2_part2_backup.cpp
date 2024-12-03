#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <string>
#include <sstream>

// Define aliases for better readability
typedef long long ll;

// Debugging macro
#define debug(x) \
    (std::cerr << #x << ": " << (x) << '\n')

int safe_count_global = 0;
int latest_diff = 0;

// Helper function to check if the sequence is safe
bool isSequenceSafe(const std::vector<int>& levels_original, bool erase_current = true) {
    std::vector<int> levels(levels_original);
    int safe_count = 1;
    bool isDecreasing = false;
    bool isIncreasing = false;

    for (size_t i = 1; i < levels.size(); ++i) {
        int diff = std::abs(levels[i] - levels[i - 1]);
        
        // Check for consistent increasing or decreasing trends
        if (levels[i] > levels[i - 1]) {
            if (isDecreasing) {
                if (erase_current) {
                    // remove leves[i] from levels
                    levels.erase(levels.begin() + i);
                    i = 0; // Adjust index after erasing
                } else {
                    // remove leves[i - 1] from levels
                    levels.erase(levels.begin() + i - 1);
                    i = 0; // Adjust index after erasing
                }
                safe_count--;
            } else {
                isIncreasing = true;
            }
        } else if (levels[i] < levels[i - 1]) {
            if (isIncreasing) {
                if (erase_current) {
                    // remove leves[i] from levels
                    levels.erase(levels.begin() + i);
                    i = 0; // Adjust index after erasing
                } else {
                    // remove leves[i - 1] from levels
                    levels.erase(levels.begin() + i - 1);
                    i = 0 ;// Adjust index after erasing
                }
                safe_count--;
            } else {
                isDecreasing = true;
            }
        }

        // Check if the difference is within the valid range
        if (diff < 1 || diff > 3) {
            if (erase_current) {
                // remove leves[i] from levels
                levels.erase(levels.begin() + i);
                i = 0; // Adjust index after erasing
            } else {
                // remove leves[i - 1] from levels
                levels.erase(levels.begin() + i - 1);
                i = 0; // Adjust index after erasing
            }
            safe_count--;
        }
        if (safe_count < 0) {
            safe_count_global = safe_count;
            latest_diff = diff;
            // erase_current is true on first call
            // and false on second call
            // if it is first call, we try second call
            // if it is second call, we return false
            if (erase_current == false) return false;
            else {
                bool alternative_safe = isSequenceSafe(levels_original, false);
                if (alternative_safe) return true;
                return false;
            }
            return false;
        }
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
        bool safe = false;

        // Parse the line into a vector of integers
        std::istringstream iss(line);
        int num;
        while (iss >> num) {
            levels.push_back(num);
        }

        // Check if the sequence is safe
        if (isSequenceSafe(levels)) {
            safe = true;
            ++count_of_safe_reports;
        }

        // Print the sequence
        for (int level : levels) {
            std::cout << level << ' ';
        }
        std::cout << (safe ? "Safe" : "Unsafe");
        std::cout << ' ' << safe_count_global << ' ' << latest_diff;
        std::cout << '\n';
    }

    infile.close();

    // Print the count of safe reports
    std::cout << "Count of safe reports: " << count_of_safe_reports << '\n';

    return 0;
}
