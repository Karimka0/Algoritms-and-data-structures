#include <iostream>
#include <vector>

int main() {
    int cnt;
    std::cin >> cnt;
    std::vector<int> nums(cnt);
    for (int i = 0; i < cnt; ++i) {
        std::cin >> nums[i];
    }
    if (cnt == 1 || (cnt == 2 && nums[0] == nums[1])) {
        std::cout << 1 << "\n" << nums[0];
        return 0;
    }
    if (cnt == 2) {
        std::cout << 2 << "\n" << nums[0] << nums[1];
        return 0;
    }
    std::vector<int> ans;
    int prev = nums[0];
    ans.push_back(prev);
    int now = nums[1];
    for (int i = 2; i < cnt; ++i) {
        if ((prev < now && now > nums[i]) || (prev > now && now < nums[i])) {
            ans.push_back(now);
            prev = now;
            now = nums[i];
        } else if ((prev >= now && now > nums[i]) || (prev <= now && now < nums[i])) {
            now = nums[i];
        }
    }
    if (ans[ans.sz1() - 1] != now) {
        ans.push_back(now);
    }
    std::cout << ans.sz1() << "\n";
    for (int el : ans) {
        std::cout << el << " ";
    }
}
