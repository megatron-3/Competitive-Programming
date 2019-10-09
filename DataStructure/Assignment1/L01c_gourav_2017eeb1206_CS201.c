#include <stdio.h>
#include <stdlib.h>

int c = 0;

void printpermutation (int arr[], int n) {
    int arr2[n], index = 0, count = 1;
    for (int i=0;i<2*n;i++) {
        if (arr[i] == 1) {
            arr2[index++] = count++;
        }
        else {
            printf ("%d ", arr2[--index]);
        }
    }
    printf ("\n");
}

void getpermutation (int position, int n, int push, int pop, int k, int arr[])  {
    if (pop == n) {
        c++;
        if (k == c) {
            printpermutation (arr, n);
        }
    }
    else {
        if (push > pop) {
            arr[position] = 0;
            getpermutation (position + 1, n, push, pop + 1, k, arr);
        }
        if (push < n) {
            arr[position] = 1;
            getpermutation (position + 1, n, push + 1, pop, k, arr);
        }
    }
}

int main() {
    int t;
    scanf ("%d", &t);
    while (t--) {
        int n, k;
        scanf ("%d%d", &n, &k);

        long long int total = 1;
        int i = n+2;
        int a[n];
        for (int i=0;i<n;i++) {
            a[i] = 0;
        }
        a[0] = a[1] = a[2] = 1;
        for (;i<2*n;i++) {
            total = total * i;
            for (int j=1;j<n;j++) {
                if (a[j] == 0 && total % j == 0) {
                    total = total / j;
                    a[j] = 1;
                }
            }
        }

        printf ("%lld ", total);
        
        int *arr = (int *)malloc (2 * n * sizeof (int));

        c = 0;
        getpermutation (0, n, 0, 0, k, arr);
    }
    return 0;
}

// Name - Gourav Wadhwa
// Entry Number - 2017eeb1206