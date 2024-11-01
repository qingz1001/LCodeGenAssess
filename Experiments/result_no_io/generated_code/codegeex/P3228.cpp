#include <stdio.h>

long long n, k, m, p;

long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int main() {
    scanf("%lld%lld%lld%lld", &n, &k, &m, &p);
    
    // 计算 m^(k-1) % p
    long long m_power_k_minus_1 = mod_exp(m, k - 1, p);
    
    // 计算 (n - m*(k-1)) % p
    long long n_minus_m_k_1 = (n - m * (k - 1)) % p;
    
    // 计算 (n - m*(k-1)) / p
    long long n_minus_m_k_1_div_p = n_minus_m_k_1 / p;
    
    // 计算 n - m*(k-1) 的对数模 p
    long long log_mod = (long long)log(n_minus_m_k_1_div_p) % p;
    
    // 计算 n - m*(k-1) 的对数模 p 的逆元
    long long log_mod_inv = mod_exp(log_mod, p - 2, p);
    
    // 最终结果
    long long result = (m_power_k_minus_1 * log_mod_inv) % p;
    
    printf("%lld\n", result);
    
    return 0;
}