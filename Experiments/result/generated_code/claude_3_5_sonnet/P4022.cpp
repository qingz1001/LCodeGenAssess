#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 1100000
#define MAX_M 1000

char library[MAX_M][MAX_LEN];
char article[MAX_LEN];
int N, M;

int is_familiar(int start, int len) {
    for (int i = 0; i < M; i++) {
        if (strstr(library[i], article + start) - library[i] + len <= strlen(library[i])) {
            return 1;
        }
    }
    return 0;
}

int check(int L) {
    int total = strlen(article);
    int familiar = 0;
    int start = 0;

    while (start < total) {
        int end = start + L;
        while (end <= total && is_familiar(start, end - start)) {
            end++;
        }
        if (end - start >= L) {
            familiar += end - start - 1;
            start = end - 1;
        } else {
            start++;
        }
    }

    return familiar >= total * 0.9;
}

int find_L0() {
    int left = 1, right = strlen(article);
    int result = 0;

    while (left <= right) {
        int mid = (left + right) / 2;
        if (check(mid)) {
            result = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return result;
}

int main() {
    scanf("%d %d", &N, &M);

    for (int i = 0; i < M; i++) {
        scanf("%s", library[i]);
    }

    for (int i = 0; i < N; i++) {
        scanf("%s", article);
        printf("%d\n", find_L0());
    }

    return 0;
}