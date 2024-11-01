#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 10000

int main(){
    int n, p;
    scanf("%d", &n);
    char S_prime[MAX_N+1];
    scanf("%s", S_prime);
    scanf("%d", &p);
    
    // Count frequency of each character
    int count[26] = {0};
    for(int i=0;i<n;i++) count[S_prime[i]-'a']++;
    
    // Compute C[c]: total number of characters less than c
    int C[26];
    C[0] = 0;
    for(int c=1; c<26; c++) C[c] = C[c-1] + count[c-1];
    
    // Build LF mapping
    int lf[MAX_N];
    int occ[26] = {0};
    for(int i=0;i<n;i++){
        int c = S_prime[i]-'a';
        lf[i] = C[c] + occ[c];
        occ[c]++;
    }
    
    // Reconstruct S
    char S[MAX_N+1];
    S[n] = '\0';
    int row = p-1;
    for(int k=0; k<n; k++){
        char c = S_prime[row];
        S[n-1 -k] = c;
        row = lf[row];
    }
    
    printf("%s\n", S);
    return 0;
}