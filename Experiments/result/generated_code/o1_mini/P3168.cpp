#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

typedef struct Node {
    int left, right;
    int count;
    ll sum;
} Node;

#define MAXN 200005
#define MAXNODE 8000000

Node nodes[MAXNODE];
int node_cnt = 0;
int roots[MAXN];
ll p_sorted[MAXN];
int p_size;

int build(int l, int r) {
    int idx = node_cnt++;
    nodes[idx].count = 0;
    nodes[idx].sum = 0;
    if(l == r) {
        nodes[idx].left = nodes[idx].right = -1;
    }
    else {
        int mid = (l + r) / 2;
        nodes[idx].left = build(l, mid);
        nodes[idx].right = build(mid+1, r);
    }
    return idx;
}

int update_node(int prev, int l, int r, int pos, int delta, ll p_val) {
    int idx = node_cnt++;
    nodes[idx] = nodes[prev];
    if(l == r) {
        nodes[idx].count += delta;
        nodes[idx].sum += delta * p_val;
        return idx;
    }
    int mid = (l + r) / 2;
    if(pos <= mid) {
        nodes[idx].left = update_node(nodes[prev].left, l, mid, pos, delta, p_val);
    }
    else {
        nodes[idx].right = update_node(nodes[prev].right, mid+1, r, pos, delta, p_val);
    }
    nodes[idx].count = nodes[nodes[idx].left].count + nodes[nodes[idx].right].count;
    nodes[idx].sum = nodes[nodes[idx].left].sum + nodes[nodes[idx].right].sum;
    return idx;
}

ll query_sum(int node, int l, int r, int k) {
    if(l == r) {
        ll cnt = nodes[node].count;
        if(cnt >= k) return (ll)k * p_sorted[l];
        else return (ll)cnt * p_sorted[l];
    }
    int mid = (l + r) / 2;
    if(nodes[nodes[node].left].count >= k) {
        return query_sum(nodes[node].left, l, mid, k);
    }
    else {
        ll left_sum = nodes[nodes[node].left].sum;
        ll right_sum = query_sum(nodes[node].right, mid+1, r, k - nodes[nodes[node].left].count);
        return left_sum + right_sum;
    }
}

int cmp_ll(const void *a, const void *b) {
    ll va = *(ll*)a;
    ll vb = *(ll*)b;
    if(va < vb) return -1;
    if(va > vb) return 1;
    return 0;
}

typedef struct Event {
    int time;
    int type; // 1 add, -1 remove
    int p_idx;
} Event;

int cmp_event(const void *a, const void *b) {
    Event *ea = (Event*)a;
    Event *eb = (Event*)b;
    if(ea->time != eb->time) return ea->time - eb->time;
    return ea->type - eb->type;
}

int main(){
    int m, n;
    scanf("%d %d", &m, &n);
    int *s = (int*)malloc(sizeof(int)*m);
    int *e = (int*)malloc(sizeof(int)*m);
    ll *p = (ll*)malloc(sizeof(ll)*m);
    for(int i=0;i<m;i++) {
        scanf("%d %d %lld", &s[i], &e[i], &p[i]);
    }
    // Collect and sort p
    for(int i=0;i<m;i++) p_sorted[i+1] = p[i];
    p_size = m;
    qsort(p_sorted+1, p_size, sizeof(ll), cmp_ll);
    int unique_p = 1;
    for(int i=2;i<=p_size;i++) {
        if(p_sorted[i] != p_sorted[unique_p]) {
            unique_p++;
            p_sorted[unique_p] = p_sorted[i];
        }
    }
    p_size = unique_p;
    // Create events
    Event *events = (Event*)malloc(sizeof(Event)*2*m);
    int ev_cnt = 0;
    for(int i=0;i<m;i++) {
        // Add
        events[ev_cnt].time = s[i];
        events[ev_cnt].type = 1;
        // Find p_idx
        ll val = p[i];
        int left = 1, right = p_size, pos = 1;
        while(left <= right){
            int mid = (left + right)/2;
            if(p_sorted[mid] == val){
                pos = mid;
                break;
            }
            else if(p_sorted[mid] < val){
                left = mid +1;
            }
            else{
                right = mid -1;
            }
        }
        events[ev_cnt].p_idx = pos;
        ev_cnt++;
        // Remove
        events[ev_cnt].time = e[i]+1;
        events[ev_cnt].type = -1;
        events[ev_cnt].p_idx = pos;
        ev_cnt++;
    }
    qsort(events, ev_cnt, sizeof(Event), cmp_event);
    // Build persistent segment tree
    int root_prev = build(1, p_size);
    int ev_ptr = 0;
    for(int time=1; time<=n; time++) {
        int current = root_prev;
        while(ev_ptr < ev_cnt && events[ev_ptr].time == time){
            if(events[ev_ptr].type == 1){
                current = update_node(current, 1, p_size, events[ev_ptr].p_idx, 1, p_sorted[events[ev_ptr].p_idx]);
            }
            else{
                current = update_node(current, 1, p_size, events[ev_ptr].p_idx, -1, p_sorted[events[ev_ptr].p_idx]);
            }
            ev_ptr++;
        }
        roots[time] = current;
        root_prev = current;
    }
    // Process queries
    ll pre = 1;
    for(int i=0;i<n;i++) {
        int x_i;
        ll a_i, b_i;
        int c_i;
        scanf("%d %lld %lld %d", &x_i, &a_i, &b_i, &c_i);
        ll k_i = 1 + ((a_i * pre) + b_i) % c_i;
        int total = nodes[roots[x_i]].count;
        if(k_i > total) k_i = total;
        ll sum = 0;
        if(k_i > 0){
            sum = query_sum(roots[x_i], 1, p_size, k_i);
        }
        printf("%lld\n", sum);
        pre = sum;
    }
    free(s);
    free(e);
    free(p);
    free(events);
    return 0;
}