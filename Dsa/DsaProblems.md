# Data Structures & Algorithms (DSA) Practice

Welcome to my DSA repository where I solve problems by topic. Below are categories with example LeetCode problems and links.  
✅ = Solved | ❌ = Not Yet

---

## Arrays
- [x] [Two Sum](https://leetcode.com/problems/two-sum/)

💡 **Hint**: Use a hash map to store the difference `target - nums[i]` while iterating.





















- it is ex
- hey

# Example Code: Two Sum (C++)

```cpp
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> map; // value -> index
    for (int i = 0; i < nums.size(); i++) {
        int complement = target - nums[i];
        if (map.find(complement) != map.end()) {
            return {map[complement], i};
        }
        map[nums[i]] = i;
    }
    return {};
}

int main() {
    vector<int> nums = {2, 7, 11, 15};
    int target = 9;
    vector<int> result = twoSum(nums, target);
    cout << "Indices: " << result[0] << ", " << result[1] << endl;
    return 0;
}
```
- [ ] [Maximum Subarray](https://leetcode.com/problems/maximum-subarray/)

## Strings
- [x] [Valid Anagram](https://leetcode.com/problems/valid-anagram/)
- [ ] [Longest Substring Without Repeating Characters](https://leetcode.com/problems/longest-substring-without-repeating-characters/)

## Linked List
- [ ] [Reverse Linked List](https://leetcode.com/problems/reverse-linked-list/)
- [x] [Detect Cycle in Linked List](https://leetcode.com/problems/linked-list-cycle/)

## Trees
- [ ] [Binary Tree Inorder Traversal](https://leetcode.com/problems/binary-tree-inorder-traversal/)
- [ ] [Lowest Common Ancestor of a Binary Tree](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/)

## Sliding Window
- [ ] [Longest Substring Without Repeating Characters](https://leetcode.com/problems/longest-substring-without-repeating-characters/)
- [ ] [Minimum Window Substring](https://leetcode.com/problems/minimum-window-substring/)

## Graphs
- [ ] [Number of Islands](https://leetcode.com/problems/number-of-islands/)
- [ ] [Course Schedule](https://leetcode.com/problems/course-schedule/)

## Dynamic Programming (DP)
- [ ] [Climbing Stairs](https://leetcode.com/problems/climbing-stairs/)
- [ ] [Longest Increasing Subsequence](https://leetcode.com/problems/longest-increasing-subsequence/)

---

