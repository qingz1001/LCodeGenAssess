#include <stdio.h>
#include <string.h>

#define MAX_N 100
#define MAX_M 100

int city[MAX_N + 1][MAX_M + 1];
int n, m, x, y;

void bomb(int x1, int y1, int x2, int y2, int round) {
    for (int i = x1; i <= x2; i++) {
        for (int j = y1; j <= y2; j++) {
            city[i][j]++;
        }
    }
}

int main() {
    scanf("%d %d %d %d", &n, &m, &x, &y);
    
    memset(city, 0, sizeof(city));
    
    for (int i = 1; i <= x; i++) {
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        bomb(x1, y1, x2, y2, i);
    }
    
    for (int i = 0; i < y; i++) {
        int px, py;
        scanf("%d %d", &px, &py);
        
        if (city[px][py] > 0) {
            int last_round = 0;
            for (int j = 1; j <= x; j++) {
                int x1, y1, x2, y2;
                scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
                if (px >= x1 && px <= x2 && py >= y1 && py <= y2) {
                    last_round = j;
                }
            }
            printf("Y %d %d\n", city[px][py], last_round);
        } else {
            printf("N\n");
        }
        
        // 重置文件指针到轰炸数据开始处
        fseek(stdin, 0, SEEK_SET);
        for (int j = 0; j < 4; j++) {
            int temp;
            scanf("%d", &temp);
        }
        for (int j = 0; j < x; j++) {
            int temp;
            for (int k = 0; k < 4; k++) {
                scanf("%d", &temp);
            }
        }
    }
    
    return 0;
}