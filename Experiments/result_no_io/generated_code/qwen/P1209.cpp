#include <stdio.h>
#include <stdlib.h>

#define MAX_M 50
#define MAX_S 200
#define MAX_C 200

int main() {
    int m, s, c;
    scanf("%d %d %d", &m, &s, &c);

    int cows[MAX_C];
    for (int i = 0; i < c; i++) {
        scanf("%d", &cows[i]);
    }

    // Sort the cow stalls
    for (int i = 0; i < c - 1; i++) {
        for (int j = i + 1; j < c; j++) {
            if (cows[i] > cows[j]) {
                int temp = cows[i];
                cows[i] = cows[j];
                cows[j] = temp;
            }
        }
    }

    int max_length = 0;
    for (int i = 0; i < c - 1; i++) {
        max_length = cows[i + 1] - cows[i];
    }

    int result = 0;
    while (max_length > 0) {
        int found = 0;
        for (int i = 0; i < c - 1; i++) {
            if (cows[i + 1] - cows[i] <= max_length) {
                cows[i + 1] = cows[i];
                found = 1;
                break;
            }
        }
        if (!found) {
            result += max_length;
            max_length--;
        } else {
            max_length--;
        }
    }

    printf("%d\n", result);

    return 0;
}