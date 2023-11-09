#include <vector>
#include <numeric>

// Solution to https://www.codewars.com/kata/5601409514fc93442500010b
// Prioritizes legilibility over compactness.

int main(){}

bool betterThanAverage(std::vector<int> classPoints, int yourPoints) {
    auto count = static_cast<float>(classPoints.size());
    auto sum = std::reduce(classPoints.begin(), classPoints.end(), 0.0);
    auto average = sum / count;
    return average < static_cast<float>(yourPoints);
}
