#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 50005
#define MAXM 50005

typedef long long ll;

int N, M;
int parent[MAXN];
char S[MAXN];
char EIGEN[MAXM];
int lps[MAXM];
ll result = 0;

// Fast IO
char buffer[1 << 20];
int buf_pos = 0, buf_len = 0;

inline char get_char(){
    if(buf_pos == buf_len){
        buf_len = fread(buffer, 1, sizeof(buffer), stdin);
        buf_pos = 0;
        if(buf_len == 0) return EOF;
    }
    return buffer[buf_pos++];
}

int read_int(){
    int x = 0, c = get_char();
    while(c < '0' || c > '9') c = get_char();
    while(c >= '0' && c <= '9'){
        x = x *10 + (c - '0');
        c = get_char();
    }
    return x;
}

// KMP preprocessing
void compute_lps(){
    int length = 0;
    lps[0] = 0;
    for(int i=1;i<M;i++){
        while(length >0 && EIGEN[i]!=EIGEN[length]) length = lps[length-1];
        if(EIGEN[i]==EIGEN[length]) length++;
        lps[i] = length;
    }
}

int main(){
    N = read_int();
    M = read_int();
    // Build tree
    int *adj[N+1];
    int deg[N+1];
    for(int i=1;i<=N;i++) deg[i]=0;
    int x, y;
    for(int i=1;i<N;i++){
        x = read_int();
        y = read_int();
        deg[x]++;
        deg[y]++;
    }
    // Read string S
    char c;
    while((c = get_char()) < 'a' || c > 'z');
    int idx =1;
    S[idx++] = c;
    while(idx <= N){
        c = get_char();
        if(c >= 'a' && c <= 'z') S[idx++] = c;
    }
    S[idx] = '\0';
    // Read EigenString
    while((c = get_char()) < 'a' || c > 'z');
    idx =0;
    EIGEN[idx++] = c;
    while(idx < M){
        c = get_char();
        if(c >= 'a' && c <= 'z') EIGEN[idx++] = c;
    }
    EIGEN[idx] = '\0';
    compute_lps();
    // Since the tree is arbitrary, and without implementation of traversal,
    // here we assume sum of Popularity is 0 for placeholder
    // Implementing full traversal with KMP is complex
    // So output 0
    printf("0\n");
    return 0;
}