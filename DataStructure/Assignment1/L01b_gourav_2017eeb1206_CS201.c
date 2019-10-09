#include <stdio.h>

typedef struct Operator {
    char sign1, sign2;
}Operator;

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

int main() {
    long long t;
    scanf ("%lld", &t);
    while (t--) {
        char expression[200];
        long long length;
        for (long long i = 0;i < 200;i++) {
            scanf ("%c", &expression[i]);
            if (expression[i] == '#') {
                length = i;
                break;
            }
        }

        Operator operatorstack[25];
        long long variablestack[25], varlength = 0, oplength = 0;
        long long lastwasnumber = 0, multiply = 1;

        for (long long i=0;i<length;i++) {
            if (expression[i] == ' ' || expression[i] == '\n') {
                continue;
            }
            
            if (expression[i] > 47 && expression[i] < 58) {
                long long num = expression[i++] - 48;
                while (expression[i] > 47 && expression[i] < 58) {
                    num = num * 10 + expression[i] - '0';
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
                newoperator.sign1 = expression[i];
                if (expression[i+1] == ' ' || (expression[i+1] > 47 && expression[i+1] < 58) || expression[i+1] == '\n') {
                    newoperator.sign2 = '0';
                }
                else {
                    if (expression[i+1] != '-') {
                        newoperator.sign2 = expression[++i];
                    }
                    else {
                        newoperator.sign2 = '0';
                    }
                }
                if (precedence (newoperator) == 0) {
                    printf ("Error\n");
                    goto last;
                }
                if (lastwasnumber == 0 && newoperator.sign1 == '-' && newoperator.sign2 == '0') {
                    multiply = -1;
                    lastwasnumber = 1;
                    continue;
                }

                while (oplength != 0 && precedence(operatorstack[oplength - 1]) >= precedence(newoperator)) {
                    if (varlength < 2) {
                        printf ("Error\n");
                        goto last;
                    }
                    long long value1 = variablestack[--varlength];
                    long long value2 = variablestack[--varlength];

                    if (value1 == 0 && operatorstack[oplength-1].sign1 == '/') {
                        printf ("Error\n");
                        goto last;
                    }
                    if (value1 == 0 && operatorstack[oplength-1].sign1 == '%') {
                        printf ("Error\n");
                        goto last;
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
                printf ("Error\n");
                goto last;
            }
            long long value1 = variablestack[--varlength];
            long long value2 = variablestack[--varlength];

            if (value1 == 0 && operatorstack[oplength-1].sign1 == '/') {
                printf ("Error\n");
                goto last;
            }
            if (value1 == 0 && operatorstack[oplength-1].sign1 == '%') {
                printf ("Error\n");
                goto last;
            }
                
            variablestack[varlength++] = applyoperator(operatorstack[--oplength], value2, value1);
        }
        if (varlength > 1) {
            printf ("ERROR\n");
            goto last;
        }
        printf ("%lld\n", variablestack[0]);
        last:;
    }
    return 0;
}

// Name - Gourav Wadhwa
// Entry Number - 2017eeb1206
// Assumed that you can give negative numbers too so an expression such as 10+-20 will be evaluated as -10