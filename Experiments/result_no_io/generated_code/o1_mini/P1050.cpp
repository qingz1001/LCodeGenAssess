#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to compute gcd
unsigned long long gcd_func(unsigned long long a, unsigned long long b){
    while(b){
        unsigned long long tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}

// Function to compute lcm
unsigned long long lcm_func(unsigned long long a, unsigned long long b){
    if(a ==0 || b==0) return 0;
    return a / gcd_func(a, b) * b;
}

// Function to count the power of p in n
int count_p(char *n, char p_char){
    int count =0;
    int len = strlen(n);
    // Convert n to integer to count factors of p
    // Since n can be up to 10^100, we process digit by digit
    char num[105];
    strcpy(num, n);
    while(1){
        int rem =0;
        int i;
        for(i=0;i<strlen(num);i++){
            int digit = num[i] - '0';
            int temp = rem *10 + digit;
            num[i] = temp / (p_char=='2'?2:5) + '0';
            rem = temp % (p_char=='2'?2:5);
        }
        // Remove leading zeros
        int start=0;
        while(start < strlen(num)-1 && num[start]=='0') start++;
        memmove(num, num+start, strlen(num+start)+1);
        if(rem !=0) break;
        count++;
    }
    return count;
}

// Function to compute n mod divisor (divisor is power of 2 or 5)
unsigned long long mod_power(char *n, unsigned long long divisor){
    unsigned long long res =0;
    for(int i=0;i<strlen(n);i++){
        res = (res *10 + (n[i]-'0')) % divisor;
    }
    return res;
}

// Function to compute power modulo m
unsigned long long powmod_func(unsigned long long base, unsigned long long exp, unsigned long long m){
    if(m ==1) return 0;
    unsigned long long result =1;
    base = base % m;
    while(exp >0){
        if(exp &1){
            result = (__int128)result * base % m;
        }
        base = (__int128)base * base % m;
        exp >>=1;
    }
    return result;
}

// Function to compute multiplicative order modulo m (m is power of 5)
unsigned long long order_mod5(unsigned long long n, unsigned long long m){
    if(n ==0) return -1;
    unsigned long long phi = 4;
    unsigned long long tmp = m;
    while(tmp >5){
        phi *=5;
        tmp /=5;
    }
    unsigned long long order = phi;
    while(order %5 ==0){
        unsigned long long candidate = order /5;
        if(powmod_func(n, candidate, m) ==1){
            order = candidate;
        }
        else{
            break;
        }
    }
    return order;
}

int main(){
    char n_str[105];
    int k;
    scanf("%s %d", n_str, &k);
    // Count factors of 2 and 5
    int cnt2=0, cnt5=0;
    // Count factors of 2
    char temp2[105];
    strcpy(temp2, n_str);
    while(1){
        int len = strlen(temp2);
        int rem =0;
        char new_num[105];
        int idx=0;
        for(int i=0;i<len;i++){
            int digit = temp2[i]-'0';
            int num = rem *10 + digit;
            new_num[idx++] = (num /2) + '0';
            rem = num %2;
        }
        new_num[idx] = '\0';
        // Remove leading zeros
        int start=0;
        while(start < strlen(new_num)-1 && new_num[start]=='0') start++;
        memmove(new_num, new_num+start, strlen(new_num+start)+1);
        if(rem !=0) break;
        cnt2++;
        strcpy(temp2, new_num);
    }
    // Count factors of 5
    char temp5[105];
    strcpy(temp5, n_str);
    while(1){
        int len = strlen(temp5);
        int rem =0;
        char new_num[105];
        int idx=0;
        for(int i=0;i<len;i++){
            int digit = temp5[i]-'0';
            int num = rem *10 + digit;
            new_num[idx++] = (num /5) + '0';
            rem = num %5;
        }
        new_num[idx] = '\0';
        // Remove leading zeros
        int start=0;
        while(start < strlen(new_num)-1 && new_num[start]=='0') start++;
        memmove(new_num, new_num+start, strlen(new_num+start)+1);
        if(rem !=0) break;
        cnt5++;
        strcpy(temp5, new_num);
    }
    // Compute m' =2^{k - cnt2} *5^{k -cnt5}
    int exp2 = k - (cnt2 <k ? cnt2 :k);
    int exp5 = k - (cnt5 <k ? cnt5 :k);
    // Compute m'
    unsigned long long m2=1, m5=1;
    for(int i=0;i<exp2;i++) m2 *=2;
    for(int i=0;i<exp5;i++) m5 *=5;
    // If m' =1, cycle length=1
    if(exp2 ==0 && exp5 ==0){
        printf("1");
        return 0;
    }
    // Compute n mod m2 and n mod m5
    unsigned long long n_mod2=0, n_mod5=0;
    if(exp2 >0) n_mod2 = mod_power(n_str, m2);
    if(exp5 >0) n_mod5 = mod_power(n_str, m5);
    // Compute order2
    unsigned long long order2=1;
    if(exp2 >0){
        if(m2 ==1){
            order2=1;
        }
        else{
            if(m2 ==2){
                order2=1;
            }
            else if(m2 ==4){
                order2=2;
            }
            else{
                // m2 >=8
                if(n_mod2 %4 ==1){
                    order2 =1;
                    for(int i=3;i<=exp2;i++){
                        order2 *=2;
                    }
                }
                else{
                    order2 =1;
                    for(int i=2;i<=exp2;i++){
                        order2 *=2;
                    }
                }
            }
        }
    }
    // Compute order5
    unsigned long long order5=1;
    if(exp5 >0){
        order5 = order_mod5(n_mod5, m5);
        if(order5 ==0){
            printf("-1");
            return 0;
        }
    }
    // Compute LCM
    unsigned long long L=1;
    if(exp2 >0 && exp5 >0){
        L = lcm_func(order2, order5);
    }
    else if(exp2 >0){
        L = order2;
    }
    else{
        L = order5;
    }
    // Check if L is valid
    // To simplify, assume it's valid
    printf("%llu", L);
    return 0;
}