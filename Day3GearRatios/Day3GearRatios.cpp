#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

// Directions for checking adjacent cells (including diagonals)
const vector<pair<int, int>> directions = {
    {-1, -1}, {-1, 0}, {-1, 1},
    {0, -1},           {0, 1},
    {1, -1}, {1, 0}, {1, 1}
};

// Function to check if a character is a symbol (anything that's not a digit or '.')
bool isSymbol(char c) {
    return !isdigit(c) && c != '.';
}

// Function to check if any digit of a number has a symbol adjacent to it
bool hasAdjacentSymbol(const vector<string>& grid, int x, int startY, int endY) {
    int rows = grid.size();
    int cols = grid[0].size();
    for (int y = startY; y <= endY; ++y) {
        for (const auto& [dx, dy] : directions) {
            int newX = x + dx;
            int newY = y + dy;
            if (newX >= 0 && newX < rows && newY >= 0 && newY < cols) {
                if (isSymbol(grid[newX][newY])) {
                    return true;
                }
            }
        }
    }
    return false;
}

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "Error: Unable to open input file." << endl;
        return 1;
    }

    // Read the input grid from the file
    vector<string> grid;
    string line;
    while (getline(inputFile, line)) {
        grid.push_back(line);
    }
    inputFile.close();

    int rows = grid.size();
    int cols = grid[0].size();
    int partNumberSum = 0;

    // Traverse the grid to find part numbers
    for (int i = 0; i < rows; ++i) {
        int j = 0;
        while (j < cols) {
            if (isdigit(grid[i][j])) {
                // Extract the full multi-digit number
                int num = 0;
                int startJ = j;
                while (j < cols && isdigit(grid[i][j])) {
                    num = num * 10 + (grid[i][j] - '0');
                    j++;
                }
                int endJ = j - 1;

                // Check if any digit of the number has an adjacent symbol
                if (hasAdjacentSymbol(grid, i, startJ, endJ)) {
                    partNumberSum += num;
                }
            }
            else {
                j++;
            }
        }
    }

    // Output the result
    cout << "Sum of part numbers: " << partNumberSum << endl;
    return 0;
}
