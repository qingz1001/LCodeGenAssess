#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXM 100005
#define MAXN 50005
#define MAXSAM 200005

typedef struct State {
    int len;
    int link;
    int next[26];
    long long cnt;
} State;

State sam[MAXSAM];
int size, last;

void sam_init() {
    memset(sam, 0, sizeof(State));
    sam[0].len = 0;
    sam[0].link = -1;
    size = 1;
    last = 0;
}

int sam_extend(char c) {
    int curr = size++;
    sam[curr].len = sam[last].len + 1;
    memset(sam[curr].next, -1, sizeof(sam[curr].next));
    sam[curr].cnt = 1;
    int p = last;
    while (p != -1 && sam[p].next[c] == -1) {
        sam[p].next[c] = curr;
        p = sam[p].link;
    }
    if (p == -1) {
        sam[curr].link = 0;
    }
    else {
        int q = sam[p].next[c];
        if (sam[p].len + 1 == sam[q].len) {
            sam[curr].link = q;
        }
        else {
            int clone = size++;
            sam[clone].len = sam[p].len + 1;
            memcpy(sam[clone].next, sam[q].next, sizeof(sam[q].next));
            sam[clone].link = sam[q].link;
            sam[clone].cnt = 0;
            while (p != -1 && sam[p].next[c] == q) {
                sam[p].next[c] = clone;
                p = sam[p].link;
            }
            sam[q].link = clone;
            sam[curr].link = clone;
        }
    }
    last = curr;
    return curr;
}

typedef struct Edge {
    int to;
    struct Edge* next;
} Edge;

Edge* adj[MAXN];
char labels[MAXN];
char eigen[50005];
int N, M;

void add_edge(int u, int v) {
    Edge* e = (Edge*)malloc(sizeof(Edge));
    e->to = v;
    e->next = adj[u];
    adj[u] = e;
}

long long total = 0;

// For counting occurrences
long long order[MAXSAM];
int cnt_len[MAXSAM];
long long occurrence[MAXSAM];

// DFS to traverse the tree and count
void dfs(int u, int parent_node, int current_state) {
    // Start a new path from u
    char c = labels[u - 1] - 'a';
    int state = current_state;
    while (state != -1 && sam[state].next[c] == -1) {
        state = sam[state].link;
    }
    if (state == -1) {
        state = 0;
    }
    else {
        state = sam[state].next[c];
    }
    total += sam[state].cnt;

    // Traverse children
    Edge* e = adj[u];
    while (e) {
        if (e->to != parent_node) {
            dfs(e->to, u, state);
        }
        e = e->next;
    }
}

int main(){
    scanf("%d %d", &N, &M);
    for(int i=0;i<N-1;i++){
        int x, y;
        scanf("%d %d", &x, &y);
        add_edge(x, y);
        add_edge(y, x);
    }
    scanf("%s", labels);
    scanf("%s", eigen);
    sam_init();
    for(int i=0;i<M;i++){
        sam_extend(eigen[i] - 'a');
    }
    // Counting occurrences
    // Counting sort based on len
    int max_len = 0;
    for(int i=0;i<size;i++) {
        if(sam[i].len > max_len) max_len = sam[i].len;
    }
    int* cnt = (int*)calloc(max_len+1, sizeof(int));
    for(int i=0;i<size;i++) {
        cnt[sam[i].len]++;
    }
    for(int i=1;i<=max_len;i++) {
        cnt[i] += cnt[i-1];
    }
    for(int i=0;i<size;i++) {
        order[--cnt[sam[i].len]] = i;
    }
    for(int i=size-1;i>=0;i--){
        int state = order[i];
        if(sam[state].link != -1){
            sam[sam[state].link].cnt += sam[state].cnt;
        }
    }
    // Traverse the tree and accumulate total
    dfs(1, -1, 0);
    printf("%lld\n", total);
    return 0;
}