#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 20000
#define MAXLOG 15

long long s[MAXN];
int st[MAXLOG][MAXN];
int log_table[MAXN+1];

int max_idx(int a, int b) {
    return s[a] >= s[b] ? a : b;
}

int main(){
    int n;
    scanf("%d", &n);
    for(int i=0;i<n;i++) scanf("%lld", &s[i]);

    log_table[1]=0;
    for(int i=2;i<=n;i++) log_table[i]=log_table[i/2]+1;

    for(int i=0;i<n;i++) st[0][i]=i;
    for(int j=1; (1<<j)<=n; j++){
        for(int i=0; i + (1<<j) <=n; i++){
            int first = st[j-1][i];
            int second = st[j-1][i + (1<<(j-1))];
            st[j][i] = s[first] >= s[second] ? first : second;
        }
    }

    int Q;
    scanf("%d", &Q);
    long long x=0;
    while(Q--){
        int a, b, c, d;
        scanf("%d %d %d %d", &a, &b, &c, &d);
        a = (a + x) % n;
        b = (b + x) % n;
        c = (c + x) % n;
        d = (d + x) % n;
        int q[4] = {a, b, c, d};
        // Simple sort
        for(int i=0;i<3;i++) {
            for(int j=i+1;j<4;j++) {
                if(q[i] > q[j]){
                    int tmp = q[i];
                    q[i] = q[j];
                    q[j] = tmp;
                }
            }
        }
        a = q[0];
        b = q[1];
        c = q[2];
        d = q[3];
        int L = a;
        int R = d;
        int j_log = log_table[R - L +1];
        int idx1 = st[j_log][L];
        int idx2 = st[j_log][R - (1<<j_log) +1];
        int res = s[idx1] >= s[idx2] ? s[idx1] : s[idx2];
        printf("%d\n", res);
        x = res;
    }
}