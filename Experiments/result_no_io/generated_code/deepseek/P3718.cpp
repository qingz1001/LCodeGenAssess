#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAXN 100005

int n, k;
char lights[MAXN];

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int calculateMinUgliness(char target) {
    int left = 0, right = 0;
    int flips = 0;
    int minUgliness = INT_MAX;

    while (right < n) {
        if (lights[right] != target) {
            flips++;
        }

        while (flips > k) {
            if (lights[left] != target) {
                flips--;
            }
            left++;
        }

        minUgliness = min(minUgliness, max(right - left + 1, 0));
        right++;
    }

    return minUgliness;
}

int main() {
    scanf("%d %d", &n, &k);
    scanf("%s", lights);

    int result = min(calculateMinUgliness('N'), calculateMinUgliness('F'));
    printf("%d\n", result);

    return 0;
}