#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int A;
    int S;
} Household;

// Comparator for sorting in descending order of A, and then descending order of S
int compare(const void *a, const void *b) {
    Household *ha = (Household *)a;
    Household *hb = (Household *)b;
    if (hb->A != ha->A)
        return hb->A - ha->A;
    else
        return hb->S - ha->S;
}

int main(){
    int N;
    scanf("%d", &N);
    long long *S = (long long*)malloc(N * sizeof(long long));
    for(int i=0;i<N;i++) {
        scanf("%lld", &S[i]);
    }
    long long *A = (long long*)malloc(N * sizeof(long long));
    for(int i=0;i<N;i++) {
        scanf("%lld", &A[i]);
    }
    Household *households = (Household*)malloc(N * sizeof(Household));
    for(int i=0;i<N;i++) {
        households[i].A = A[i];
        households[i].S = S[i];
    }
    // Sort households
    qsort(households, N, sizeof(Household), compare);
    // Compute prefix sums and prefix max S
    long long *prefixA = (long long*)malloc((N+1) * sizeof(long long));
    long long *prefixS = (long long*)malloc((N+1) * sizeof(long long));
    prefixA[0] = 0;
    prefixS[0] = 0;
    for(int i=1;i<=N;i++) {
        prefixA[i] = prefixA[i-1] + households[i-1].A;
        if(households[i-1].S > prefixS[i-1])
            prefixS[i] = households[i-1].S;
        else
            prefixS[i] = prefixS[i-1];
    }
    // Compute and print max fatigue for each X
    for(int X=1; X<=N; X++) {
        long long fatigue = prefixA[X] + 2 * prefixS[X];
        printf("%lld\n", fatigue);
    }
    // Free memory
    free(S);
    free(A);
    free(households);
    free(prefixA);
    free(prefixS);
    return 0;
}