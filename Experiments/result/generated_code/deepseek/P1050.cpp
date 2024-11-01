#include <stdio.h>
#include <string.h>

#define MAX_K 100

void multiply(int result[], int n[], int len) {
    int carry = 0;
    for (int i = 0; i < len; i++) {
        int temp = result[i] * n[0] + carry;
        result[i] = temp % 10;
        carry = temp / 10;
    }
}

int find_cycle_length(int n[], int k) {
    int result[MAX_K] = {0};
    int temp[MAX_K] = {0};
    int cycle_length = 0;
    int cycle_found = 0;

    for (int i = 0; i < k; i++) {
        temp[i] = n[i];
    }

    while (!cycle_found) {
        cycle_length++;
        multiply(temp, n, k);

        int match = 1;
        for (int i = 0; i < k; i++) {
            if (temp[i] != n[i]) {
                match = 0;
                break;
            }
        }

        if (match) {
            cycle_found = 1;
        }
    }

    return cycle_length;
}

int main() {
    char n_str[MAX_K + 1];
    int k;
    scanf("%s %d", n_str, &k);

    int n[MAX_K] = {0};
    int len = strlen(n_str);
    for (int i = 0; i < len; i++) {
        n[i] = n_str[len - 1 - i] - '0';
    }

    int cycle_length = find_cycle_length(n, k);
    printf("%d\n", cycle_length);

    return 0;
}