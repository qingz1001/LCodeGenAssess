#include <stdio.h>
#include <stdlib.h>

#define MAX_K 100000

typedef long long ll;

ll n, k;
int a[MAX_K];
ll last_step[MAX_K];

int main() {
    scanf("%lld %lld", &n, &k);
    
    for (int i = 0; i < k; i++) {
        scanf("%d", &a[i]);
    }
    
    ll current_pos = 0;
    for (ll step = 1; step <= n; step++) {
        int conductor = 0;
        while (conductor < k && last_step[conductor] == step - 1) {
            conductor++;
        }
        
        if (conductor == k) {
            break;
        }
        
        current_pos += a[conductor];
        last_step[conductor] = step;
    }
    
    for (int i = 0; i < k; i++) {
        printf("%lld ", last_step[i]);
    }
    
    return 0;
}