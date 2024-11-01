#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

// Function to compute gcd
ll gcd_func(ll a, ll b){
    while(b){
        ll temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

// Function to sort divisors
int cmpfunc(const void *a, const void *b){
    ll va = *(ll*)a;
    ll vb = *(ll*)b;
    if(va < vb) return -1;
    if(va > vb) return 1;
    return 0;
}

int main(){
    int n;
    scanf("%d", &n);
    while(n--){
        ll a0, a1, b0, b1;
        scanf("%lld %lld %lld %lld", &a0, &a1, &b0, &b1);
        if(b1 % b0 !=0 || a0 % a1 !=0){
            printf("0\n");
            continue;
        }
        ll c = b1 / a1;
        // Enumerate divisors of c
        ll divisors[134];
        int cnt =0;
        for(ll i=1;i*i <=c;i++){
            if(c % i ==0){
                divisors[cnt++] = i;
                if(c/i !=i){
                    divisors[cnt++] = c/i;
                }
            }
        }
        // Sort divisors to remove duplicates if any
        qsort(divisors, cnt, sizeof(ll), cmpfunc);
        // Count unique valid y
        int count =0;
        ll a0_div_a1 = a0 / a1;
        for(int i=0;i<cnt;i++){
            ll y = divisors[i];
            // Check gcd(y, a0/a1) ==1
            if(gcd_func(y, a0_div_a1)!=1){
                continue;
            }
            // Check lcm(a1*y, b0) == b1
            // lcm(a1*y, b0) = (a1*y * b0) / gcd(a1*y, b0)
            ll g = gcd_func(a1*y, b0);
            ll lcm = (a1*y / g) * b0;
            if(lcm == b1){
                count++;
            }
        }
        printf("%d\n", count);
    }
    return 0;
}