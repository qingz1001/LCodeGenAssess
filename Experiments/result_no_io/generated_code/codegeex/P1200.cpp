#include <stdio.h>
#include <string.h>

int main() {
    char comet[7], group[7];
    int cometProduct = 1, groupProduct = 1;

    // 读取彗星名和队伍名
    scanf("%s %s", comet, group);

    // 计算彗星名字的乘积
    for (int i = 0; comet[i] != '\0'; i++) {
        cometProduct *= comet[i] - 'A' + 1;
    }

    // 计算队伍名字的乘积
    for (int i = 0; group[i] != '\0'; i++) {
        groupProduct *= group[i] - 'A' + 1;
    }

    // 比较模47的结果
    if (cometProduct % 47 == groupProduct % 47) {
        printf("GO\n");
    } else {
        printf("STAY\n");
    }

    return 0;
}