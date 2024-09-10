#include <iostream>
#include <vector>
#include <utility>

void shift(std::vector<std::pair<int, int>> &nums)
{
    for (auto& [first, second] : nums)
    {
        first++;
        second++;
    }
}

int main()
{
    // Test case 1: Empty vector
    std::vector<std::pair<int, int>> nums1;
    shift(nums1);
    // Expected output: nums1 is still empty

    // Test case 2: Vector with one pair
    std::vector<std::pair<int, int>> nums2 = {{1, 2}};
    shift(nums2);
    // Expected output: nums2 = {{2, 3}}

    // Test case 3: Vector with multiple pairs
    std::vector<std::pair<int, int>> nums3 = {{1, 2}, {3, 4}, {5, 6}};
    shift(nums3);
    // Expected output: nums3 = {{2, 3}, {4, 5}, {6, 7}}

    // Test case 4: Vector with negative values
    std::vector<std::pair<int, int>> nums4 = {{-1, -2}, {-3, -4}, {-5, -6}};
    shift(nums4);
    // Expected output: nums4 = {{0, -1}, {-2, -3}, {-4, -5}}

    return 0;
}