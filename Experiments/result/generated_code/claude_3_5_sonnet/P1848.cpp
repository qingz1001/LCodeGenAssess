#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000

typedef struct {
    int height;
    int width;
} Book;

Book books[MAX_N];
int N, L;

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d %d", &N, &L);
    
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &books[i].height, &books[i].width);
    }

    int total_height = 0;
    int current_width = 0;
    int current_max_height = 0;

    for (int i = 0; i < N; i++) {
        if (current_width + books[i].width > L) {
            total_height += current_max_height;
            current_width = 0;
            current_max_height = 0;
        }
        
        current_width += books[i].width;
        current_max_height = max(current_max_height, books[i].height);
    }

    // Add the height of the last shelf
    total_height += current_max_height;

    printf("%d\n", total_height);

    return 0;
}