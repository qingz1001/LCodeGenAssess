#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int L;
    int R;
} Substring;

char S_global[100005];
int cmp_sa(const void *a, const void *b) {
    int i = *(const int*)a;
    int j = *(const int*)b;
    return strcmp(&S_global[i], &S_global[j]) > 0 ? -1 :
           strcmp(&S_global[i], &S_global[j]) < 0 ? 1 : 0;
}

int main(){
    // Read string
    scanf("%s", S_global);
    int N = strlen(S_global);
    // Read V_i
    int V[N];
    for(int i=0;i<N;i++) scanf("%d", &V[i]);
    // Compute prefix sums
    long long prefix_sum[N+1];
    prefix_sum[0] = 0;
    for(int i=0;i<N;i++) prefix_sum[i+1] = prefix_sum[i] + V[i];
    // Build suffix array
    int SA[N];
    for(int i=0;i<N;i++) SA[i] = i;
    qsort(SA, N, sizeof(int), cmp_sa);
    // Build rank array
    int rank_arr[N];
    for(int i=0;i<N;i++) rank_arr[SA[i]] = i;
    // Build LCP array using Kasai's algorithm
    int LCP[N];
    for(int i=0;i<N;i++) LCP[i] = 0;
    int k = 0;
    for(int i=0;i<N;i++){
        if(rank_arr[i] == 0){
            k = 0;
            continue;
        }
        int j = SA[rank_arr[i]-1];
        while(i + k < N && j + k < N && S_global[i + k] == S_global[j + k]) k++;
        LCP[rank_arr[i]] = k;
        if(k > 0) k--;
    }
    // Enumerate substrings and assign ranks
    Substring substrs[100005];
    int S_count = 0;
    long long rank = 1;
    for(int i=0;i<N;i++){
        int lcp = LCP[i];
        int len = N - SA[i];
        for(int j=lcp +1; j<=len; j++){
            int L = SA[i] +1;
            int R = SA[i] + j;
            if(R > N) break;
            long long sum = prefix_sum[R] - prefix_sum[SA[i]];
            if(sum == rank){
                if(S_count < 100000){
                    substrs[S_count].L = L;
                    substrs[S_count].R = R;
                    S_count++;
                }
            }
            rank++;
            if(S_count >= 100000) break;
        }
        if(S_count >= 100000) break;
    }
    // Sort the substrings by L then R
    int cmp_substrings(const void *a, const void *b){
        Substring *s1 = (Substring*)a;
        Substring *s2 = (Substring*)b;
        if(s1->L != s2->L) return s1->L - s2->L;
        return s1->R - s2->R;
    }
    qsort(substrs, S_count, sizeof(Substring), cmp_substrings);
    // Output
    printf("%d\n", S_count);
    for(int i=0;i<S_count;i++) printf("%d %d\n", substrs[i].L, substrs[i].R);
    return 0;
}