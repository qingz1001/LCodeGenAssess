#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005

typedef struct Node {
    int id;
    struct Node* next;
} Node;

Node* children[MAXN];
int parent_arr[MAXN];
int in_time[MAXN];
int out_time[MAXN];
int timer = 1;
int n, q;

void add_child(int p, int c) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->id = c;
    node->next = children[p];
    children[p] = node;
}

void dfs(int u) {
    in_time[u] = timer;
    timer++;
    Node* ptr = children[u];
    while(ptr) {
        dfs(ptr->id);
        ptr = ptr->next;
    }
    out_time[u] = timer - 1;
}

long long segtree[4 * MAXN];
long long lazy[4 * MAXN];

void push_down(int node, int l, int r) {
    if(lazy[node] != -1){
        int mid = (l + r) / 2;
        segtree[node*2] = (mid - l +1)*lazy[node];
        segtree[node*2+1] = (r - mid)*lazy[node];
        lazy[node*2] = lazy[node];
        lazy[node*2+1] = lazy[node];
        lazy[node] = -1;
    }
}

void update_range(int node, int l, int r, int ul, int ur, int val){
    if(ul > r || ur < l) return;
    if(ul <= l && r <= ur){
        segtree[node] = (r - l +1)*val;
        lazy[node] = val;
        return;
    }
    push_down(node, l, r);
    int mid = (l + r) / 2;
    update_range(node*2, l, mid, ul, ur, val);
    update_range(node*2+1, mid+1, r, ul, ur, val);
    segtree[node] = segtree[node*2] + segtree[node*2+1];
}

long long query_range(int node, int l, int r, int ql, int qr){
    if(ql > r || qr < l) return 0;
    if(ql <= l && r <= qr){
        return segtree[node];
    }
    push_down(node, l, r);
    int mid = (l + r) / 2;
    return query_range(node*2, l, mid, ql, qr) + query_range(node*2+1, mid+1, r, ql, qr);
}

int main(){
    scanf("%d", &n);
    for(int i=1;i<n;i++){
        scanf("%d", &parent_arr[i]);
        add_child(parent_arr[i], i);
    }
    dfs(0);
    memset(lazy, -1, sizeof(lazy));
    scanf("%d", &q);
    char cmd[10];
    int x;
    while(q--){
        scanf("%s %d", cmd, &x);
        if(strcmp(cmd, "install") == 0){
            int cnt = 0;
            int path[MAXN];
            int top = 0;
            int cur = x;
            while(1){
                path[top++] = cur;
                if(cur == 0) break;
                cur = parent_arr[cur];
            }
            for(int i=top-1;i>=0;i--){
                int node_id = path[i];
                long long installed = query_range(1, 1, n, in_time[node_id], in_time[node_id]);
                if(!installed){
                    cnt++;
                    update_range(1, 1, n, in_time[node_id], in_time[node_id], 1);
                }
            }
            printf("%d\n", cnt);
        }
        else{
            long long installed = query_range(1, 1, n, in_time[x], in_time[x]);
            if(x != 0){
                long long total = query_range(1, 1, n, in_time[x], out_time[x]);
                if(total >0){
                    printf("%lld\n", total);
                    update_range(1, 1, n, in_time[x], out_time[x], 0);
                }
                else{
                    printf("0\n");
                }
            }
            else{
                long long total = query_range(1, 1, n, in_time[x], out_time[x]);
                if(total >0){
                    printf("%lld\n", total);
                    update_range(1, 1, n, in_time[x], out_time[x], 0);
                }
                else{
                    printf("0\n");
                }
            }
        }
    }
    return 0;
}