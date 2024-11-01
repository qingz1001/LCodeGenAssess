#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10000

typedef struct {
    int start;
    int end;
} Segment;

int compare(const void *a, const void *b) {
    Segment *segA = (Segment *)a;
    Segment *segB = (Segment *)b;
    return segA->start - segB->start;
}

int main() {
    int n, L;
    Segment segments[MAX_N];
    
    scanf("%d %d", &n, &L);
    
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &segments[i].start, &segments[i].end);
    }
    
    qsort(segments, n, sizeof(Segment), compare);
    
    int boards = 0;
    int current_end = -1;
    
    for (int i = 0; i < n; i++) {
        if (segments[i].start > current_end) {
            int length = segments[i].end - segments[i].start;
            boards += (length + L - 1) / L;
            current_end = segments[i].start + ((length + L - 1) / L) * L;
        } else if (segments[i].end > current_end) {
            int length = segments[i].end - current_end;
            boards += (length + L - 1) / L;
            current_end += ((length + L - 1) / L) * L;
        }
    }
    
    printf("%d\n", boards);
    
    return 0;
}