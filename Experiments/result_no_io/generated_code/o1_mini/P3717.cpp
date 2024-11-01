#include <stdio.h>

int main(){
    int n, m, r;
    scanf("%d %d %d", &n, &m, &r);
    int detectors[m][2];
    for(int i=0;i<m;i++) {
        scanf("%d %d", &detectors[i][0], &detectors[i][1]);
    }
    int count = 0;
    int r_sq = r * r;
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) {
            for(int k=0;k<m;k++) {
                int dx = i - detectors[k][0];
                int dy = j - detectors[k][1];
                if(dx*dx + dy*dy <= r_sq){
                    count++;
                    break;
                }
            }
        }
    }
    printf("%d\n", count);
    return 0;
}