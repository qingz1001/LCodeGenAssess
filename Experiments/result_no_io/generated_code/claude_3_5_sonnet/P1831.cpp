#include <stdio.h>
#include <stdbool.h>

typedef long long ll;

int digits[20];
int len;

bool isLever(ll num) {
    len = 0;
    while (num) {
        digits[len++] = num % 10;
        num /= 10;
    }
    
    for (int pivot = 0; pivot < len; pivot++) {
        ll left = 0, right = 0;
        for (int i = pivot + 1; i < len; i++) {
            left += digits[i] * (i - pivot);
        }
        for (int i = 0; i < pivot; i++) {
            right += digits[i] * (pivot - i);
        }
        if (left == right) return true;
    }
    return false;
}

int main() {
    ll x, y;
    scanf("%lld %lld", &x, &y);
    
    int count = 0;
    for (ll i = x; i <= y; i++) {
        if (isLever(i)) {
            count++;
        }
    }
    
    printf("%d\n", count);
    return 0;
}