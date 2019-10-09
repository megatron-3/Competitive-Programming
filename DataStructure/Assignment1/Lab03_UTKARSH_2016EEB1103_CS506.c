#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int c = 0;

typedef struct Operator {
    char sign1, sign2;
}Operator;

void stack (char str[], int z) {
    int len = strlen (str), multiply = 1, stack[z], stacklen = 0;
    for (int i=0;i<len;i++) {
        if (str[i] == ' ' || str[i] == 'S') {
            continue;
        }
        else if (str[i] == '\0') {
            break;
        }
        else if (str[i] == '-') {
            multiply = -1;
            continue;
        }
        else if (str[i] - '0' >= 0 && str[i] - '0' <= 9) {
            long long num = str[i++] - 48;
            while (str[i] > 47 && str[i] < 58) {
                num = num * 10 + str[i] - '0';
                i++;
            }
            i--;
            num = num * multiply;
            multiply = 1;

            if (num > 0) {
                if (stacklen != z) {
                    stack[stacklen++] = num;
                }
            }
            else if (num == 0) {
                if (stacklen == 0) {
                    printf ("E ");
                }
                else {
                    printf ("NE ");
                }
            }
            else if (num == -1) {
                if (stacklen != 0) {
                    printf ("%d ", stack[--stacklen]);
                }
            }
            else if (num == -2) {
                if (stacklen == z) {
                    printf ("F ");
                }
                else {
                    printf ("NF ");
                }
            }
            else if (num == -3) {
                printf ("%d ", stacklen);
            }
            else {
                return;
            }
        }   
    }
}

typedef struct queue {
    int data;
    struct queue *next;
}Queue;

void queue(char str[], int z) {
    int len = strlen(str), queuelen = 0, multiply = 1;
    Queue *head = NULL, *rear = NULL;
    for (int i=0;i<len;i++) {
        if (str[i] == ' ' || str[i] == 'Q') {
            continue;
        }
        else if (str[i] == '\0') {
            break;
        }
        else if (str[i] == '-') {
            multiply = -1;
            continue;
        }
        else if (str[i] - '0' >= 0 && str[i] - '0' <= 9) {
            long long num = str[i++] - 48;
            while (str[i] > 47 && str[i] < 58) {
                num = num * 10 + str[i] - '0';
                i++;
            }
            i--;
            num = num * multiply;
            multiply = 1;

            if (num > 0) {
                if (head == NULL && queuelen < z) {
                    head = (Queue *)malloc (sizeof (Queue));
                    head->data = num;
                    head->next = NULL;
                    rear = head;
                    queuelen++;
                }
                else if (queuelen < z){
                    rear->next = (Queue *)malloc (sizeof (Queue));
                    rear = rear->next;
                    rear->data = num;
                    rear->next = NULL;
                    queuelen++;
                }
            }
            else if (num == 0) {
                if (head == NULL && rear == NULL) {
                    printf ("E ");
                }
                else {
                    printf ("NE ");
                }
            }
            else if (num == -1) {
                if (head != NULL) {
                    printf ("%d ", head->data);
                    if (head == rear) {
                        head = rear = NULL;
                    }
                    else {
                        head = head->next;
                    }
                    queuelen--;
                }
            }
            else if (num == -2) {
                if (queuelen == z) {
                    printf ("F ");
                }
                else {
                    printf ("NF ");
                }
            }
            else if (num == -3) {
                printf ("%d ", queuelen);
            }
            else {
                return;
            }
        }   
    }
}

long long precedence (Operator operator) {
    if ((operator.sign1 == '*' || operator.sign1 == '/' || operator.sign1 == '%') && operator.sign2 == '0') {
        return 8;
    }
    if ((operator.sign1 == '+' || operator.sign1 == '-') && operator.sign2 == '0') {
        return 7;
    }
    if ((operator.sign1 == '>' && operator.sign2 == '>') || (operator.sign1 == '<' && operator.sign2 == '<')) {
        return 6;
    }
    if (operator.sign1 == '>' || operator.sign1 == '<' || (operator.sign1 == '>' && operator.sign2 == '=') || (operator.sign1 == '<' && operator.sign2 == '=')) {
        return 5;
    }
    if ((operator.sign1 == '!' && operator.sign2 == '=') || (operator.sign1 == '=' && operator.sign2 == '=')) {
        return 4;
    }
    if (operator.sign1 == '&' && operator.sign2 == '0') {
        return 3;
    }
    if (operator.sign1 == '^' && operator.sign2 == '0') {
        return 8;
    }
    if (operator.sign1 == '|' && operator.sign2 == '0') {
        return 8;
    }
    return 0;
}

long long applyoperator (Operator op, long long a, long long b) {
    if (op.sign2 == '0') {
        switch (op.sign1) {
            case '*' : return a * b;
            case '/' : return a / b;
            case '%' : return a % b;
            case '+' : return a + b;
            case '-' : return a - b;
            case '>' : return a > b;
            case '<' : return a < b;
            case '&' : return a & b;
            case '^' : return a ^ b;
            case '|' : return a | b; 
        }
    }

    if (op.sign1 == '>' && op.sign2 == '>') {
        return a >> b;
    }
    if (op.sign1 == '<' && op.sign2 == '<') {
        return a << b;
    }
    if (op.sign1 == '<' && op.sign2 == '=') {
        return a <= b;
    }
    if (op.sign1 == '>' && op.sign2 == '=') {
        return a >= b;
    }
    if (op.sign1 == '=' && op.sign2 == '=') {
        return a == b;
    }
    if (op.sign1 == '!' && op.sign2 == '=') {
        return a != b;
    }
    return 0;
}

void concatenate (char ans[], int *anslen, int a, int b, char ch1, char ch2) {
    if (a != -1 && b != -1) {
        ans[(*anslen)++] = a + '0';
        ans[(*anslen)++] = ' ';

        ans[(*anslen)++] = b + '0';
        ans[(*anslen)++] = ' ';
    }
    else if (a == -1) {
        ans[(*anslen)++] = b + '0';
        ans[(*anslen)++] = ' ';
    }
    else {
        ans[(*anslen)++] = a + '0';
        ans[(*anslen)++] = ' ';
    }

    if (ch2 == '0') {
        ans[(*anslen)++] = ch1;
        ans[(*anslen)++] = ' ';
    }
    else {
        ans[(*anslen)++] = ch1;
        ans[(*anslen)++] = ' ';

        ans[(*anslen)++] = ch2;
        ans[(*anslen)++] = ' ';
    }
}

void postfixtoinfix (char str[]) {
    long long length;
    char ans[1000];
    int anslen = 0;
    for (long long i = 0;i < 200;i++) {
        if (str[i] == '#') {
            length = i;
            break;
        }
    }

    Operator operatorstack[25];
    long long variablestack[25], varlength = 0, oplength = 0;
    long long lastwasnumber = 0, multiply = 1;

    for (long long i=0;i<length;i++) {
        if (str[i] == ' ' || str[i] == '\n' || str[i] == 'I') {
            continue;
        }
        
        if (str[i] > 47 && str[i] < 58) {
            long long num = str[i++] - 48;
            while (str[i] > 47 && str[i] < 58) {
                num = num * 10 + str[i] - '0';
                i++;
            }
            i--;
            num = num * multiply;
            multiply = 1;
            variablestack[varlength] = num;
            varlength++;
            lastwasnumber = 1;
        }
        else {
            Operator newoperator;
            newoperator.sign1 = str[i];
            if (str[i+1] == ' ' || (str[i+1] > 47 && str[i+1] < 58) || str[i+1] == '\n') {
                newoperator.sign2 = '0';
            }
            else {
                if (str[i+1] != '-') {
                    newoperator.sign2 = str[++i];
                }
                else {
                    newoperator.sign2 = '0';
                }
            }
            if (precedence (newoperator) == 0) {
                printf ("ERROR");
                return;
            }
            if (lastwasnumber == 0 && newoperator.sign1 == '-' && newoperator.sign2 == '0') {
                multiply = -1;
                lastwasnumber = 1;
                continue;
            }

            while (oplength != 0 && precedence(operatorstack[oplength - 1]) >= precedence(newoperator)) {
                if (varlength < 2) {
                    printf ("ERROR");
                    return;
                }
                long long value1 = variablestack[--varlength];
                long long value2 = variablestack[--varlength];

                if (value1 == 0 && operatorstack[oplength-1].sign1 == '/') {
                    printf ("ERROR");
                    return;
                }
                if (value1 == 0 && operatorstack[oplength-1].sign1 == '%') {
                    printf ("ERROR");
                    return;
                }
                concatenate (ans, &anslen, value1, value2, operatorstack[oplength-1].sign1, operatorstack[oplength-1].sign2);
                variablestack[varlength++] = -1;
                oplength--;
            }
            operatorstack[oplength] = newoperator;
            oplength++;
            lastwasnumber = 0;
        }
    }
    while (oplength != 0) {
        if (varlength < 2) {
            printf ("ERROR");
            return;
        }
        long long value1 = variablestack[--varlength];
        long long value2 = variablestack[--varlength];

        if (value1 == 0 && operatorstack[oplength-1].sign1 == '/') {
            printf ("ERROR");
            return;
        }
        if (value1 == 0 && operatorstack[oplength-1].sign1 == '%') {
            printf ("ERROR");
            return;
        }
        
        concatenate (ans, &anslen, value1, value2, operatorstack[oplength-1].sign1, operatorstack[oplength-1].sign2);
        variablestack[varlength++] = -1;
        oplength--;
    }
    if (varlength > 1) {
        printf ("ERROR");
        return;
    }
    ans[anslen] = '\0';
    if (variablestack[0] != -1) {
        printf ("%s %lld", ans, variablestack[0]);
    }
    else {
        printf ("%s", ans);
    }
}

void evaluate (char str[]) {
    long long length;
    for (long long i = 0;i < 200;i++) {
        if (str[i] == '#') {
            length = i;
            break;
        }
    }

    Operator operatorstack[25];
    long long variablestack[25], varlength = 0, oplength = 0;
    long long lastwasnumber = 0, multiply = 1;

    for (long long i=0;i<length;i++) {
        if (str[i] == ' ' || str[i] == '\n' || str[i] == 'E') {
            continue;
        }
        
        if (str[i] > 47 && str[i] < 58) {
            long long num = str[i++] - 48;
            while (str[i] > 47 && str[i] < 58) {
                num = num * 10 + str[i] - '0';
                i++;
            }
            i--;
            num = num * multiply;
            multiply = 1;
            variablestack[varlength] = num;
            varlength++;
            lastwasnumber = 1;
        }
        else {
            Operator newoperator;
            newoperator.sign1 = str[i];
            if (str[i+1] == ' ' || (str[i+1] > 47 && str[i+1] < 58) || str[i+1] == '\n') {
                newoperator.sign2 = '0';
            }
            else {
                if (str[i+1] != '-') {
                    newoperator.sign2 = str[++i];
                }
                else {
                    newoperator.sign2 = '0';
                }
            }
            if (precedence (newoperator) == 0) {
                printf ("ERROR");
                return;
            }
            if (lastwasnumber == 0 && newoperator.sign1 == '-' && newoperator.sign2 == '0') {
                multiply = -1;
                lastwasnumber = 1;
                continue;
            }

            while (oplength != 0 && precedence(operatorstack[oplength - 1]) >= precedence(newoperator)) {
                if (varlength < 2) {
                    printf ("ERROR");
                    return;
                }
                long long value1 = variablestack[--varlength];
                long long value2 = variablestack[--varlength];

                if (value1 == 0 && operatorstack[oplength-1].sign1 == '/') {
                    printf ("ERROR");
                    return;
                }
                if (value1 == 0 && operatorstack[oplength-1].sign1 == '%') {
                    printf ("ERROR");
                    return;
                }
            
                variablestack[varlength++] = applyoperator(operatorstack[--oplength], value2, value1);
            }
            operatorstack[oplength] = newoperator;
            oplength++;
            lastwasnumber = 0;
        }
    }
    while (oplength != 0) {
        if (varlength < 2) {
            printf ("ERROR");
            return;
        }
        long long value1 = variablestack[--varlength];
        long long value2 = variablestack[--varlength];

        if (value1 == 0 && operatorstack[oplength-1].sign1 == '/') {
            printf ("ERROR");
            return;
        }
        if (value1 == 0 && operatorstack[oplength-1].sign1 == '%') {
            printf ("ERROR");
            return;
        }
            
        variablestack[varlength++] = applyoperator(operatorstack[--oplength], value2, value1);
    }
    if (varlength > 1) {
        printf ("ERROR");
        return;
    }
    printf ("%lld", variablestack[0]);
}

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
    int t, z, tmp;
    scanf ("%d%d", &t, &z);
    while (t--) {
        char str[1000];
        //scanf ("%d", &tmp);
        fflush (stdin);
        scanf ("%[^\n]%*c", str);
        if (str[0] == '\n') {
            t++;
            continue;
        }
        if (str[0] == 'S') {
            stack (str, z);
            printf ("\n");
        }
        else if (str[0] == 'Q') {
            queue (str, z);
            printf ("\n");
        }
        else if (str[0] == 'I') {
            postfixtoinfix (str);
            printf ("\n");
        }
        else if (str[0] == 'E') {
            evaluate (str);
            printf ("\n");
        }
        else if (str[0] == 'P') {
            int len = strlen (str), n = -1, k = -1;
            for (int i=0;i<len;i++) {
                if (str[i] == ' ' || str[i] == 'P') {
                    continue;
                }
                else {
                    long long num = str[i++] - 48;
                    while (str[i] > 47 && str[i] < 58) {
                        num = num * 10 + str[i] - '0';
                        i++;
                    }
                    i--;
                    if (n == -1) {
                        n = num;
                    }
                    else {
                        k = num;
                        i = len;
                    }
                }
            }

            long long int total = 1;
            int i = n+2;
            int a[n];
            
            for (int i=0;i<n;i++) {
                a[i] = 0;
                
                if (i == 0 || i == 1 || i == 2) {
                    a[i] = 1;
                }
            }
            
            for (;i<2*n;i++) {
                total = total * i;
                for (int j=1;j<n;j++) {
                    if (a[j] == 0 && total % j == 0) {
                        total = total / j;
                        a[j] = 1;
                    }
                }
            }

            if (n == 2) {
                total = 2;
            }

            printf ("%lld ", total);

            int *arr = (int *)malloc (2 * n * sizeof (int));
            c = 0;
            getpermutation (0, n, 0, 0, k, arr);
        }
        else {
            printf ("Wrong Input\n");
        }
    }
    return 0;
}