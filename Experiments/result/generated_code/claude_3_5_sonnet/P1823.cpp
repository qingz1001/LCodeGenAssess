#include <stdio.h>
#include <stdlib.h>

#define MAX_N 500000

typedef struct {
    int height;
    int count;
} Person;

Person stack[MAX_N];
int top = -1;

long long countVisiblePairs(int n) {
    long long result = 0;
    int height;

    for (int i = 0; i < n; i++) {
        scanf("%d", &height);

        while (top >= 0 && stack[top].height < height) {
            result += stack[top].count;
            top--;
        }

        if (top >= 0) {
            if (stack[top].height == height) {
                result += stack[top].count;
                if (top > 0) result++;
                stack[top].count++;
            } else {
                result++;
                top++;
                stack[top].height = height;
                stack[top].count = 1;
            }
        } else {
            top++;
            stack[top].height = height;
            stack[top].count = 1;
        }
    }

    return result;
}

int main() {
    int n;
    scanf("%d", &n);

    long long pairs = countVisiblePairs(n);
    printf("%lld\n", pairs);

    return 0;
}