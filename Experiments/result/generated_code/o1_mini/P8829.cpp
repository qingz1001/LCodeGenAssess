#include <stdio.h>
#include <string.h>

double unit_to_bytes(char *unit) {
    if(strcmp(unit, "GB") == 0) return (double)(1 << 30);
    if(strcmp(unit, "MB") == 0) return (double)(1 << 20);
    if(strcmp(unit, "KB") == 0) return (double)(1 << 10);
    if(strcmp(unit, "B") == 0) return 1.0;
    return 1.0;
}

int main(){
    double value;
    char src_unit[3], target_unit[3];
    scanf("%lf%2s=?%2s", &value, src_unit, target_unit);
    double bytes = value * unit_to_bytes(src_unit);
    double result = bytes / unit_to_bytes(target_unit);
    printf("%.6lf\n", result);
    return 0;
}