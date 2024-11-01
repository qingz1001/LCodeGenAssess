#include <stdio.h>
#include <string.h>

#define MAX 1000000000

int count_digits(int num) {
    int count = 0;
    while (num) {
        count++;
        num /= 10;
    }
    return count;
}

int compare(char *a, char *b) {
    int len_a = strlen(a), len_b = strlen(b);
    if (len_a != len_b) return len_a - len_b;
    return strcmp(a, b);
}

int solve(int K, int M) {
    int left = K, right = MAX;
    char str_K[11], str_i[11];
    sprintf(str_K, "%d", K);

    while (left <= right) {
        int mid = left + (right - left) / 2;
        int count = 0;

        for (int i = 1; i <= mid; i++) {
            sprintf(str_i, "%d", i);
            if (compare(str_i, str_K) <= 0) count++;
        }

        if (count == M) return mid;
        if (count < M) left = mid + 1;
        else right = mid - 1;
    }

    return 0;
}

int main() {
    int K, M;
    scanf("%d %d", &K, &M);
    printf("%d\n", solve(K, M));
    return 0;
}