#include <stdio.h>
#include <string.h>

int main(){
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    
    int items[101][101];
    int lit[101][101];
    memset(items, 0, sizeof(items));
    memset(lit, 0, sizeof(lit));
    
    int x, y;
    for(int i=0;i<m;i++){
        scanf("%d %d", &x, &y);
        if(x >=1 && x <=n && y >=1 && y <=n){
            items[x][y] = 1;
            // Torch lighting pattern
            // (x-2, y)
            if(x-2 >=1 && y >=1 && y <=n) lit[x-2][y] = 1;
            // (x-1, y-1), (x-1, y), (x-1, y+1)
            if(x-1 >=1){
                if(y-1 >=1) lit[x-1][y-1] =1;
                if(y >=1 && y <=n) lit[x-1][y] =1;
                if(y+1 <=n) lit[x-1][y+1] =1;
            }
            // (x, y-2), (x, y-1), (x, y), (x, y+1), (x, y+2)
            if(y-2 >=1) lit[x][y-2] =1;
            if(y-1 >=1) lit[x][y-1] =1;
            if(y >=1 && y <=n) lit[x][y] =1;
            if(y+1 <=n) lit[x][y+1] =1;
            if(y+2 <=n) lit[x][y+2] =1;
            // (x+1, y-1), (x+1, y), (x+1, y+1)
            if(x+1 <=n){
                if(y-1 >=1) lit[x+1][y-1] =1;
                if(y >=1 && y <=n) lit[x+1][y] =1;
                if(y+1 <=n) lit[x+1][y+1] =1;
            }
            // (x+2, y)
            if(x+2 <=n && y >=1 && y <=n){
                lit[x+2][y] =1;
            }
        }
    }
    
    for(int i=0;i<k;i++){
        scanf("%d %d", &x, &y);
        if(x >=1 && x <=n && y >=1 && y <=n){
            items[x][y] =1;
            for(int dx=-2; dx<=2; dx++){
                for(int dy=-2; dy<=2; dy++){
                    int nx = x + dx;
                    int ny = y + dy;
                    if(nx >=1 && nx <=n && ny >=1 && ny <=n){
                        lit[nx][ny] =1;
                    }
                }
            }
        }
    }
    
    int count=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(!items[i][j] && !lit[i][j]){
                count++;
            }
        }
    }
    
    printf("%d\n", count);
    return 0;
}