#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long c;
    int x;
    int y;
} Pair;

int compare(const void *a, const void *b){
    Pair *pa = (Pair *)a;
    Pair *pb = (Pair *)b;
    if(pb->c > pa->c) return 1;
    else if(pb->c < pa->c) return -1;
    return 0;
}

int main(){
    int N;
    scanf("%d", &N);
    // c[i][j] where i < j
    long long c[N+1][N+1];
    // Initialize
    for(int i=1;i<=N;i++) {
        for(int j=i+1;j<=N;j++) {
            c[i][j] = 0;
        }
    }
    // Read input
    for(int i=1;i<N;i++) {
        for(int j=i+1;j<=N;j++) {
            scanf("%lld", &c[i][j]);
        }
    }
    // Collect all pairs
    int total = N*(N-1)/2;
    Pair *pairs = (Pair *)malloc(sizeof(Pair)*total);
    int idx=0;
    for(int i=1;i<N;i++) {
        for(int j=i+1;j<=N;j++) {
            pairs[idx].c = c[i][j];
            pairs[idx].x = i;
            pairs[idx].y = j;
            idx++;
        }
    }
    // Sort pairs descendingly
    qsort(pairs, total, sizeof(Pair), compare);
    // Get the top pair
    Pair top = pairs[0];
    long long c_max2 = -1;
    // Find the next pair where one of the generals is top.x
    for(int i=1;i<total;i++) {
        if(pairs[i].x == top.x || pairs[i].y == top.x){
            c_max2 = pairs[i].c;
            break;
        }
    }
    // If not found, find the next pair where one of the generals is top.y
    if(c_max2 == -1){
        for(int i=1;i<total;i++) {
            if(pairs[i].x == top.y || pairs[i].y == top.y){
                c_max2 = pairs[i].c;
                break;
            }
        }
    }
    // If still not found, set to -1
    if(c_max2 == -1){
        printf("0\n");
        return 0;
    }
    // Now, to ensure Ha-han can achieve c_max2, check if it's possible
    // According to the analysis, it is always possible
    printf("1\n%lld\n", c_max2);
    free(pairs);
    return 0;
}