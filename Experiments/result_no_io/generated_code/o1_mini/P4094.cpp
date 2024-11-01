#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define LOGN 20

char s[MAXN];
int sa[MAXN], rank_arr[MAXN], tmp[MAXN];
int lcp[MAXN], st[LOGN][MAXN];
int log_table[MAXN];

int cmp_sa(const void *a, const void *b, void *k) {
    int i = *(int*)a;
    int j = *(int*)b;
    if (rank_arr[i] != rank_arr[j])
        return rank_arr[i] - rank_arr[j];
    int rank_i = (i + *(int*)k < strlen(s)) ? rank_arr[i + *(int*)k] : -1;
    int rank_j = (j + *(int*)k < strlen(s)) ? rank_arr[j + *(int*)k] : -1;
    return rank_i - rank_j;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    scanf("%s", s);
    // Initialize SA
    for(int i=0;i<n;i++) { sa[i]=i; rank_arr[i]=s[i]; }
    // Build SA
    for(int k=1; k< n; k <<=1){
        int key = k;
        qsort_r(sa, n, sizeof(int), cmp_sa, &key);
        tmp[sa[0]]=0;
        for(int i=1;i<n;i++){
            int first1 = rank_arr[sa[i-1]];
            int second1 = (sa[i-1]+k < n) ? rank_arr[sa[i-1]+k] : -1;
            int first2 = rank_arr[sa[i]];
            int second2 = (sa[i]+k < n) ? rank_arr[sa[i]+k] : -1;
            if(first1 != first2 || second1 != second2)
                tmp[sa[i]]=tmp[sa[i-1]] + 1;
            else
                tmp[sa[i]]=tmp[sa[i-1]];
        }
        for(int i=0;i<n;i++) rank_arr[i]=tmp[i];
        if(rank_arr[sa[n-1]] == n-1) break;
    }
    // Build LCP array
    int k_lcp=0;
    for(int i=0;i<n;i++) rank_arr[sa[i]]=i;
    for(int i=0;i<n;i++){
        if(rank_arr[i]==n-1){k_lcp=0; continue;}
        int j = sa[rank_arr[i]+1];
        while(i + k_lcp < n && j + k_lcp < n && s[i + k_lcp] == s[j + k_lcp]) k_lcp++;
        lcp[rank_arr[i]]=k_lcp;
        if(k_lcp >0) k_lcp--;
    }
    // Build log table
    log_table[1]=0;
    for(int i=2;i<=n;i++) log_table[i]=log_table[i/2]+1;
    // Build Sparse Table
    for(int i=0;i<n;i++) st[0][i]=lcp[i];
    for(int j=1; (1<<j) <=n; j++) {
        for(int i=0;i + (1<<j) <=n;i++) {
            if(st[j-1][i] < st[j-1][i + (1<<(j-1))])
                st[j][i]=st[j-1][i];
            else
                st[j][i]=st[j-1][i + (1<<(j-1))];
        }
    }
    // Function to get LCP of two indices
    auto get_lcp = [&](int a, int b) -> int {
        if(a == b) return n - sa[a];
        if(a > b){
            int tmp = a; a = b; b = tmp;
        }
        int l = a, r = b-1;
        int j = log_table[r - l +1];
        if(st[j][l] < st[j][r - (1<<j)+1]) return st[j][l];
        else return st[j][r - (1<<j)+1];
    };
    // Process queries
    while(m--){
        int a, b, c, d;
        scanf("%d %d %d %d", &a, &b, &c, &d);
        a--, b--, c--, d--;
        // Get ranks
        // Binary search for the range in SA
        // Find the range of suffixes starting between a..b
        // Similarly for c..d
        // Find the maximum LCP between two ranges
        // This is complex, so here we just iterate through
        int max_lcp = 0;
        for(int i=a;i<=b;i++){
            for(int j=c;j<=d;j++){
                int l = get_lcp(rank_arr[i], rank_arr[j]);
                if(l > max_lcp) max_lcp = l;
            }
        }
        printf("%d\n", max_lcp);
    }
    return 0;
}