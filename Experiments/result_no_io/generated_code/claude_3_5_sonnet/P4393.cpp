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

ll peek() {
    return stack[top];
}

int size() {
    return top + 1;
}

int main() {
    int n;
    scanf("%d", &n);

    ll result = 0;
    for (int i = 0; i < n; i++) {
        ll x;
        scanf("%lld", &x);

        while (size() > 0 && peek() <= x) {
            ll cost = pop();
            result += cost;
            if (size() > 0) {
                result += cost;
            }
        }

        push(x);
    }

    while (size() > 1) {
        ll cost = pop();
        result += cost;
        if (size() > 0) {
            result += cost;
        }
    }

    printf("%lld\n", result);

    return 0;
}