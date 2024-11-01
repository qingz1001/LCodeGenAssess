#include <stdio.h>
#include <string.h>

int possible_digits[10][7] = {
    {1, 1, 1, 1, 1, 1, 0}, // 0
    {0, 1, 1, 0, 0, 0, 0}, // 1
    {1, 1, 0, 1, 1, 0, 1}, // 2
    {1, 1, 1, 1, 0, 0, 1}, // 3
    {0, 1, 1, 0, 0, 1, 1}, // 4
    {1, 0, 1, 1, 0, 1, 1}, // 5
    {1, 0, 1, 1, 1, 1, 1}, // 6
    {1, 1, 1, 0, 0, 0, 0}, // 7
    {1, 1, 1, 1, 1, 1, 1}, // 8
    {1, 1, 1, 1, 0, 1, 1}  // 9
};

int count_possible_digits(int segment_state[7]) {
    int count = 0;
    for (int i = 0; i < 10; i++) {
        int match = 1;
        for (int j = 0; j < 7; j++) {
            if (segment_state[j] == 1 && possible_digits[i][j] == 0) {
                match = 0;
                break;
            }
        }
        if (match) {
            count++;
        }
    }
    return count;
}

int main() {
    int segment_states[18][7] = {
        {0, 0, 0, 0, 0, 1, 1},
        {1, 0, 0, 1, 0, 1, 1},
        {0, 0, 0, 0, 0, 0, 1},
        {0, 1, 0, 0, 0, 0, 1},
        {0, 1, 0, 1, 0, 1, 1},
        {0, 1, 1, 0, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 1},
        {0, 0, 1, 0, 1, 1, 0},
        {0, 1, 0, 1, 0, 0, 1},
        {0, 0, 1, 0, 1, 1, 0},
        {1, 0, 1, 1, 1, 0, 0},
        {0, 1, 0, 0, 1, 1, 0},
        {1, 0, 1, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 1, 1},
        {0, 0, 0, 1, 1, 1, 1},
        {0, 1, 0, 1, 1, 0, 1},
        {0, 1, 1, 0, 1, 0, 1},
        {1, 1, 0, 1, 0, 1, 0}
    };

    long long total_combinations = 1;
    for (int i = 0; i < 18; i++) {
        total_combinations *= count_possible_digits(segment_states[i]);
    }

    printf("%lld\n", total_combinations);
    return 0;
}