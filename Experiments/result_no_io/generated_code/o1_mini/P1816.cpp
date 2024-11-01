#include <stdio.h>
#include <math.h>

#define MAX 100005
#define LOG_MAX 20

int main(){
    int m, n;
    scanf("%d %d", &m, &n);
    int arr[m];
    for(int i=0;i<m;i++) scanf("%d", &arr[i]);

    // Compute log table
    int log_table[m+1];
    log_table[1]=0;
    for(int i=2;i<=m;i++) log_table[i] = log_table[i/2] +1;

    // Build sparse table
    int st[m][LOG_MAX];
    for(int i=0;i<m;i++) st[i][0] = arr[i];
    for(int j=1; (1<<j) <=m; j++){
        for(int i=0; i + (1<<j) <=m; i++){
            if(st[i][j-1] < st[i + (1<<(j-1))][j-1])
                st[i][j] = st[i][j-1];
            else
                st[i][j] = st[i + (1<<(j-1))][j-1];
        }
    }

    // Process queries
    for(int i=0;i<n;i++){
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;
        int length = b - a +1;
        int k = log_table[length];
        int minimum;
        if(st[a][k] < st[b - (1<<k) +1][k]) minimum = st[a][k];
        else minimum = st[b - (1<<k) +1][k];
        printf("%d%c", minimum, (i<n-1)?' ':'\n');
    }
    return 0;
}