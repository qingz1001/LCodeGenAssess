#include <stdio.h>
#include <string.h>

#define MAX_NAME_LENGTH 21
#define MAX_FOODS 101

int main() {
    int n;
    scanf("%d", &n);
    char foods[MAX_FOODS][MAX_NAME_LENGTH];
    int count[MAX_NAME_LENGTH] = {0};

    for (int i = 0; i < n; i++) {
        scanf("%s", foods[i]);
        count[foods[i][0]]++;
        int sum = 0;
        for (int j = 0; j < 26; j++) {
            if (j != foods[i][0] - 'a') {
                sum += count[j];
            }
        }
        if (count[foods[i][0] - 'a'] > sum) {
            printf("1\n");
        } else {
            printf("0\n");
        }
    }

    return 0;
}