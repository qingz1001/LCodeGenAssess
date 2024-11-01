#include <stdio.h>
#include <stdlib.h>

int main(){
    int n, t;
    if(scanf("%d %d", &n, &t)!=2){
        return 0;
    }
    for(int q=0; q<t; q++){
        int m;
        if(scanf("%d", &m)!=1){
            return 0;
        }
        int *S = (int *)malloc(m * sizeof(int));
        for(int i=0; i<m; i++){
            if(scanf("%d", &S[i])!=1){
                free(S);
                return 0;
            }
        }
        // Compute prefix function
        int *pi = (int *)malloc(m * sizeof(int));
        pi[0] = 0;
        for(int i=1; i<m; i++){
            int k = pi[i-1];
            while(k >0 && S[k] != S[i]){
                k = pi[k-1];
            }
            if(S[k] == S[i]){
                k +=1;
            }
            pi[i] = k;
        }
        // Compute E[i]
        // To handle E[fail[i}], we need E array from 0 to m
        // E[m] =0
        long long *E = (long long *)malloc((m +1) * sizeof(long long));
        E[m] =0;
        for(int i=m-1; i>=0; i--){
            int fail_i = pi[i];
            long long sum = (long long)n + E[i+1] + (long long)(n-1) * E[fail_i];
            long long modulo = (long long)n * 10000;
            sum = sum % modulo;
            E[i] = sum / n;
            E[i] = E[i] % 10000;
        }
        // Output E[0] with leading zeros
        printf("%04lld\n", E[0]);
        free(S);
        free(pi);
        free(E);
    }
    return 0;
}