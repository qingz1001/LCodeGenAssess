#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int index;
    int max_w;
} Scallion;

int compare(const void *a, const void *b) {
    Scallion *sa = (Scallion *)a;
    Scallion *sb = (Scallion *)b;
    if (sb->max_w != sa->max_w)
        return sb->max_w - sa->max_w;
    return sa->index - sb->index;
}

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    
    int *a = (int*)malloc(N * sizeof(int));
    for(int i=0;i<N;i++) scanf("%d", &a[i]);
    
    int *b = (int*)malloc(M * sizeof(int));
    for(int i=0;i<M;i++) scanf("%d", &b[i]);
    
    int **w = (int**)malloc(N * sizeof(int*));
    for(int i=0;i<N;i++) {
        w[i] = (int*)malloc(M * sizeof(int));
        for(int j=0;j<M;j++) scanf("%d", &w[i][j]);
    }
    
    Scallion *s = (Scallion*)malloc(N * sizeof(Scallion));
    for(int i=0;i<N;i++) {
        s[i].index = i;
        int max_w = 0;
        for(int j=0;j<M;j++) if(w[i][j] > max_w) max_w = w[i][j];
        s[i].max_w = max_w;
    }
    
    qsort(s, N, sizeof(Scallion), compare);
    
    int *assign = (int*)calloc(N, sizeof(int));
    
    for(int i=0;i<N;i++) {
        int scallion = s[i].index;
        int best_j = -1;
        int best_w = -1;
        for(int j=0; j<M; j++) {
            if(w[scallion][j] > best_w && b[j] >= a[scallion]){
                best_w = w[scallion][j];
                best_j = j;
            }
        }
        if(best_j != -1){
            assign[scallion] = best_j +1;
            b[best_j] -= a[scallion];
        }
    }
    
    for(int i=0;i<N;i++) printf("%d\n", assign[i]);
    
    // Free memory
    free(a);
    free(b);
    for(int i=0;i<N;i++) free(w[i]);
    free(w);
    free(s);
    free(assign);
    
    return 0;
}