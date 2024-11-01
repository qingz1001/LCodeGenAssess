#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int x, y, z;
} Cell;

int main(){
    int D;
    scanf("%d", &D);
    while(D--){
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        int total = a * b * c;
        Cell cells[5000];
        int cnt =0;
        int val;
        int x, y, z;
        for(x=0; x<a; x++){
            for(y=0; y<b; y++){
                for(z=0; z<c; z++){
                    scanf("%d", &val);
                    if(val){
                        cells[cnt].x = x;
                        cells[cnt].y = y;
                        cells[cnt].z = z;
                        cnt++;
                    }
                }
            }
        }
        if(cnt ==0){
            printf("0\n");
            continue;
        }
        int min_x = cells[0].x, max_x = cells[0].x;
        int min_y = cells[0].y, max_y = cells[0].y;
        int min_z = cells[0].z, max_z = cells[0].z;
        for(int i=1;i<cnt;i++){
            if(cells[i].x < min_x) min_x = cells[i].x;
            if(cells[i].x > max_x) max_x = cells[i].x;
            if(cells[i].y < min_y) min_y = cells[i].y;
            if(cells[i].y > max_y) max_y = cells[i].y;
            if(cells[i].z < min_z) min_z = cells[i].z;
            if(cells[i].z > max_z) max_z = cells[i].z;
        }
        int size_x = max_x - min_x +1;
        int size_y = max_y - min_y +1;
        int size_z = max_z - min_z +1;
        if(size_x * size_y * size_z == cnt){
            int m;
            if(size_x < size_y){
                m = size_x;
            }
            else{
                m = size_y;
            }
            if(m > size_z){
                m = size_z;
            }
            printf("%d\n", m);
        }
        else{
            printf("%d\n", cnt);
        }
    }
    return 0;
}