#include <stdio.h>
#include <string.h>

int calculateValue(const char *name) {
    int value = 1;
    for (int i = 0; name[i] != '\0'; ++i) {
        value *= (name[i] - 'A' + 1);
    }
    return value % 47;
}

int main() {
    char comet[7], group[7];
    
    scanf("%s", comet);
    scanf("%s", group);
    
    int cometValue = calculateValue(comet);
    int groupValue = calculateValue(group);
    
    if (cometValue == groupValue) {
        printf("GO\n");
    } else {
        printf("STAY\n");
    }
    
    return 0;
}