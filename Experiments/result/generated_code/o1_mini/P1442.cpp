#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define INF 1000000000

typedef long long ll;

typedef struct {
    ll h;
    ll l;
    ll r;
    ll dp;
} Platform;

typedef struct {
    ll x;
} Coord;

int cmp_platform(const void *a, const void *b){
    Platform *pa = (Platform*)a;
    Platform *pb = (Platform*)b;
    if(pb->h != pa->h) return (pb->h > pa->h) - (pb->h < pa->h);
    if(pa->l != pb->l) return (pa->l > pb->l) - (pa->l < pb->l);
    return (pa->r > pb->r) - (pa->r < pb->r);
}

int cmp_coord(const void *a, const void *b){
    ll x1 = ((Coord*)a)->x;
    ll x2 = ((Coord*)b)->x;
    if(x1 < x2) return -1;
    if(x1 > x2) return 1;
    return 0;
}

ll get_coord(ll x, Coord *coords, int size){
    int left=0, right=size-1, mid;
    while(left <= right){
        mid=(left+right)/2;
        if(coords[mid].x == x) return mid;
        if(coords[mid].x < x) left=mid+1;
        else right=mid-1;
    }
    return -1;
}

ll compressed_x[MAXN*2];
int size_x=0;

typedef struct {
    ll max_h;
} SegmentTree;

SegmentTree segt[400020];
int N;

void update(int node, int l, int r, int ul, int ur, ll val){
    if(ur < l || ul > r) return;
    if(ul <= l && r <= ur){
        if(segt[node].max_h < val){
            segt[node].max_h = val;
        }
        return;
    }
    int mid = (l + r)/2;
    update(node*2, l, mid, ul, ur, val);
    update(node*2+1, mid+1, r, ul, ur, val);
    if(segt[node].max_h < segt[node*2].max_h) segt[node].max_h = segt[node*2].max_h;
    if(segt[node].max_h < segt[node*2+1].max_h) segt[node].max_h = segt[node*2+1].max_h;
}

ll query(int node, int l, int r, int pos){
    if(l == r){
        return segt[node].max_h;
    }
    int mid = (l + r)/2;
    if(pos <= mid) return segt[node].max_h > segt[node*2].max_h ? segt[node].max_h : query(node*2, l, mid, pos);
    else return segt[node].max_h > segt[node*2+1].max_h ? segt[node].max_h : query(node*2+1, mid+1, r, pos);
}

int main(){
    int n;
    ll H;
    scanf("%d %lld", &n, &H);
    
    Platform platforms[MAXN];
    ll init_x, init_y;
    scanf("%lld %lld", &init_x, &init_y);
    
    platforms[0].h = init_y;
    platforms[0].l = init_x;
    platforms[0].r = init_x;
    
    for(int i=1;i<=n;i++) {
        scanf("%lld %lld %lld", &platforms[i].h, &platforms[i].l, &platforms[i].r);
    }
    n++;
    
    // Add ground
    platforms[n].h = 0;
    platforms[n].l = -1000000001;
    platforms[n].r = 1000000001;
    
    n++;
    
    qsort(platforms, n, sizeof(Platform), cmp_platform);
    
    Coord coords[MAXN*2 + 2];
    size_x=0;
    for(int i=0;i<n;i++){
        coords[size_x++].x = platforms[i].l;
        coords[size_x++].x = platforms[i].r;
    }
    coords[size_x++].x = init_x;
    
    qsort(coords, size_x, sizeof(Coord), cmp_coord);
    int unique=0;
    for(int i=0;i<size_x;i++) {
        if(i==0 || coords[i].x != coords[i-1].x){
            compressed_x[unique] = coords[i].x;
            unique++;
        }
    }
    size_x = unique;
    
    // Sort platforms by h descending
    qsort(platforms, n, sizeof(Platform), cmp_platform);
    
    // Initialize dp
    ll dp[n];
    for(int i=0;i<n;i++) dp[i] = INF;
    dp[0] = 0; // initial position
    
    // Initialize segment tree
    memset(segt, 0, sizeof(segt));
    N = size_x;
    
    for(int i=0;i<n;i++){
        if(platforms[i].h == 0){
            // Ground
            dp[i] = 0;
        }
        else{
            // Find left
            ll x_left = platforms[i].l;
            int idx_left = get_coord(x_left, coords, size_x);
            if(idx_left == -1){
                // Find insertion point
                int left=0, right=size_x-1, mid, pos=-1;
                while(left <= right){
                    mid=(left+right)/2;
                    if(coords[mid].x < x_left){
                        left=mid+1;
                    }
                    else{
                        pos=mid;
                        right=mid-1;
                    }
                }
                idx_left = pos;
            }
            ll h_j_left = query(1, 0, N-1, idx_left);
            ll time_left;
            if(h_j_left > 0 && (platforms[i].h - h_j_left) <= H){
                // Find dp[j]
                // Binary search for h_j_left
                int j;
                for(j=0;j<n;j++) if(platforms[j].h == h_j_left) break;
                if(j < n) time_left = (platforms[i].h - h_j_left) + dp[j];
                else time_left = INF;
            }
            else{
                if(platforms[i].h <= H){
                    time_left = platforms[i].h;
                }
                else{
                    time_left = INF;
                }
            }
            
            // Find right
            ll x_right = platforms[i].r;
            int idx_right = get_coord(x_right, coords, size_x);
            if(idx_right == -1){
                // Find insertion point
                int left=0, right=size_x-1, mid, pos=-1;
                while(left <= right){
                    mid=(left+right)/2;
                    if(coords[mid].x < x_right){
                        left=mid+1;
                    }
                    else{
                        pos=mid;
                        right=mid-1;
                    }
                }
                idx_right = pos;
            }
            ll h_j_right = query(1, 0, N-1, idx_right);
            ll time_right;
            if(h_j_right > 0 && (platforms[i].h - h_j_right) <= H){
                // Find dp[j]
                int j;
                for(j=0;j<n;j++) if(platforms[j].h == h_j_right) break;
                if(j < n) time_right = (platforms[i].h - h_j_right) + dp[j];
                else time_right = INF;
            }
            else{
                if(platforms[i].h <= H){
                    time_right = platforms[i].h;
                }
                else{
                    time_right = INF;
                }
            }
            
            if(i == 0){
                dp[i] = (platforms[i].h - platforms[i].h) + ((platforms[i].h <= H) ? platforms[i].h : INF);
            }
            else{
                dp[i] = (time_left < time_right) ? time_left : time_right;
            }
        }
        // Update segment tree
        int ul, ur;
        // Find compressed indices
        // Left
        ll cl = platforms[i].l;
        int il = get_coord(cl, coords, size_x);
        if(il == -1){
            int left=0, right=size_x-1, mid, pos=-1;
            while(left <= right){
                mid=(left+right)/2;
                if(coords[mid].x < cl){
                    left=mid+1;
                }
                else{
                    pos=mid;
                    right=mid-1;
                }
            }
            il = pos;
        }
        // Right
        ll cr = platforms[i].r;
        int ir = get_coord(cr, coords, size_x);
        if(ir == -1){
            int left=0, right=size_x-1, mid, pos=-1;
            while(left <= right){
                mid=(left+right)/2;
                if(coords[mid].x < cr){
                    left=mid+1;
                }
                else{
                    pos=mid;
                    right=mid-1;
                }
            }
            ir = pos;
        }
        update(1, 0, N-1, il, ir-1, platforms[i].h);
    }
    
    // Find the initial dp
    ll result = INF;
    // Initial position is platforms[0]
    // It can drop down directly
    // Or roll to left or right
    // Here, dp[0] is already set
    result = dp[0];
    printf("%lld", result);
}