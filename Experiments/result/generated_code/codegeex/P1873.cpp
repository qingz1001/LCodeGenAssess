#include <stdio.h>

// 定义一个函数来计算在给定高度h下能砍伐的木材总长度
int calculateWood(int treeHeights[], int n, int h) {
    int totalWood = 0;
    for (int i = 0; i < n; i++) {
        if (treeHeights[i] > h) {
            totalWood += treeHeights[i] - h;
        }
    }
    return totalWood;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    int treeHeights[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &treeHeights[i]);
    }
    
    // 初始化二分查找的左右边界
    int left = 0, right = 0;
    for (int i = 0; i < n; i++) {
        if (treeHeights[i] > right) {
            right = treeHeights[i];
        }
    }
    
    // 二分查找锯片的最高高度
    while (left < right) {
        int mid = (left + right + 1) / 2;
        int wood = calculateWood(treeHeights, n, mid);
        
        if (wood >= m) {
            left = mid; // 如果砍伐的木材长度大于等于所需长度，尝试更高的高度
        } else {
            right = mid - 1; // 否则尝试更低的高度
        }
    }
    
    printf("%d\n", left);
    return 0;
}