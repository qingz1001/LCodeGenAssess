#include<stdio.h>
#include<string.h>

long long dp[200][200];
int head_label[200];
int tail_label[200];
int main(){
    int N;
    scanf("%d", &N);
    int temp[100];
    for(int i=0;i<N;i++) scanf("%d", &temp[i]);
    for(int i=0;i<2*N;i++){
        head_label[i] = temp[i%N];
        if(i%N < N-1) tail_label[i] = temp[(i+1)%N];
        else tail_label[i] = temp[0];
    }
    for(int len=1; len<=N; len++){
        for(int i=0; i+len<=2*N; i++){
            int j = i + len;
            if(j >=2*N) continue;
            dp[i][j] = 0;
            for(int k=i; k<j; k++){
                long long temp_val = dp[i][k] + dp[k][j] + (long long)head_label[i] * tail_label[k] * tail_label[j];
                if(temp_val > dp[i][j]) dp[i][j] = temp_val;
            }
        }
    }
    long long max_energy=0;
    for(int i=0;i<N;i++) {
        if(dp[i][i+N] > max_energy) max_energy = dp[i][i+N];
    }
    printf("%lld", max_energy);
}