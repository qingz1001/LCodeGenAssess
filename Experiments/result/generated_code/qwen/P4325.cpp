#include <stdio.h>
#include <stdbool.h>

int main() {
    int numbers[10];
    bool seen[42] = {false};
    int count = 0;

    for (int i = 0; i < 10; i++) {
        scanf("%d", &numbers[i]);
        int mod = numbers[i] % 42;
        if (!seen[mod]) {
            seen[mod] = true;
            count++;
        }
    }

    printf("%d\n", count);
    return 0;
}