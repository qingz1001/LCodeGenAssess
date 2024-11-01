#include <stdio.h>
#include <stdbool.h>

bool can_split_into_increasing_subsequences(int N, int arr[]) {
    if (N % 2 != 0) return false;

    int half = N / 2;
    int max1 = -1, max2 = -1;
    int count1 = 0, count2 = 0;

    for (int i = 0; i < N; i++) {
        if (arr[i] > max1) {
            max1 = arr[i];
            count1++;
        } else if (arr[i] > max2) {
            max2 = arr[i];
            count2++;
        } else {
            return false;
        }
    }

    return count1 == half && count2 == half;
}

int main() {
    int N;
    while (scanf("%d", &N) != EOF) {
        int arr[N];
        for (int i = 0; i < N; i++) {
            scanf("%d", &arr[i]);
        }
        if (can_split_into_increasing_subsequences(N, arr)) {
            printf("Yes!\n");
        } else {
            printf("No!\n");
        }
    }
    return 0;
}