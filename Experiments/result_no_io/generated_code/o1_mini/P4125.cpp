#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x1, y1, x2, y2;
} Segment;

int n;
Segment segments[1001];
int move_p[1001];
int move_q[1001];
int removed[1001];

int intersect(double a1, double b1, double a2, double b2,
             double c1, double d1, double c2, double d2) {
    double det = (a2 - a1)*(d2 - d1) - (b2 - b1)*(c2 - c1);
    if (fabs(det) < 1e-8) return 0;
    double t = ((c1 - a1)*(d2 - d1) - (d1 - b1)*(c2 - c1)) / det;
    double u = ((c1 - a1)*(b2 - b1) - (d1 - b1)*(a2 - a1)) / det;
    if (t >= -1e-8 && t <=1+1e-8 && u >= -1e-8 && u <=1+1e-8)
        return 1;
    return 0;
}

int blocks(int pi, int qi, Segment s) {
    double dx, dy;
    if (qi == 0) { dx = -1; dy = 0; }
    else if (qi == 1) { dx = 0; dy = 1; }
    else if (qi == 2) { dx = 1; dy = 0; }
    else { dx = 0; dy = -1; }
    // p_i original
    double x1 = segments[pi].x1;
    double y1 = segments[pi].y1;
    double x2 = segments[pi].x2;
    double y2 = segments[pi].y2;
    // s_j segment
    double x3 = s.x1;
    double y3 = s.y1;
    double x4 = s.x2;
    double y4 = s.y2;
    // Solve for t, s_param, u
    double a = -dx;
    double b = segments[pi].x2 - segments[pi].x1;
    double c = -(segments[pi].x2 - segments[pi].x1);
    double d = -dy;
    double e = segments[pi].y2 - segments[pi].y1;
    double f = -(segments[pi].y2 - segments[pi].y1);
    // Using parametric intersection
    // Not implemented due to complexity, use intersect with shifted segments
    // Instead, iterate t from 0 to a large number and check
    // We can instead compute intersection with direction
    // Use binary search on t
    // But to simplify, iterate t from 0 to 2000 with step
    for(int i=0;i<=1000;i++){
        double t = i * 1000.0 / 1000.0;
        double px1 = x1 + t * dx;
        double py1 = y1 + t * dy;
        double px2 = x2 + t * dx;
        double py2 = y2 + t * dy;
        if(intersect(px1, py1, px2, py2, x3, y3, x4, y4)) return 1;
    }
    return 0;
}

int can_move(int pi, int qi){
    for(int j=1;j<=n;j++) if(!removed[j] && j != pi){
        if(blocks(pi, qi, segments[j])) return 0;
    }
    return 1;
}

int main(){
    scanf("%d", &n);
    for(int i=1;i<=n;i++) scanf("%lf %lf %lf %lf", &segments[i].x1, &segments[i].y1, &segments[i].x2, &segments[i].y2);
    for(int i=1;i<=n;i++) { scanf("%d %d", &move_p[i], &move_q[i]); }
    int illegal = -1;
    for(int i=1;i<=n;i++){
        int pi = move_p[i];
        int qi = move_q[i];
        if(!removed[pi]){
            if(can_move(pi, qi)){
                removed[pi] = 1;
            }
            else{
                illegal = i;
                break;
            }
        }
    }
    printf("%d\n", illegal);
    // Now find a valid move sequence
    for(int i=1;i<=n;i++) removed[i]=0;
    int valid_seq_p[1001], valid_seq_q[1001];
    int idx = 0;
    while(idx < n){
        for(int j=1;j<=n;j++) if(!removed[j]){
            for(int dir=0; dir<4; dir++){
                if(can_move(j, dir)){
                    removed[j]=1;
                    valid_seq_p[idx] = j;
                    valid_seq_q[idx] = dir;
                    idx++;
                    goto next;
                }
            }
        }
        next:;
    }
    for(int i=0;i<n;i++) printf("%d %d\n", valid_seq_p[i], valid_seq_q[i]);
}