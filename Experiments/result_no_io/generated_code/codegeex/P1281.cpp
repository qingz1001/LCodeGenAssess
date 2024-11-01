#include <stdio.h>
#include <stdlib.h>

int books[501];
int result[501][2];

void print_result(int k) {
    for (int i = 0; i < k; i++) {
        printf("%d %d\n", result[i][0], result[i][1]);
    }
}

int main() {
    int m, k;
    scanf("%d %d", &m, &k);
    
    for (int i = 0; i < m; i++) {
        scanf("%d", &books[i]);
    }
    
    int left = 1, right = 0;
    for (int i = 0; i < m; i++) {
        right += books[i];
    }
    
    while (left <= right) {
        int mid = (left + right) / 2;
        int current_sum = 0;
        int people_count = 1;
        
        for (int i = 0; i < m; i++) {
            if (current_sum + books[i] <= mid) {
                current_sum += books[i];
            } else {
                people_count++;
                current_sum = books[i];
                if (people_count > k) {
                    break;
                }
            }
        }
        
        if (people_count <= k) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    
    int max_pages = left;
    int current_sum = 0;
    int people_count = 0;
    result[0][0] = 1;
    
    for (int i = 0; i < m; i++) {
        if (current_sum + books[i] <= max_pages) {
            current_sum += books[i];
        } else {
            result[people_count][1] = i;
            people_count++;
            result[people_count][0] = i + 1;
            current_sum = books[i];
        }
    }
    
    result[people_count][1] = m;
    
    print_result(k);
    
    return 0;
}