#include <stdio.h>
#include <stdbool.h>

bool can_form_24(int a, int b, int c, int d) {
    int nums[4] = {a, b, c, d};
    char ops[4] = {'+', '-', '*', '/'};

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                for (int l = 0; l < 4; l++) {
                    if (i != j && i != k && i != l && j != k && j != l && k != l) {
                        int res1, res2, res3;
                        // Try all possible operations
                        for (int op1 = 0; op1 < 4; op1++) {
                            for (int op2 = 0; op2 < 4; op2++) {
                                for (int op3 = 0; op3 < 4; op3++) {
                                    if (ops[op1] == '+') res1 = nums[i] + nums[j];
                                    else if (ops[op1] == '-') res1 = nums[i] - nums[j];
                                    else if (ops[op1] == '*') res1 = nums[i] * nums[j];
                                    else if (ops[op1] == '/' && nums[j] != 0 && nums[i] % nums[j] == 0) res1 = nums[i] / nums[j];
                                    else continue;

                                    if (ops[op2] == '+') res2 = res1 + nums[k];
                                    else if (ops[op2] == '-') res2 = res1 - nums[k];
                                    else if (ops[op2] == '*') res2 = res1 * nums[k];
                                    else if (ops[op2] == '/' && nums[k] != 0 && res1 % nums[k] == 0) res2 = res1 / nums[k];
                                    else continue;

                                    if (ops[op3] == '+') res3 = res2 + nums[l];
                                    else if (ops[op3] == '-') res3 = res2 - nums[l];
                                    else if (ops[op3] == '*') res3 = res2 * nums[l];
                                    else if (ops[op3] == '/' && nums[l] != 0 && res2 % nums[l] == 0) res3 = res2 / nums[l];
                                    else continue;

                                    if (res3 == 24) {
                                        printf("%d%c%d=%d\n", nums[i], ops[op1], nums[j], res1);
                                        printf("%d%c%d=%d\n", res1, ops[op2], nums[k], res2);
                                        printf("%d%c%d=24\n", res2, ops[op3], nums[l]);
                                        return true;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}

int main() {
    int a, b, c, d;
    scanf("%d %d %d %d", &a, &b, &c, &d);

    if (!can_form_24(a, b, c, d)) {
        printf("No answer!\n");
    }

    return 0;
}