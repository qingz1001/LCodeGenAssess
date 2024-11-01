#include <stdio.h>

int main() {
    FILE *fp = fopen("game0.out", "w");
    
    // 最小值
    fprintf(fp, "2\n");
    
    // 最大值
    fprintf(fp, "3\n");
    
    fclose(fp);
    return 0;
}