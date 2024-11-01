#include <stdio.h>
#include <math.h>

int main(){
    int n, m, r;
    scanf("%d %d %d", &n, &m, &r);
    int detectors[m][2];
    for(int i=0;i<m;i++) scanf("%d %d", &detectors[i][0], &detectors[i][1]);
    int count=0;
    for(int x=1;x<=n;x++) {
        for(int y=1;y<=n;y++) {
            for(int i=0;i<m;i++) {
                int dx = x - detectors[i][0];
                int dy = y - detectors[i][1];
                if(dx*dx + dy*dy <= r*r){
                    count++;
                    break;
                }
            }
        }
    }
    printf("%d", count);
}