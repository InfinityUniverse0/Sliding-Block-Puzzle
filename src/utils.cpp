// 利用归并排序统计序列逆序数，用于数字华容道有解性判断
/*
 * 当且仅当逆序数为偶数时，数字华容道（本项目场景下）有解
 * 逆序数为奇数时，数字华容道无解
 */

#include "utils.h"

int merge(int *arr, int low, int mid, int high) {
    // Merge a[low..mid] and a[mid+1..high] to b[low..high]
    int i = low, j = mid + 1, k = 0;
    int inversions = 0;
    int *temp = new int[high - low + 1];

    while (i <= mid && j <= high) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            inversions += mid - i + 1;
        }
    }

    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    while (j <= high) {
        temp[k++] = arr[j++];
    }

    for (i = low, k = 0; i <= high; i++, k++) {
        arr[i] = temp[k];
    }

    delete[] temp;
    return inversions;
}

int mergeSortAndCountInversions(int *arr, int low, int high) {
    // Sort arr[low..high] and count inversions
    if (low >= high) {
        return 0;
    }

    int mid = (low + high) / 2;
    int inversions = 0;

    inversions += mergeSortAndCountInversions(arr, low, mid);
    inversions += mergeSortAndCountInversions(arr, mid + 1, high);
    inversions += merge(arr, low, mid, high);

    return inversions;
}
