#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

typedef struct {
    ll sum;
    int set;
} Node;

int m_global;
Node tree_nodes[400005];
ll room_cnt[100005];
int person_room_arr[100005];
int n_global;

void build(int node, int l, int r) {
    tree_nodes[node].set = 0;
    if(l == r){
        tree_nodes[node].sum = room_cnt[l];
        return;
    }
    int mid = (l + r) /2;
    build(2*node, l, mid);
    build(2*node+1, mid+1, r);
    tree_nodes[node].sum = tree_nodes[2*node].sum + tree_nodes[2*node+1].sum;
}

void push_down(int node, int l, int r) {
    if(tree_nodes[node].set){
        int mid = (l + r)/2;
        tree_nodes[2*node].sum = 0;
        tree_nodes[2*node+1].sum = 0;
        tree_nodes[2*node].set = 1;
        tree_nodes[2*node+1].set = 1;
        tree_nodes[node].set = 0;
    }
}

ll query_sum(int node, int l, int r, int ql, int qr){
    if(ql > r || qr < l) return 0;
    if(ql <= l && r <= qr){
        return tree_nodes[node].sum;
    }
    push_down(node, l, r);
    int mid = (l + r)/2;
    return query_sum(2*node, l, mid, ql, qr) + query_sum(2*node+1, mid+1, r, ql, qr);
}

void range_set_zero(int node, int l, int r, int ql, int qr){
    if(ql > r || qr < l) return;
    if(ql <= l && r <= qr){
        tree_nodes[node].sum = 0;
        tree_nodes[node].set = 1;
        return;
    }
    push_down(node, l, r);
    int mid = (l + r)/2;
    range_set_zero(2*node, l, mid, ql, qr);
    range_set_zero(2*node+1, mid+1, r, ql, qr);
    tree_nodes[node].sum = tree_nodes[2*node].sum + tree_nodes[2*node+1].sum;
}

void point_update(int node, int l, int r, int pos, ll delta){
    if(l == r){
        tree_nodes[node].sum += delta;
        return;
    }
    push_down(node, l, r);
    int mid = (l + r)/2;
    if(pos <= mid){
        point_update(2*node, l, mid, pos, delta);
    }
    else{
        point_update(2*node+1, mid+1, r, pos, delta);
    }
    tree_nodes[node].sum = tree_nodes[2*node].sum + tree_nodes[2*node+1].sum;
}

int main(){
    int n, m, q;
    scanf("%d %d %d", &n, &m, &q);
    n_global = n;
    m_global = m;
    for(int i=1;i<=m;i++) room_cnt[i] = 0;
    room_cnt[1] = n;
    for(int i=1;i<=n;i++) person_room_arr[i] = 1;
    build(1,1,m);
    char cmd[2];
    for(int i=0;i<q;i++){
        scanf("%s", cmd);
        if(cmd[0] == 'C'){
            int x, y;
            scanf("%d %d", &x, &y);
            int a = person_room_arr[x];
            person_room_arr[x] = y;
            // Decrement from a
            point_update(1,1,m,a,-1);
            // Increment to y
            point_update(1,1,m,y,1);
        }
        else if(cmd[0] == 'W'){
            int l, r;
            scanf("%d %d", &l, &r);
            ll res = query_sum(1,1,m,l,r);
            printf("%lld\n", res);
            if(res >0){
                range_set_zero(1,1,m,l,r);
            }
        }
    }
}