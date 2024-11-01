#include <stdio.h>
#include <string.h>

#define MAX_DIGITS 10
#define MAX_ROWS 7
#define MAX_COLS 7

const char digits[MAX_DIGITS][MAX_ROWS][MAX_COLS] = {
    {
        ".......",".......","..*....","..*....","*****..","..*.*..",".*..*.*","*...***"
    },
    {
        ".......",".......",".......","..***..",".......",".......","......."
    },
    {
        ".......",".......","..***..",".......",".*****.",".......",".******"
    },
    {
        ".......",".......",".......","..***..",".......",".*****.","......."
    },
    {
        "*******","*.*.*.*","*.*.*.*","**...**","*.....*","*.....*","*******"
    },
    {
        ".......","*******","...*...",".*****.","..*.*..",".*...*.","......."
    },
    {
        ".......","...*...","...*...","*******","...*...","...*..*","...****"
    },
    {
        ".......","..*.*..","..*.*..","..*.*..",".*..*.*","*.....*","......."
    },
    {
        "..*....","..*...."."*****..","..*.*..","..*.*..",".*..*..","......."},
    {
        "*******","*.....*","*.....*","*.....*","*.....*","*.....*","*******"
    }
};

int count_stars(const char digit[MAX_ROWS][MAX_COLS]) {
    int count = 0;
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            if (digit[i][j] == '*') {
                count++;
            }
        }
    }
    return count;
}

int main() {
    int n;
    scanf("%d", &n);

    int star_counts[MAX_DIGITS];
    for (int i = 0; i < MAX_DIGITS; i++) {
        star_counts[i] = count_stars(digits[i]);
    }

    int result = 0;
    while (n >= star_counts[1]) {  // Minimum stars required for digit '1'
        for (int i = MAX_DIGITS - 1; i >= 0; i--) {
            if (n >= star_counts[i]) {
                result = result * 10 + i;
                n -= star_counts[i];
                break;
            }
        }
    }

    printf("%d\n", result);
    return 0;
}