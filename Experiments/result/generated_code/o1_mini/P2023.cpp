#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

typedef struct {
    int left, right;
    ll sum;
    ll mul_lazy;
    ll add_lazy;
} node;

int n, m;
ll p;
ll a_initial[100005];
node segtree[400020];

void build(int idx, int l, int r){
    segtree[idx].left = l;
    segtree[idx].right = r;
    segtree[idx].mul_lazy = 1;
    segtree[idx].add_lazy = 0;
    if(l == r){
        segtree[idx].sum = a_initial[l];
        return;
    }
    int mid = (l + r) / 2;
    build(idx*2, l, mid);
    build(idx*2+1, mid+1, r);
    segtree[idx].sum = segtree[idx*2].sum + segtree[idx*2+1].sum;
}

void pushdown(int idx){
    ll mul = segtree[idx].mul_lazy;
    ll add = segtree[idx].add_lazy;
    if(mul != 1 || add != 0){
        int left = idx*2;
        int right = idx*2+1;
        segtree[left].sum = segtree[left].sum * mul + (segtree[left].right - segtree[left].left +1) * add;
        segtree[right].sum = segtree[right].sum * mul + (segtree[right].right - segtree[right].left +1) * add;
        segtree[left].mul_lazy *= mul;
        segtree[left].add_lazy = segtree[left].add_lazy * mul + add;
        segtree[right].mul_lazy *= mul;
        segtree[right].add_lazy = segtree[right].add_lazy * mul + add;
        segtree[idx].mul_lazy = 1;
        segtree[idx].add_lazy = 0;
    }
}

void update_mul(int idx, int l, int r, ll c){
    if(segtree[idx].left > r || segtree[idx].right < l){
        return;
    }
    if(l <= segtree[idx].left && segtree[idx].right <= r){
        segtree[idx].sum *= c;
        segtree[idx].mul_lazy *= c;
        segtree[idx].add_lazy *= c;
        return;
    }
    pushdown(idx);
    update_mul(idx*2, l, r, c);
    update_mul(idx*2+1, l, r, c);
    segtree[idx].sum = segtree[idx*2].sum + segtree[idx*2+1].sum;
}

void update_add(int idx, int l, int r, ll c){
    if(segtree[idx].left > r || segtree[idx].right < l){
        return;
    }
    if(l <= segtree[idx].left && segtree[idx].right <= r){
        segtree[idx].sum += (segtree[idx].right - segtree[idx].left +1) * c;
        segtree[idx].add_lazy += c;
        return;
    }
    pushdown(idx);
    update_add(idx*2, l, r, c);
    update_add(idx*2+1, l, r, c);
    segtree[idx].sum = segtree[idx*2].sum + segtree[idx*2+1].sum;
}

ll query_sum(int idx, int l, int r){
    if(segtree[idx].left > r || segtree[idx].right < l){
        return 0;
    }
    if(l <= segtree[idx].left && segtree[idx].right <= r){
        return segtree[idx].sum;
    }
    pushdown(idx);
    return query_sum(idx*2, l, r) + query_sum(idx*2+1, l, r);
}

int main(){
    scanf("%d %lld", &n, &p);
    for(int i=1;i<=n;i++) scanf("%lld", &a_initial[i]);
    build(1,1,n);
    scanf("%d", &m);
    for(int i=0;i<m;i++){
        int type, t, g;
        ll c;
        scanf("%d", &type);
        if(type ==1){
            scanf("%d %d %lld", &t, &g, &c);
            update_mul(1, t, g, c);
        }
        else if(type ==2){
            scanf("%d %d %lld", &t, &g, &c);
            update_add(1, t, g, c);
        }
        else{
            scanf("%d %d", &t, &g);
            ll res = query_sum(1, t, g);
            if(p ==0) printf("%lld\n", res);
            else printf("%lld\n", res % p);
        }
    }
    return 0;
}