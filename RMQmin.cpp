#include <iostream>
#include <cctype>
#include <vector>

const int maxn = 300000;
long long Fenv[maxn + 2];
int init[maxn + 1];
int n;
std::vector<int> D[maxn + 1];

long long query(int i)
{
    long long sum = 0;
    while (i > 0)
        sum += Fenv[i], i -= i & -i;
    return sum;
}

void add(int i, long long k)
{
    while (i <= n)
        Fenv[i] += k, i += i & -i;
}

void update(int j, int k, long long v)
{
    add(j, v);
    add(k + 1, -v);
}

inline int getint()
{
    int ret = 0, ch;
    while (!isdigit(ch = getc(stdin)));
    ret = ch - '0';
    while (isdigit(ch = getc(stdin)))
        ret = ret * 10 + ch - '0';
    return ret;
}

void getDivs()
{
    for (int i = 1; i <= n; i++)
        for (int j = 1; j*i <= n; j++)
            D[j*i].push_back(i);
}

int main()
{
    n = getint();
    getDivs();
    for (int i = 1; i <= n; i++)
        init[i] = getint();
    int q = getint();
    while (q--)
    {
        int opt = getint();
        if (opt == 1)
        {
            int i = getint();
            long long ans = init[i];
            for (auto d : D[i])
                ans += query(d);
            std::cout << ans<<'\n';
        }
        else
        {
            int l = getint(), r = getint(), d = getint();
            update(l, r, d);
        }
    }
}
