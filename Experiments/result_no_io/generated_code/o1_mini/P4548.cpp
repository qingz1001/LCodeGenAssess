#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long ull;

// Function to compute the prefix function (KMP failure function)
void compute_prefix(int m, int *P, int *pi){
    pi[0] = 0;
    for(int i=1;i<m;i++){
        int j = pi[i-1];
        while(j >0 && P[j]!=P[i]){
            j = pi[j-1];
        }
        if(P[j]==P[i]){
            j++;
        }
        pi[i] = j;
    }
}

int main(){
    int n, t;
    scanf("%d %d", &n, &t);
    while(t--){
        int m;
        scanf("%d", &m);
        int *P = (int*)malloc(sizeof(int)*m);
        for(int i=0;i<m;i++) scanf("%d", &P[i]);
        int *pi = (int*)malloc(sizeof(int)*m);
        compute_prefix(m, P, pi);
        ull *E = (ull*)malloc(sizeof(ull)*(m+1));
        E[m] = 0;
        for(int k = m-1; k >=0; k--){
            if(n ==1){
                E[k] = 1 + E[k+1];
            }
            else{
                // Compute (n + E[k+1] + (n-1)*E[pi[k]]) /n
                // To prevent overflow, use unsigned long long
                ull numerator = n + E[k+1] + (ull)(n-1)*E[pi[k]];
                E[k] = numerator / n;
            }
        }
        ull result;
        if(n ==1){
            result = E[0];
        }
        else{
            result = E[0] % 10000;
        }
        // If n !=1, E[0] was computed correctly
        // If n ==1, E[0] =m
        if(n ==1){
            result = E[0] % 10000;
        }
        printf("%04llu\n", result);
        free(P);
        free(pi);
        free(E);
    }
    return 0;
}