#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to hold string and original index
typedef struct {
    char *str;
    int index;
} String;

int cmp(const void *a, const void *b) {
    String *sa = (String *)a;
    String *sb = (String *)b;
    return strcmp(sa->str, sb->str);
}

int main(){
    int n, q;
    scanf("%d %d", &n, &q);
    String *S = (String *)malloc(n * sizeof(String));
    char buffer[10005];
    for(int i=0;i<n;i++){
        scanf("%s", buffer);
        S[i].str = strdup(buffer);
        S[i].index = i+1;
    }
    // Read tasks but ignore for now
    int X, Y;
    for(int i=0;i<q;i++) {
        scanf("%d %d", &X, &Y);
    }
    // Sort strings lex order
    qsort(S, n, sizeof(String), cmp);
    // Compute W(P*_G)
    long long W = 0;
    for(int i=1;i<n;i++){
        int lcp = 0;
        char *a = S[i-1].str;
        char *b = S[i].str;
        while(a[lcp] && b[lcp] && a[lcp]==b[lcp]) lcp++;
        W += (long long)lcp * lcp;
    }
    printf("%lld\n", W);
    // Output tasks part: k=0
    printf("0\n");
    // Output permutation
    for(int i=0;i<n;i++){
        printf("%d%c", S[i].index, (i<n-1)?' ':'\n');
    }
    // Free memory
    for(int i=0;i<n;i++) free(S[i].str);
    free(S);
    return 0;
}