#include <stdio.h>
#include <stdlib.h>

typedef long long LL;

int main() {
    LL n;
    scanf("%lld", &n);
    LL *heights = (LL *)malloc(n * sizeof(LL));
    LL *leftMax = (LL *)malloc(n * sizeof(LL));
    LL *rightMax = (LL *)malloc(n * sizeof(LL));
    LL *count = (LL *)malloc(n * sizeof(LL));
    LL result = 0;

    for (LL i = 0; i < n; i++) {
        scanf("%lld", &heights[i]);
        leftMax[i] = heights[i];
        rightMax[i] = heights[i];
        count[i] = 1;
    }

    // Calculate leftMax array
    for (LL i = 1; i < n; i++) {
        if (heights[i] > leftMax[i - 1]) {
            leftMax[i] = heights[i];
        } else {
            leftMax[i] = leftMax[i - 1];
        }
    }

    // Calculate rightMax array
    for (LL i = n - 2; i >= 0; i--) {
        if (heights[i] > rightMax[i + 1]) {
            rightMax[i] = heights[i];
        } else {
            rightMax[i] = rightMax[i + 1];
        }
    }

    // Calculate the number of pairs that can see each other
    for (LL i = 0; i < n; i++) {
        if (leftMax[i] == heights[i] && rightMax[i] == heights[i]) {
            result += count[i] * (i + 1) * (n - i - 1);
        } else if (leftMax[i] == heights[i]) {
            LL j = i + 1;
            while (j < n && heights[j] < heights[i]) {
                j++;
            }
            result += count[i] * (i + 1) * (n - j);
        } else if (rightMax[i] == heights[i]) {
            LL j = i - 1;
            while (j >= 0 && heights[j] < heights[i]) {
                j--;
            }
            result += count[i] * (j + 1) * (n - i - 1);
        } else {
            LL j = i - 1;
            while (j >= 0 && heights[j] < heights[i]) {
                j--;
            }
            LL k = i + 1;
            while (k < n && heights[k] < heights[i]) {
                k++;
            }
            result += count[i] * (j + 1) * (n - k);
        }
    }

    printf("%lld\n", result);

    free(heights);
    free(leftMax);
    free(rightMax);
    free(count);

    return 0;
}