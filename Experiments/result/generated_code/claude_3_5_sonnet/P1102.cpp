#include <stdio.h>
#include <stdlib.h>

#define MAX_N 200000

int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int N, C;
    int numbers[MAX_N];
    long long count = 0;
    
    scanf("%d %d", &N, &C);
    
    for (int i = 0; i < N; i++) {
        scanf("%d", &numbers[i]);
    }
    
    qsort(numbers, N, sizeof(int), cmp);
    
    int left = 0, right = 0;
    while (right < N) {
        int diff = numbers[right] - numbers[left];
        if (diff == C) {
            int same_left = 1, same_right = 1;
            while (left + 1 < N && numbers[left] == numbers[left + 1]) {
                left++;
                same_left++;
            }
            if (left != right) {
                while (right + 1 < N && numbers[right] == numbers[right + 1]) {
                    right++;
                    same_right++;
                }
                count += (long long)same_left * same_right;
            } else {
                count += (long long)same_left * (same_left - 1) / 2;
            }
            left++;
            right = left + 1;
        } else if (diff < C) {
            right++;
        } else {
            left++;
            if (left > right) {
                right = left + 1;
            }
        }
    }
    
    printf("%lld\n", count);
    
    return 0;
}