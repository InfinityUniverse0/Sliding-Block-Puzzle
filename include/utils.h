// 利用归并排序统计序列逆序数，用于数字华容道有解性判断

// Merge a[low..mid] and a[mid+1..high] to b[low..high]
int merge(int *arr, int low, int mid, int high);

// Sort arr[low..high] and count inversions
int mergeSortAndCountInversions(int *arr, int low, int high);
