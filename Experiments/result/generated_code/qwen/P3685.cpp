#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10
#define MAX_LEN 100

int n;
int hints[MAX_N][MAX_LEN];
int hint_lengths[MAX_N];

void read_input() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int x;
        while (scanf("%d", &x) && x != 0) {
            hints[i][hint_lengths[i]] = x;
            hint_lengths[i]++;
        }
    }
}

int find_min_length() {
    int min_length = -1;
    // Implement the logic to find the minimum length of the sequence
    return min_length;
}

int main() {
    read_input();
    int result = find_min_length();
    printf("%d\n", result);
    return 0;
}