#include <cstdint>
#include <iostream>
#include <string>
#include <algorithm>
#include <set>

using i32 = int32_t;


void gen(const i32 & n, int cnt_open, int cnt_close,std::string ans) {
    if (cnt_open + cnt_close == 2 * n) {
        std::cout << ans << '\n';
        return;
    }
    if (cnt_open < n) {
        gen(n, cnt_open + 1, cnt_close, ans + '(');
    }
    if (cnt_open > cnt_close) {
        gen(n, cnt_open, cnt_close + 1, ans + ')');
    }
}



int main() {
    i32 n;
    std::cin >> n;
    gen(n,0,0,"");
    system("pause");
    return 0;
}