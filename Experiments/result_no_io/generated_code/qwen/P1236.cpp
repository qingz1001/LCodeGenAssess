#include <stdio.h>
#include <stdlib.h>

#define MAX_NUMS 4
#define TARGET 24

typedef struct {
    int value;
    int index;
} Node;

int is_valid(int a, int b) {
    return b != 0 && (a % b == 0 || b % a == 0);
}

int calculate(Node *nums, int n) {
    if (n == 1) {
        return nums[0].value == TARGET ? 1 : 0;
    }

    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            Node new_nums[MAX_NUMS];
            int k = 0;

            // Try addition
            new_nums[k++] = (Node){nums[i].value + nums[j].value, -1};
            for (int m = 0; m < n; ++m) {
                if (m != i && m != j) {
                    new_nums[k++] = nums[m];
                }
            }
            if (calculate(new_nums, k)) return 1;

            // Try subtraction
            new_nums[k++] = (Node){abs(nums[i].value - nums[j].value), -1};
            for (int m = 0; m < n; ++m) {
                if (m != i && m != j) {
                    new_nums[k++] = nums[m];
                }
            }
            if (calculate(new_nums, k)) return 1;

            // Try multiplication
            new_nums[k++] = (Node){nums[i].value * nums[j].value, -1};
            for (int m = 0; m < n; ++m) {
                if (m != i && m != j) {
                    new_nums[k++] = nums[m];
                }
            }
            if (calculate(new_nums, k)) return 1;

            // Try division
            if (is_valid(nums[i].value, nums[j].value)) {
                new_nums[k++] = (Node){nums[i].value / nums[j].value, -1};
                for (int m = 0; m < n; ++m) {
                    if (m != i && m != j) {
                        new_nums[k++] = nums[m];
                    }
                }
                if (calculate(new_nums, k)) return 1;
            }
            if (is_valid(nums[j].value, nums[i].value)) {
                new_nums[k++] = (Node){nums[j].value / nums[i].value, -1};
                for (int m = 0; m < n; ++m) {
                    if (m != i && m != j) {
                        new_nums[k++] = nums[m];
                    }
                }
                if (calculate(new_nums, k)) return 1;
            }
        }
    }
    return 0;
}

void print_solution(Node *nums, int n) {
    if (n == 1) {
        printf("%d = %d\n", nums[0].index, TARGET);
    } else {
        for (int i = 0; i < n - 1; ++i) {
            for (int j = i + 1; j < n; ++j) {
                Node new_nums[MAX_NUMS];
                int k = 0;

                // Try addition
                new_nums[k++] = (Node){nums[i].value + nums[j].value, -1};
                for (int m = 0; m < n; ++m) {
                    if (m != i && m != j) {
                        new_nums[k++] = nums[m];
                    }
                }
                if (calculate(new_nums, k)) {
                    printf("%d + %d = %d\n", nums[i].index, nums[j].index, nums[i].value + nums[j].value);
                    print_solution(new_nums, k);
                    return;
                }

                // Try subtraction
                new_nums[k++] = (Node){abs(nums[i].value - nums[j].value), -1};
                for (int m = 0; m < n; ++m) {
                    if (m != i && m != j) {
                        new_nums[k++] = nums[m];
                    }
                }
                if (calculate(new_nums, k)) {
                    printf("%d - %d = %d\n", nums[i].index, nums[j].index, abs(nums[i].value - nums[j].value));
                    print_solution(new_nums, k);
                    return;
                }

                // Try multiplication
                new_nums[k++] = (Node){nums[i].value * nums[j].value, -1};
                for (int m = 0; m < n; ++m) {
                    if (m != i && m != j) {
                        new_nums[k++] = nums[m];
                    }
                }
                if (calculate(new_nums, k)) {
                    printf("%d * %d = %d\n", nums[i].index, nums[j].index, nums[i].value * nums[j].value);
                    print_solution(new_nums, k);
                    return;
                }

                // Try division
                if (is_valid(nums[i].value, nums[j].value)) {
                    new_nums[k++] = (Node){nums[i].value / nums[j].value, -1};
                    for (int m = 0; m < n; ++m) {
                        if (m != i && m != j) {
                            new_nums[k++] = nums[m];
                        }
                    }
                    if (calculate(new_nums, k)) {
                        printf("%d / %d = %d\n", nums[i].index, nums[j].index, nums[i].value / nums[j].value);
                        print_solution(new_nums, k);
                        return;
                    }
                }
                if (is_valid(nums[j].value, nums[i].value)) {
                    new_nums[k++] = (Node){nums[j].value / nums[i].value, -1};
                    for (int m = 0; m < n; ++m) {
                        if (m != i && m != j) {
                            new_nums[k++] = nums[m];
                        }
                    }
                    if (calculate(new_nums, k)) {
                        printf("%d / %d = %d\n", nums[j].index, nums[i].index, nums[j].value / nums[i].value);
                        print_solution(new_nums, k);
                        return;
                    }
                }
            }
        }
    }
}

int main() {
    Node nums[MAX_NUMS];
    for (int i = 0; i < MAX_NUMS; ++i) {
        scanf("%d", &nums[i].value);
        nums[i].index = i + 1;
    }

    if (calculate(nums, MAX_NUMS)) {
        print_solution(nums, MAX_NUMS);
    } else {
        printf("No answer!\n");
    }

    return 0;
}