#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int index;
    int difficulty;
} Song;

int compare(const void *a, const void *b) {
    Song *songA = (Song *)a;
    Song *songB = (Song *)b;
    if (songA->difficulty != songB->difficulty) {
        return songB->difficulty - songA->difficulty;
    } else {
        return songA->index - songB->index;
    }
}

int main() {
    int n;
    double k;
    scanf("%d %lf", &n, &k);
    
    Song songs[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &songs[i].difficulty);
        songs[i].index = i;
    }
    
    qsort(songs, n, sizeof(Song), compare);
    
    printf("%d", songs[0].difficulty);
    for (int i = 1; i < n; i++) {
        printf(" %d", songs[i].difficulty);
    }
    printf("\n");
    
    return 0;
}