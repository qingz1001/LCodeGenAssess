#include <stdio.h>
#include <stdlib.h>

#define MAX_N 200000

int compare(const void *a, const void *b) {
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
    
    qsort(numbers, N, sizeof(int), compare);
    
    int left = 0, right = 0;
    while (right < N) {
        int diff = numbers[right] - numbers[left];
        if (diff == C) {
            int same_left = 1, same_right = 1;
            
            while (left + 1 < N && numbers[left] == numbers[left + 1]) {
                left++;
                same_left++;
            }
            
            if (C != 0) {
                while (right + 1 < N && numbers[right] == numbers[right + 1]) {
                    right++;
                    same_right++;
                }
            } else {
                same_right = same_left;
            }
            
            count += (long long)same_left * same_right;
            left++;
            if (C == 0) right = left;
            else right++;
        } else if (diff < C) {
            right++;
        } else {
            left++;
        }
    }
    
    printf("%lld\n", count);
    
    return 0;
}