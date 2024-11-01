#include <stdio.h>
#include <string.h>

int main() {
    char str[100];
    scanf("%s", str);
    
    double num;
    char unit1[4], unit2[4];
    
    sscanf(str, "%lf %s = ? %s", &num, unit1, unit2);
    
    double result;
    if (strcmp(unit1, "GB") == 0) {
        if (strcmp(unit2, "MB") == 0) {
            result = num * 1024;
        } else if (strcmp(unit2, "KB") == 0) {
            result = num * 1048576;
        } else if (strcmp(unit2, "B") == 0) {
            result = num * 1073741824;
        }
    } else if (strcmp(unit1, "MB") == 0) {
        if (strcmp(unit2, "GB") == 0) {
            result = num / 1024;
        } else if (strcmp(unit2, "KB") == 0) {
            result = num * 1024;
        } else if (strcmp(unit2, "B") == 0) {
            result = num * 1048576;
        }
    } else if (strcmp(unit1, "KB") == 0) {
        if (strcmp(unit2, "GB") == 0) {
            result = num / 1048576;
        } else if (strcmp(unit2, "MB") == 0) {
            result = num / 1024;
        } else if (strcmp(unit2, "B") == 0) {
            result = num * 1024;
        }
    } else if (strcmp(unit1, "B") == 0) {
        if (strcmp(unit2, "GB") == 0) {
            result = num / 1073741824;
        } else if (strcmp(unit2, "MB") == 0) {
            result = num / 1048576;
        } else if (strcmp(unit2, "KB") == 0) {
            result = num / 1024;
        }
    }
    
    printf("%.6lf\n", result);
    return 0;
}