#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int length;
    int width;
} Stick;

int compare(const void* a, const void* b) {
    Stick* stickA = (Stick*)a;
    Stick* stickB = (Stick*)b;
    
    if (stickA->length != stickB->length)
        return stickB->length - stickA->length;
    return stickB->width - stickA->width;
}

int main() {
    int n;
    scanf("%d", &n);
    
    Stick sticks[5000];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &sticks[i].length, &sticks[i].width);
    }
    
    qsort(sticks, n, sizeof(Stick), compare);
    
    int prep_time = 1;
    int max_width = sticks[0].width;
    
    for (int i = 1; i < n; i++) {
        if (sticks[i].width > max_width) {
            prep_time++;
            max_width = sticks[i].width;
        }
    }
    
    printf("%d\n", prep_time);
    
    return 0;
}