#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAXN 501
#define INF 1000000000

int main(){
    int n, A;
    scanf("%d %d", &A, &n);
    int cost[MAXN][MAXN];
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            scanf("%d", &cost[i][j]);
            if(cost[i][j] == 0 && i != j){
                cost[i][j] = 2*A;
            }
            if(i == j){
                cost[i][j] = 0;
            } else {
                if(cost[i][j] < 2*A){
                    cost[i][j] = 2*A - cost[i][j];
                }
                else{
                    cost[i][j] = 0;
                }
            }
        }
    }

    int N = n;
    int max_match = 0;
    int Lx[MAXN], Ly[MAXN];
    int xy[MAXN], yx[MAXN];
    int slack[MAXN];
    int slackx[MAXN];
    int prevv[MAXN];
    int S[MAXN], T_flag[MAXN];
    int q[MAXN], head, tail;

    memset(xy, -1, sizeof(xy));
    memset(yx, -1, sizeof(yx));

    for(int i=0;i<N;i++) {
        Lx[i] = 0;
        for(int j=0;j<N;j++) {
            if(cost[i][j] > Lx[i]) Lx[i] = cost[i][j];
        }
    }

    for(int x=0;x<N;x++) {
        memset(S, 0, sizeof(S));
        memset(T_flag, 0, sizeof(T_flag));
        memset(prevv, -1, sizeof(prevv));
        for(int i=0;i<N;i++) slack[i] = INF;
        head = tail = 0;
        q[tail++] = x;
        S[x] = 1;
        for(int y=0;y<N;y++) {
            slack[y] = Lx[x] + Ly[y] - cost[x][y];
            slackx[y] = x;
        }

        int matched = -1;
        while(1){
            while(head < tail){
                int u = q[head++];
                for(int v=0; v<N; v++) {
                    if(cost[u][v] == 0) continue;
                    if(Lx[u] + Ly[v] == cost[u][v] && !T_flag[v]){
                        if(yx[v] == -1){
                            matched = v;
                            break;
                        }
                        T_flag[v] = 1;
                        q[tail++] = yx[v];
                        S[yx[v]] = 1;
                        for(int k=0;k<N;k++) {
                            if(Lx[yx[v]] + Ly[k] - cost[yx[v]][k] < slack[k]){
                                slack[k] = Lx[yx[v]] + Ly[k] - cost[yx[v]][k];
                                slackx[k] = yx[v];
                            }
                        }
                    }
                }
                if(matched != -1) break;
            }
            if(matched != -1) break;

            int delta = INF;
            for(int y=0;y<N;y++) {
                if(!T_flag[y] && slack[y] < delta){
                    delta = slack[y];
                }
            }
            for(int i=0;i<N;i++) {
                if(S[i]) Lx[i] -= delta;
            }
            for(int y=0;y<N;y++) {
                if(T_flag[y]) Ly[y] += delta;
                else slack[y] -= delta;
            }
            for(int y=0;y<N;y++) {
                if(!T_flag[y] && slack[y] == 0){
                    if(yx[y] == -1){
                        matched = y;
                        break;
                    }
                    T_flag[y] = 1;
                    if(!S[yx[y]]){
                        q[tail++] = yx[y];
                        S[yx[y]] = 1;
                        for(int k=0;k<N;k++){
                            if(Lx[yx[y]] + Ly[k] - cost[yx[y]][k] < slack[k]){
                                slack[k] = Lx[yx[y]] + Ly[k] - cost[yx[y]][k];
                                slackx[k] = yx[y];
                            }
                        }
                    }
                }
            }
            if(matched != -1) break;
        }

        if(matched != -1){
            max_match++;
            int y = matched;
            while(y != -1){
                int x_prev = slackx[y];
                int y_prev = xy[x_prev];
                xy[x_prev] = y;
                yx[y] = x_prev;
                y = y_prev;
            }
        }
    }

    long long total = (long long)n * A;
    for(int x=0;x<N;x++) {
        if(xy[x] != -1 && x < xy[x]){
            int y = xy[x];
            total -= (2*A - (2*A - cost[x][y]));
        }
    }

    // Alternatively, calculate total cost directly
    long long sum = 0;
    for(int x=0; x<N; x++) {
        if(xy[x] != -1 && x < xy[x]){
            int y = xy[x];
            sum += (2*A - cost[x][y]);
        }
    }
    long long answer = (long long)n * A - sum;
    printf("%lld\n", answer);
}