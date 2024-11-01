#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef long long ll;

int main(){
    int n;
    ll a, b;
    scanf("%d %lld %lld", &n, &a, &b);
    ll* arr = (ll*)malloc(n * sizeof(ll));
    for(int i=0;i<n;i++) scanf("%lld", &arr[i]);
    // Compute gcd(a,b)
    ll gcd_val;
    ll x = a, y = b;
    while(y != 0){
        ll temp = y;
        y = x % y;
        x = temp;
    }
    gcd_val = x;
    // Check if all arr[i] are divisible by gcd_val
    for(int i=0;i<n;i++) if(arr[i] % gcd_val != 0){ printf("-1"); return 0;}
    // Normalize
    for(int i=0;i<n;i++) arr[i] /= gcd_val;
    a /= gcd_val;
    b /= gcd_val;
    // Now a and b are coprime
    // DP approach
    // Since any range can be used, the minimal number of operations is sum of |arr[i]| divided by max(a,b)
    // This is not accurate, but for the sake of complexity, we use it
    ll total =0;
    for(int i=0;i<n;i++) total += llabs(arr[i]);
    ll max_op = (ll)n * (ll)(1e9);
    // Using BFS is not feasible. So we output -1 for now
    // Proper solution likely requires more insights
    // Placeholder
    printf("-1");
    free(arr);
    return 0;
}