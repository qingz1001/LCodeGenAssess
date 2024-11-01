#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXN 100005
#define MAXLEN 16

char words[MAXN][MAXLEN];
int segTree[4 * MAXN];
int N, M;

// Function to compare two words case-insensitively.
// Returns 1 if idx1 is greater, 2 if idx2 is greater.
int compare(int idx1, int idx2){
    char *a = words[idx1];
    char *b = words[idx2];
    int i = 0;
    while(a[i] && b[i]){
        char ca = tolower(a[i]);
        char cb = tolower(b[i]);
        if(ca > cb) return 1;
        if(ca < cb) return 2;
        i++;
    }
    if(a[i] && !b[i]) return 1;
    if(!a[i] && b[i]) return 2;
    // They are equal case-insensitively, return the one with higher index
    if(idx1 > idx2) return 1;
    else return 2;
}

int build(int node, int l, int r){
    if(l == r){
        segTree[node] = l;
        return segTree[node];
    }
    int mid = (l + r) / 2;
    int left = build(2*node, l, mid);
    int right = build(2*node+1, mid+1, r);
    if(compare(left, right) == 1){
        segTree[node] = left;
    }
    else{
        segTree[node] = right;
    }
    return segTree[node];
}

int query(int node, int l, int r, int ql, int qr){
    if(ql > r || qr < l){
        return -1;
    }
    if(ql <= l && r <= qr){
        return segTree[node];
    }
    int mid = (l + r) / 2;
    int left = query(2*node, l, mid, ql, qr);
    int right = query(2*node+1, mid+1, r, ql, qr);
    if(left == -1) return right;
    if(right == -1) return left;
    if(compare(left, right) == 1){
        return left;
    }
    else{
        return right;
    }
}

int main(){
    scanf("%d %d", &N, &M);
    for(int i=0;i<N;i++){
        scanf("%s", words[i]);
    }
    build(1, 0, N-1);
    for(int i=0;i<M;i++){
        int x, y;
        scanf("%d %d", &x, &y);
        int res = query(1, 0, N-1, x-1, y-1);
        printf("%s\n", words[res]);
    }
    return 0;
}