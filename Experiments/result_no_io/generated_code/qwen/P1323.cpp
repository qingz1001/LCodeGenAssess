#include <stdio.h>
#include <stdlib.h>

#define MAXN 30005

int main() {
    int k, m;
    scanf("%d %d", &k, &m);

    // Initialize the set with the first element
    int set[MAXN];
    int size = 1;
    set[0] = 1;

    // Generate the set elements
    for (int i = 0; i < k - 1; i++) {
        int last = set[size - 1];
        set[size++] = 2 * last + 1;
        if (size < MAXN) set[size++] = 4 * last + 5;
    }

    // Convert the set to a string
    char num_str[MAXN];
    for (int i = 0; i < size; i++) {
        sprintf(num_str + i * 6, "%d", set[i]);
    }
    num_str[k * 6] = '\0';

    // Remove m digits to maximize the number
    for (int i = 0; i < m; i++) {
        int max_pos = 0;
        for (int j = 0; j <= k * 6 - m - i; j++) {
            if (num_str[j] > num_str[max_pos]) {
                max_pos = j;
            } else if (num_str[j] == num_str[max_pos] && j + 1 <= k * 6 - m - i) {
                if (num_str[j + 1] > num_str[max_pos + 1]) {
                    max_pos = j;
                }
            }
        }
        for (int j = max_pos; j < k * 6 - m - i; j++) {
            num_str[j] = num_str[j + 1];
        }
    }

    // Output the results
    printf("%s\n%s\n", num_str, num_str);

    return 0;
}