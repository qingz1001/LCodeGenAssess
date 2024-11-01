#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

typedef struct {
    int x, y;
} Point;

int cmp(const void *a, const void *b) {
    Point *p1 = (Point*)a;
    Point *p2 = (Point*)b;
    if (p1->x != p2->x)
        return p1->x - p2->x;
    return p1->y - p2->y;
}

ll cross(const Point *O, const Point *A, const Point *B) {
    ll val = (ll)(A->x - O->x) * (B->y - O->y) - (ll)(A->y - O->y) * (B->x - O->x);
    return val;
}

int convex_hull(Point *pts, int n, Point *hull) {
    int k = 0;
    // Lower hull
    for(int i=0;i<n;i++) {
        while(k >=2 && cross(&hull[k-2], &hull[k-1], &pts[i]) <=0) k--;
        hull[k++] = pts[i];
    }
    // Upper hull
    int t = k+1;
    for(int i=n-2;i>=0;i--) {
        while(k >= t && cross(&hull[k-2], &hull[k-1], &pts[i]) <=0) k--;
        hull[k++] = pts[i];
    }
    if(k >1) k--;
    return k;
}

int main(){
    int n;
    scanf("%d", &n);
    Point *pts = (Point*)malloc(n * sizeof(Point));
    for(int i=0;i<n;i++) scanf("%d %d", &pts[i].x, &pts[i].y);
    qsort(pts, n, sizeof(Point), cmp);
    Point *hull = (Point*)malloc(2*n * sizeof(Point));
    int m = convex_hull(pts, n, hull);
    free(pts);
    if(m ==1){
        printf("0\n");
        return 0;
    }
    // Rotating calipers
    ll max_dist = 0;
    int j =1;
    for(int i=0;i<m;i++){
        int ni = (i+1)%m;
        while(1){
            int nj = (j+1)%m;
            ll cross_val = cross(&hull[i], &hull[ni], &hull[nj]);
            ll cross_next = cross(&hull[i], &hull[ni], &hull[j]);
            if(cross_val > cross_next){
                j = nj;
            }
            else break;
        }
        ll dx = (ll)(hull[i].x - hull[j].x);
        ll dy = (ll)(hull[i].y - hull[j].y);
        ll dist = dx*dx + dy*dy;
        if(dist > max_dist) max_dist = dist;
    }
    printf("%lld\n", max_dist);
    free(hull);
}