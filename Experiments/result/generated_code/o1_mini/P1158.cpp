#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int d1;
    int d2;
} MissileD1;

typedef struct {
    int d2;
    int d1;
} MissileD2;

// Comparator for sorting by d1 ascending
int cmp_d1(const void *a, const void *b) {
    MissileD1 *m1 = (MissileD1 *)a;
    MissileD1 *m2 = (MissileD1 *)b;
    if (m1->d1 != m2->d1)
        return (m1->d1 - m2->d1);
    else
        return (m1->d2 - m2->d2);
}

// Comparator for sorting by d2 ascending
int cmp_d2(const void *a, const void *b) {
    MissileD2 *m1 = (MissileD2 *)a;
    MissileD2 *m2 = (MissileD2 *)b;
    if (m1->d2 != m2->d2)
        return (m1->d2 - m2->d2);
    else
        return (m1->d1 - m2->d1);
}

int main(){
    int x1, y1, x2, y2;
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
    int N;
    scanf("%d", &N);
    MissileD1 *missiles_d1 = (MissileD1*)malloc(N * sizeof(MissileD1));
    MissileD2 *missiles_d2 = (MissileD2*)malloc(N * sizeof(MissileD2));
    for(int i=0; i<N; i++){
        int x, y;
        scanf("%d %d", &x, &y);
        int dx1 = x - x1;
        int dy1 = y - y1;
        int dx2 = x - x2;
        int dy2 = y - y2;
        missiles_d1[i].d1 = dx1 * dx1 + dy1 * dy1;
        missiles_d1[i].d2 = dx2 * dx2 + dy2 * dy2;
        missiles_d2[i].d2 = dx2 * dx2 + dy2 * dy2;
        missiles_d2[i].d1 = dx1 * dx1 + dy1 * dy1;
    }

    // Sort by d1
    qsort(missiles_d1, N, sizeof(MissileD1), cmp_d1);
    // Sort by d2
    qsort(missiles_d2, N, sizeof(MissileD2), cmp_d2);

    // Compute suffix max for d2 in sorted by d1
    int *suffix_max_d2 = (int*)malloc((N+1) * sizeof(int));
    suffix_max_d2[N] = 0;
    for(int i=N-1; i>=0; i--){
        if(missiles_d1[i].d2 > suffix_max_d2[i+1])
            suffix_max_d2[i] = missiles_d1[i].d2;
        else
            suffix_max_d2[i] = suffix_max_d2[i+1];
    }

    // Compute suffix max for d1 in sorted by d2
    int *suffix_max_d1 = (int*)malloc((N+1) * sizeof(int));
    suffix_max_d1[N] = 0;
    for(int i=N-1; i>=0; i--){
        if(missiles_d2[i].d1 > suffix_max_d1[i+1])
            suffix_max_d1[i] = missiles_d2[i].d1;
        else
            suffix_max_d1[i] = suffix_max_d1[i+1];
    }

    // Iterate sorted by d1
    long long min_sum = (long long)1e18;
    for(int k=0; k<=N; k++){
        int r1, r2;
        if(k ==0){
            r1 = 0;
            r2 = (N>0)? suffix_max_d2[0] : 0;
        }
        else if(k ==N){
            r1 = missiles_d1[N-1].d1;
            r2 = 0;
        }
        else{
            r1 = missiles_d1[k-1].d1;
            r2 = suffix_max_d2[k];
        }
        long long current_sum = (long long)r1 + (long long)r2;
        if(current_sum < min_sum){
            min_sum = current_sum;
        }
    }

    // Iterate sorted by d2
    for(int k=0; k<=N; k++){
        int r1, r2;
        if(k ==0){
            r2 =0;
            r1 = (N>0)? suffix_max_d1[0] : 0;
        }
        else if(k ==N){
            r2 = missiles_d2[N-1].d2;
            r1 =0;
        }
        else{
            r2 = missiles_d2[k-1].d2;
            r1 = suffix_max_d1[k];
        }
        long long current_sum = (long long)r1 + (long long)r2;
        if(current_sum < min_sum){
            min_sum = current_sum;
        }
    }

    printf("%lld\n", min_sum);

    free(missiles_d1);
    free(missiles_d2);
    free(suffix_max_d2);
    free(suffix_max_d1);
    return 0;
}