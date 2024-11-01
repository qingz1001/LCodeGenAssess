#include <stdio.h>
#include <string.h>

int calculate_product(char *name) {
    int product = 1;
    for (int i = 0; i < strlen(name); i++) {
        product *= (name[i] - 'A' + 1);
    }
    return product;
}

int main() {
    char comet[7], group[7];
    
    scanf("%s", comet);
    scanf("%s", group);
    
    int comet_value = calculate_product(comet);
    int group_value = calculate_product(group);
    
    if (comet_value % 47 == group_value % 47) {
        printf("GO\n");
    } else {
        printf("STAY\n");
    }
    
    return 0;
}