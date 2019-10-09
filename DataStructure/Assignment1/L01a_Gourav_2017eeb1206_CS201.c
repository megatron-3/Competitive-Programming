#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

typedef struct Node {
    long long number;
    struct Node *next;
}Node;

Node * calculatemultiplication (Node *root, long long n) {
    Node *pointer = root;
    long long carry = 0;
    while (1) {
        long long sum = n * pointer->number + carry;
        pointer->number = sum % 10;
        carry = sum / 10;
        if (pointer->next == NULL) {
            break;
        }
        pointer = pointer->next;
    }
    while (carry != 0) {
        pointer->next = (Node *)malloc (sizeof (Node));
        pointer = pointer->next;
        pointer->next = NULL;
        pointer->number = carry % 10;
        carry = carry / 10; 
    }
    return root;
}

Node * multiply (Node *root, long long n) {
    long long temp = 1;
    for (long long i=1;i<=n;i++) {
        for (long long j=0;j<i;j++) {
            root = calculatemultiplication (root, i);
        }
    }
    return root;
} 


long long pattern (Node *root, char *k) {
    int length = strlen (k), count = 0;
    while (root != NULL) {
        if (length == 3) {
            if ((root->number == k[length-1] - '0') && (root->next != NULL && root->next->number == k[length-2] - '0') && (root->next->next != NULL && root->next->next->number == k[length-3] - '0')) {
                count++;
            }
        }
        else if (length == 2) {
            if ((root->number == k[length-1] - '0') && (root->next != NULL && root->next->number == k[length-2] - '0')) {
                count++;
            }
        }
        else {
            if (root->number == k[length-1] - '0') {
                count++;
            }
        }
        root = root->next;
    }
    return count;
}


long long numberofzeros (long long n) {
    long long count5 = 0, count2 = 0, i = 2;
    while (i <= n) {
        int b = i;
        int no2 = 0, no5 = 0;
        while (b % 2 == 0) {
            no2 = no2 + 1;
            b = b / 2;
        }
        while (b % 5 == 0) {
            no5 = no5 + 1;
            b = b / 5;
        }

        count2 = count2 + no2 * i;
        count5 = count5 + no5 * i;
        i++;
    }
    if (count2 < count5) {
        return count2;
    }
    return count5;
}

void print (Node *root) {
    if (root->next != NULL) {
        print (root->next);
    }
    printf ("%lld", root->number);
}

int main() {
    long long t;
    scanf ("%lld", &t);
    while (t--) {
        long long n;
        char *k;
        k = (char *)malloc (sizeof(char) * 10);
        scanf ("%lld%s", &n, k);
        Node *root;
        root = (Node *)malloc (sizeof (Node));
        root->number = 1;
        root->next = NULL;

        root = multiply (root, n);

        long long patterns = pattern (root, k);
        long long zeros = numberofzeros (n);
        printf ("%lld %lld ", zeros, patterns);
        print (root);
        printf ("\n");
    }
    return 0;
}

// Made By - Megatron-3
