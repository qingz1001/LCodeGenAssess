#include <stdio.h>
#include <string.h>

#define MAXH 6
#define MAXN 6
#define MAXM (1<<12)

char a[MAXH][MAXN+1], b[MAXH][MAXN+1];
long long f[MAXM][MAXM];
int h, m;

int check(int x, int y, int z, int w) {
    for (int i = 0; i < h; i++) {
        if ((x & (1<<i)) && a[i][0] == '.')  return 0;
        if ((y & (1<<i)) && a[i][5] == '.')  return 0;
        if ((z & (1<<i)) && b[i][0] == '.')  return 0;
        if ((w & (1<<i)) && b[i][5] == '.')  return 0;
    }
    return 1;
}

int main() {
    scanf("%d", &h);
    for (int i = 0; i < h; i++)
        scanf("%s", a[i]);
    for (int i = 0; i < h; i++)
        scanf("%s", b[i]);
    
    m = 1 << h;
    f[0][0] = 1;
    
    for (int i = 0; i < m; i++)
        for (int j = 0; j < m; j++)
            if (f[i][j])
                for (int x = 0; x < m; x++)
                    for (int y = 0; y < m; y++)
                        if (check(i, x, j, y))
                            f[x][y] += f[i][j];
    
    printf("%lld\n", f[0][0]);
    return 0;
}