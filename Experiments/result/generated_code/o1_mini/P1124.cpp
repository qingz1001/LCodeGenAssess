#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10000
#define ALPHABET 26

int main(){
    int n, p;
    scanf("%d", &n);
    char S_dash[MAX+1];
    scanf("%s", S_dash);
    scanf("%d", &p);
    
    // Count frequency of each character
    int count[ALPHABET] = {0};
    for(int i=0;i<n;i++) {
        count[S_dash[i]-'a']++;
    }
    
    // Compute cumulative counts
    int cum_counts[ALPHABET] = {0};
    for(int i=1;i<ALPHABET;i++) {
        cum_counts[i] = cum_counts[i-1] + count[i-1];
    }
    
    // Reset counts for occurrence
    int occ[ALPHABET] = {0};
    int *next = (int*)malloc(n * sizeof(int));
    for(int i=0;i<n;i++) {
        int c = S_dash[i]-'a';
        next[i] = cum_counts[c] + occ[c];
        occ[c]++;
    }
    
    // Reconstruct S
    char S[MAX+1];
    int index = p-1;
    for(int j=n-1;j>=0;j--){
        S[j] = S_dash[index];
        index = next[index];
    }
    S[n] = '\0';
    
    printf("%s\n", S);
    free(next);
    return 0;
}