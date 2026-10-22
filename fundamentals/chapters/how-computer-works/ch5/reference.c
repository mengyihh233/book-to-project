// 二分查找：数组必须先有序
#include <stdio.h>

int main(void) {
    int a[] = {1, 3, 5, 7, 9, 11, 13, 15};
    int n = 8, key = 9;
    int lo = 0, hi = n - 1, ans = -1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] == key) { ans = mid; break; }
        if (a[mid] < key) lo = mid + 1; else hi = mid - 1;
    }
    printf("%d 在数组索引 %d\n", key, ans);
    return 0;
}
