#include <iostream>
#include <vector>
#include <algorithm>

#define maxx 10234
using i32 = int32_t;
std::vector<std::vector<i32 > > g;
i32 dp[maxx][2]; //0 - size of min if dont take else 1
i32 used[maxx];

void dfs(i32 v, i32 parent = -1) {
    used[v] = 1;
    i32 next, count_child = 0;
    for (i32 i = 0; i < g[v].size(); ++i) {
        next = g[v][i];
        if (next != parent) {
            dfs(next, v);
            count_child++;
        }
    }
    if (count_child == 0) {
        dp[v][1] = 1;
        dp[v][0] = 0;
        return;
    }
    i32 inc_root = 1, out_root = 0;
    for (i32 i = 0; i < g[v].size(); ++i) {
        next = g[v][i];
        inc_root += std::min(dp[next][0], dp[next][1]);
        out_root += dp[next][1];
    }
    dp[v][0] = out_root;
    dp[v][1] = inc_root;
    return;
}
int main() {
    i32 n, res = 0;
    std::cin >> n;
    g.resize(n);
    for (i32 i = 0; i < n; ++i) {
        i32 cnt, ver;
        std::cin >> cnt;
        while (cnt--) {
            std::cin >> ver;
            g[i].push_back(ver);
        }
    }
    for (i32 i = 0; i < n; ++i) {
        if (used[i]) continue;
        dfs(i);
        res += std::min(dp[i][0], dp[i][1]);
    }
    std::cout << res;
    system("pause");
}