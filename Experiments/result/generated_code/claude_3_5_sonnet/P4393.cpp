#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000001

typedef long long ll;

ll stack[MAX_N];
int top = -1;

void push(ll x) {
    stack[++top] = x;
}

ll pop() {
    return stack[top--];
}

int main() {
    int n;
    scanf("%d", &n);

    ll result = 0;
    for (int i = 0; i < n; i++) {
        ll x;
        scanf("%lld", &x);

        while (top > -1 && stack[top] <= x) {
            ll temp = pop();
            result += temp;
            x = (x > temp) ? x : temp;
        }
        push(x);
    }

    while (top > 0) {
        ll temp = pop();
        result += temp;
    }

    printf("%lld\n", result);

    return 0;
}