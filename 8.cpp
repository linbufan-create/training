/*
模考2
T1
字符串哈希
统计s1与s2共有的循环节个数
*/
#include <bits/stdc++.h>
using namespace std;
#define int size_t      // 防止爆int
const int N = 1e7 + 10; // 最长字符串长度
char s1[N], s2[N];      // 字符串,从1开始存
int len1, len2;
int ans; // 存储答案
int hash_val1[N], hash_val2[N], base = 131, mod = 1e9 + 7;
/// @brief 实现O(log b)求a^b%mod,快速幂实现
/// @param a 底数
/// @param b 指数
/// @param mod 模数
/// @return a^b%mod的结果
int modf(int a, int b, int mod)
{
        int sum = 1;
        while (b)
        {
                if (b & 1)
                {
                        sum = sum * a % mod;
                }
                b >>= 1;
                a = a * a % mod;
        }
        return sum;
}
/// @brief 实现O(log x) 求x在%mod 意义下的逆元,基于快速幂
/// @param x 原数
/// @param mod 模数
/// @return x的逆元
int get_inv(int x, int mod)
{
        return modf(x, mod - 2, mod);
}
/// @brief 获取字符串char s[ ] 的哈希值
/// @param s  被哈希字符串
/// @param val 存储所有前缀的哈希值的数组
void get_string_hash(char s[], int val[])
{
        int sum = 0;
        int len = strlen(s + 1);
        for (int i = 1; i <= len; i++)
        {
                sum = (sum * base + s[i]) % mod;
                val[i] = sum;
        }
}
/// @brief 获取以val[ ]为存储前缀哈希值的字符串从l到r的字串的哈希值
/// @param l 字串的左端点
/// @param r 子串的右端点
/// @param val 存储所有前缀的哈希值的数组
/// @return 子串的哈希值
int get_sub_hash(int l, int r, int val[])
{
        return ((long long)(val[r] - ((long long)val[l - 1] * (long long)modf(base, r - l + 1, mod)) % mod + mod) % mod);
}
/// @brief 输入s1,s2,初始化,求s1,s2的哈希值
void init()
{
        scanf("%s", s1 + 1);
        scanf("%s", s2 + 1);
        len1 = strlen(s1 + 1);
        len2 = strlen(s2 + 1);
        get_string_hash(s1, hash_val1);
        get_string_hash(s2, hash_val2);
}
/// @brief 判断长为len的子串是否能作为循环节
/// @param len 要判断的子串的长度
/// @return 是否可以,0-不可以,1-可以
bool check(int len)
{
        if (__gcd(len2, len1) % len)
        {
                return 0;
        }
        if (get_sub_hash(1, len, hash_val1) != get_sub_hash(1, len, hash_val2))
        {
                return 0;
        }
        if (get_sub_hash(1, len1 - len, hash_val1) != get_sub_hash(len + 1, len1, hash_val1))
        {
                return 0;
        }
        if (get_sub_hash(1, len2 - len, hash_val2) != get_sub_hash(len + 1, len2, hash_val2))
        {
                return 0;
        }
        return 1;
}
/// @brief 统计公共除数,并输出个数
void solve()
{
        int max_len = __gcd(strlen(s1 + 1), strlen(s2 + 1));
        for (int i = 1; i <= max_len; i++)
        {
                ans += check(i);
        }
        cout << ans;
}
signed main()
{

        init();
        solve();
}
