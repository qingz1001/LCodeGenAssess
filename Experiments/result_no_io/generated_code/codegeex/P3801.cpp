#include <stdio.h>

int n, m, q;
int rowCover[100005], colCover[100005];
int rowFog[100005], colFog[100005];
int rowSum[100005], colSum[100005];

int main() {
    scanf("%d%d%d", &n, &m, &q);
    
    while (q--) {
        int type;
        scanf("%d", &type);
        
        if (type == 1) {
            int x, y;
            scanf("%d%d", &x, &y);
            
            if (!rowCover[x]) {
                rowCover[x] = 1;
                rowFog[x] = 1;
            }
            if (!colCover[y]) {
                colCover[y] = 1;
                colFog[y] = 1;
            }
        } else if (type == 2) {
            int x1, y1, x2, y2;
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            
            int rowFogCount = 0, colFogCount = 0;
            for (int i = x1; i <= x2; i++) {
                if (rowCover[i]) rowFogCount++;
            }
            for (int i = y1; i <= y2; i++) {
                if (colCover[i]) colFogCount++;
            }
            
            int totalFog = rowFogCount + colFogCount;
            if (rowCover[x1] && colCover[y1]) totalFog--;
            
            printf("%d\n", totalFog);
        }
    }
    
    return 0;
}