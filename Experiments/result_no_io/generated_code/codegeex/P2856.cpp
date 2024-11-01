#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LEN 11

int B, L, D;
char dictionary[1001][MAX_LEN];
int max_unique_words;
char button_assignments[26][27];

bool check_uniqueness(int button_assignment[]) {
    int count[MAX_LEN] = {0};
    for (int i = 0; i < L; ++i) {
        count[button_assignment[i]]++;
    }
    for (int i = 0; i < L; ++i) {
        if (count[i] > 1) {
            return false;
        }
    }
    return true;
}

void assign_letters(int button_assignment[]) {
    for (int i = 0; i < L; ++i) {
        int start = button_assignment[i];
        int end = (i == L - 1) ? L - 1 : button_assignment[i + 1] - 1;
        button_assignments[i][0] = end - start + 2;
        for (int j = start; j <= end; ++j) {
            button_assignments[i][j - start + 1] = 'A' + j;
        }
    }
}

void solve(int index, int current_assignment[], int unique_count) {
    if (index == L) {
        if (check_uniqueness(current_assignment)) {
            if (unique_count > max_unique_words) {
                max_unique_words = unique_count;
                assign_letters(current_assignment);
            }
        }
        return;
    }
    for (int i = 0; i < B; ++i) {
        current_assignment[index] = i;
        int new_unique_count = unique_count;
        for (int j = 0; j < D; ++j) {
            bool is_unique = true;
            for (int k = 0; k < strlen(dictionary[j]); ++k) {
                int button = current_assignment[dictionary[j][k] - 'A'];
                if (button != current_assignment[dictionary[j][k - 1] - 'A']) {
                    is_unique = false;
                    break;
                }
            }
            if (is_unique) {
                new_unique_count++;
            }
        }
        solve(index + 1, current_assignment, new_unique_count);
    }
}

int main() {
    scanf("%d %d", &B, &L);
    scanf("%d", &D);
    for (int i = 0; i < D; ++i) {
        scanf("%s", dictionary[i]);
    }

    int button_assignment[L];
    max_unique_words = 0;
    solve(0, button_assignment, 0);

    printf("%d\n", max_unique_words);
    for (int i = 0; i < B; ++i) {
        printf("%s\n", button_assignments[i]);
    }

    return 0;
}