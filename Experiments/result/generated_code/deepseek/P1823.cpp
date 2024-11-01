#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int height;
    int count;
} Person;

int main() {
    int n;
    scanf("%d", &n);

    int *heights = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &heights[i]);
    }

    Person *stack = (Person *)malloc(n * sizeof(Person));
    int top = -1;
    long long count = 0;

    for (int i = 0; i < n; i++) {
        while (top >= 0 && stack[top].height < heights[i]) {
            count++;
            top--;
        }

        if (top >= 0 && stack[top].height == heights[i]) {
            count += stack[top].count;
            if (top > 0) count++;
            stack[top].count++;
        } else {
            if (top >= 0) count++;
            stack[++top].height = heights[i];
            stack[top].count = 1;
        }
    }

    printf("%lld\n", count);

    free(heights);
    free(stack);
    return 0;
}