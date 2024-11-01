#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 10

struct Bowl {
    int h, r1, r2;
} bowls[N];

int compare(const void *a, const void *b) {
    struct Bowl * bowlA = (struct Bowl *)a;
    struct Bowl * bowlB = (struct Bowl *)b;
    
    // Compare based on the difference in radius at the top and bottom
    double diffA = (bowlA->r2 - bowlA->r1) / sqrt(bowlA->h);
    double diffB = (bowlB->r2 - bowlB->r1) / sqrt(bowlB->h);
    
    if (diffA < diffB) return -1;
    if (diffA > diffB) return 1;
    
    // If the difference is the same, compare based on the difference in radius at the bottom
    diffA = (bowlA->r1 - bowlA->r2) / sqrt(bowlA->h);
    diffB = (bowlB->r1 - bowlB->r2) / sqrt(bowlB->h);
    
    if (diffA < diffB) return -1;
    if (diffA > diffB) return 1;
    
    // If both differences are the same, compare based on height
    if (bowlA->h < bowlB->h) return -1;
    if (bowlA->h > bowlB->h) return 1;
    
    return 0;
}

int main() {
    int n;
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &bowls[i].h, &bowls[i].r1, &bowls[i].r2);
    }
    
    // Sort the bowls based on the defined criteria
    qsort(bowls, n, sizeof(struct Bowl), compare);
    
    double maxHeight = 0;
    double currentHeight = 0;
    
    for (int i = 0; i < n; i++) {
        // Calculate the new height when placing the current bowl on top
        double newHeight = currentHeight + sqrt(pow(bowls[i].r2, 2) - pow(bowls[i].r1, 2));
        if (newHeight > maxHeight) {
            maxHeight = newHeight;
        }
        currentHeight += bowls[i].h;
    }
    
    printf("%.0lf\n", maxHeight);
    
    return 0;
}