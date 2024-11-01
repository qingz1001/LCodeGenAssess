#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

typedef struct {
    int x, y;
} Point;

// Compare function for sorting points
int cmp(const void *a, const void *b) {
    Point *p1 = (Point*)a;
    Point *p2 = (Point*)b;
    if (p1->x != p2->x)
        return p1->x - p2->x;
    return p1->y - p2->y;
}

// Cross product
ll cross(Point O, Point A, Point B) {
    ll dx1 = A.x - O.x;
    ll dy1 = A.y - O.y;
    ll dx2 = B.x - O.x;
    ll dy2 = B.y - O.y;
    return dx1 * dy2 - dy1 * dx2;
}

// Squared distance
ll dist_sq(Point A, Point B) {
    ll dx = (ll)(A.x - B.x);
    ll dy = (ll)(A.y - B.y);
    return dx * dx + dy * dy;
}

int main(){
    int n;
    scanf("%d", &n);
    Point *pts = (Point*)malloc(sizeof(Point)*n);
    for(int i=0;i<n;i++) scanf("%d %d", &pts[i].x, &pts[i].y);
    qsort(pts, n, sizeof(Point), cmp);
    // Build lower hull
    Point *hull = (Point*)malloc(sizeof(Point)*(2*n));
    int k = 0;
    for(int i=0;i<n;i++){
        while(k >=2 && cross(hull[k-2], hull[k-1], pts[i]) <=0) k--;
        hull[k++] = pts[i];
    }
    // Build upper hull
    for(int i=n-2,t=k+1;i>=0;i--){
        while(k >=t && cross(hull[k-2], hull[k-1], pts[i]) <=0) k--;
        hull[k++] = pts[i];
    }
    if(k>1) k--;
    // Rotating calipers
    if(k ==1){
        printf("0\n");
        return 0;
    }
    ll maxd = 0;
    int j =1;
    for(int i=0;i<k;i++){
        int ni = (i+1)%k;
        while(1){
            int nj = (j+1)%k;
            ll cross1 = (hull[ni].x - hull[i].x)*(hull[nj].y - hull[j].y) - (hull[ni].y - hull[i].y)*(hull[nj].x - hull[j].x);
            if(cross1 >0) j = nj;
            else break;
        }
        ll d = dist_sq(hull[i], hull[j]);
        if(d > maxd) maxd = d;
    }
    printf("%lld\n", maxd);
    free(pts);
    free(hull);
    return 0;
}