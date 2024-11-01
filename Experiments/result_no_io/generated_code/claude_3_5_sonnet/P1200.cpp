#include <stdio.h>
#include <string.h>

int calculate(char *name) {
    int result = 1;
    for (int i = 0; i < strlen(name); i++) {
        result *= (name[i] - 'A' + 1);
    }
    return result % 47;
}

int main() {
    char comet[7], group[7];
    scanf("%s", comet);
    scanf("%s", group);
    
    if (calculate(comet) == calculate(group)) {
        printf("GO\n");
    } else {
        printf("STAY\n");
    }
    
    return 0;
}