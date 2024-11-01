#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAX_OUTPUT 100005

typedef long long ll;

// Suffix array using prefix-doubling
int sa[MAXN], rank_arr[MAXN], tmp[MAXN], n;
char S[MAXN];
int lcp_arr[MAXN];
int cnt[MAXN];
int* suffix_array(char *s, int n){
    int i, k, *sa_out = sa;
    for(i=0;i<n;i++){
        rank_arr[i] = s[i];
        sa_out[i] = i;
    }
    for(k=1; k< n; k <<=1){
        // Comparator
        int cmp(const void *a, const void *b){
            int x = *((int*)a);
            int y = *((int*)b);
            if(rank_arr[x] != rank_arr[y]) return rank_arr[y] - rank_arr[x];
            int rx = (x +k <n)? rank_arr[x +k]: -1;
            int ry = (y +k <n)? rank_arr[y +k]: -1;
            return ry - rx;
        }
        qsort(sa_out, n, sizeof(int), cmp);
        tmp[sa_out[0]] = 0;
        for(i=1;i<n;i++){
            int a = sa_out[i-1];
            int b = sa_out[i];
            if(rank_arr[a] != rank_arr[b]){
                tmp[b] = tmp[a] +1;
            }
            else{
                int ra = (a +k <n)? rank_arr[a +k]: -1;
                int rb = (b +k <n)? rank_arr[b +k]: -1;
                if(ra != rb){
                    tmp[b] = tmp[a] +1;
                }
                else{
                    tmp[b] = tmp[a];
                }
            }
        }
        for(i=0;i<n;i++) rank_arr[i] = tmp[i];
        if(rank_arr[sa_out[n-1]] == n-1) break;
    }
    return sa_out;
}

// Kasai's algorithm for LCP
int* compute_lcp(char *s, int n, int *sa){
    int i, j, k=0;
    int *rank_inv = tmp;
    for(i=0;i<n;i++) rank_inv[sa[i]] = i;
    for(i=0;i<n;i++){
        if(rank_inv[i]==n-1){
            k=0;
            continue;
        }
        j = sa[rank_inv[i]+1];
        while(i +k <n && j +k <n && s[i+k]==s[j+k]) k++;
        lcp_arr[rank_inv[i]] = k;
        if(k>0) k--;
    }
    return lcp_arr;
}

typedef struct{
    int L;
    int R;
} Pair;

int main(){
    scanf("%s", S);
    n = strlen(S);
    int V[MAXN];
    for(int i=0;i<n;i++) scanf("%d", &V[i]);
    // Compute prefix sum
    ll prefix_sum[MAXN];
    prefix_sum[0]=0;
    for(int i=0;i<n;i++) prefix_sum[i+1] = prefix_sum[i] + V[i];
    // Build suffix array
    int *sa_out = suffix_array(S, n);
    // Build LCP array
    compute_lcp(S, n, sa_out);
    // Traverse suffix array from last to first for descending order
    ll rank_num =1;
    Pair *results = (Pair*)malloc(sizeof(Pair)*MAX_OUTPUT);
    int res_cnt=0;
    for(int i=n-1;i>=0;i--){
        int pos = sa_out[i];
        int lcp = (i==0)?0:lcp_arr[i-1];
        int max_len = n - pos;
        for(int l = lcp +1; l <= max_len; l++){
            if(rank_num > MAX_OUTPUT) break;
            ll sum_v = prefix_sum[pos + l] - prefix_sum[pos];
            if(sum_v == rank_num){
                if(res_cnt < MAX_OUTPUT){
                    results[res_cnt].L = pos +1;
                    results[res_cnt].R = pos + l;
                    res_cnt++;
                }
            }
            rank_num++;
            if(rank_num > 100000) break;
        }
        if(rank_num > 100000) break;
    }
    // Sort the results by L ascending, then R ascending
    int cmp_pair(const void *a, const void *b){
        Pair pa = *((Pair*)a);
        Pair pb = *((Pair*)b);
        if(pa.L != pb.L) return pa.L - pb.L;
        return pa.R - pb.R;
    }
    qsort(results, res_cnt, sizeof(Pair), cmp_pair);
    // Output
    printf("%d\n", res_cnt);
    for(int i=0;i<res_cnt;i++) printf("%d %d\n", results[i].L, results[i].R);
    free(results);
    return 0;
}