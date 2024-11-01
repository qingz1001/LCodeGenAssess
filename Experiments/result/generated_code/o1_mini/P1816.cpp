#include <stdio.h>
#include <math.h>

#define MAX_M 100005
#define MAX_LOG 17

int main(){
    int m, n;
    scanf("%d %d", &m, &n);
    int a[MAX_M];
    for(int i=1;i<=m;i++) scanf("%d", &a[i]);
    
    int log_table[MAX_M+1];
    log_table[1] = 0;
    for(int i=2;i<=m;i++) {
        log_table[i] = log_table[i/2] + 1;
    }
    
    int st[MAX_LOG][MAX_M];
    for(int i=1;i<=m;i++) st[0][i] = a[i];
    for(int j=1; j<MAX_LOG; j++){
        for(int i=1; i + (1<<j) -1 <= m; i++){
            if(st[j-1][i] < st[j-1][i + (1<<(j-1))])
                st[j][i] = st[j-1][i];
            else
                st[j][i] = st[j-1][i + (1<<(j-1))];
        }
    }
    
    int a_q, b_q;
    int k;
    int res;
    for(int i=0;i<n;i++){
        scanf("%d %d", &a_q, &b_q);
        if(a_q > b_q){
            int temp = a_q;
            a_q = b_q;
            b_q = temp;
        }
        k = log_table[b_q - a_q +1];
        if(st[k][a_q] < st[k][b_q - (1<<k) +1])
            res = st[k][a_q];
        else
            res = st[k][b_q - (1<<k) +1];
        if(i != 0) printf(" ");
        printf("%d", res);
    }
    printf("\n");
    return 0;
}