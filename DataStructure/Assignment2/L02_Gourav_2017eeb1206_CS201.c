#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    long long data;
    struct Node *left, *right;
    struct Node *parent; 
    long long hieght;
}Node;

typedef struct Queue {
    Node *node;
    long long level;
    struct Queue *next, *prev;
}Queue;

long long StringLen (char str[]) {
    long long i = 0;
    while (str[i] != '\0') {
        i++;
    }
    return i;
}

Node * NewNode (long long num) {
    Node *node = (Node *) malloc (sizeof (Node));
    node->data = num;
    node->left = node->right = node->parent = NULL;
    node->hieght = 0;

    return node;
}

long long Maximum (long long a, long long b) {
    if (a > b) {
        return a;
    }
    return b;
}

long long hieght (Node *a) {
    if (a == NULL) {
        return -1;
    }

    return a->hieght;
}

Node * DeleteTree (Node *root) {
    if (root == NULL) {
        return root;
    }

    root->left = DeleteTree (root->left);
    root->right = DeleteTree (root->right);
    free (root);
    return NULL;
}

Node * RightRotate (Node *x) {
    Node *y = x->left;
    x->left = y->right;
    y->right = x;

    y->hieght = Maximum (hieght (y->left), hieght (y->right)) + 1;
    x->hieght = Maximum (hieght (x->left), hieght (x->right)) + 1;

    return y; 
}

Node * LeftRotate (Node *x) {
    Node *y = x->right;
    x->right = y->left;
    y->left = x;

    y->hieght = Maximum (hieght (y->left), hieght (y->right)) + 1;
    x->hieght = Maximum (hieght (x->left), hieght (x->right)) + 1;

    return y;
}

Node * InsertionBST (Node *root, long long number) {
    if (root == NULL) {
        root = NewNode (number);

        return root;
    }

    if (number <= root->data) {
        root->left = InsertionBST (root->left, number);
        root->left->parent = root;

        root->hieght = Maximum (hieght (root->left), hieght (root->right)) + 1;
    }
    else if (number > root->data) {
        root->right = InsertionBST (root->right, number);
        root->right->parent = root;

        root->hieght = Maximum (hieght (root->left), hieght (root->right)) + 1;
    }

    return root;
}

Node * DeletionBST (Node *root, long long number) {
    if (root == NULL) {
        return root;
    } 
    else if (root->data > number) {
        root->left = DeletionBST (root->left, number);
        
        if (root->left != NULL) {
            root->left->hieght = Maximum (hieght (root->left->left), hieght (root->left->right)) + 1;
            root->left->parent = root;
        }
        
        root->hieght = Maximum (hieght (root->left), hieght (root->right)) + 1;
    }
    else if (root->data < number) {
        root->right = DeletionBST (root->right, number);
        
        if (root->right != NULL) {
            root->right->hieght = Maximum (hieght (root->right->right), hieght (root->right->left)) + 1;
            root->right->parent = root;
        }
        
        root->hieght = Maximum (hieght (root->left), hieght (root->right)) + 1;
    }
    else {
        if (root->left == NULL) {
            return root->right;
        }
        else if (root->right == NULL) {
            return root->left;
        }
        else {
            Node *temp = root->right;
            while (temp->left != NULL) {
                temp = temp->left;
            }

            root->data = temp->data;
            root->right = DeletionBST (root->right, root->data);

            if (root->right != NULL) {
                root->right->hieght = Maximum (hieght (root->right->right), hieght (root->right->left)) + 1;
                root->right->parent = root;
            }
            
            root->hieght = Maximum (hieght (root->left), hieght (root->right)) + 1;

            return root;
        }
    }
    return root;
}

Node * InsertionAVL (Node *root, long long number) {
    if (root == NULL) {
        root = NewNode (number);

        return root;
    }

    if (number <= root->data) {
        root->left = InsertionAVL (root->left, number);
        root->left->parent = root;

        root->hieght = Maximum (hieght (root->left), hieght (root->right)) + 1;
    }
    else if (number > root->data) {
        root->right = InsertionAVL (root->right, number);
        root->right->parent = root;

        root->hieght = Maximum (hieght (root->left), hieght (root->right)) + 1;
    }

    if (hieght (root->left) - hieght (root->right) > 1) {
        if (hieght(root->left->left) > hieght (root->left->right)) {
            root = RightRotate (root);
        }
        else {
            root->left = LeftRotate (root->left);
            root = RightRotate (root);
        }
    }
    else if (hieght (root->left) - hieght (root->right) < -1) {
        if (hieght (root->right->right) > hieght (root->right->left)) {
            root = LeftRotate (root);
        }
        else {
            root->right = RightRotate (root->right);
            root = LeftRotate (root);
        }
    }

    root->hieght = Maximum (hieght (root->left), hieght (root->right)) + 1;

    return root;
}

Node * DeletionAVL (Node *root, long long number) {
    if (root == NULL) {
        return root;
    } 
    else if (root->data > number) {
        root->left = DeletionAVL (root->left, number);
        
        if (root->left != NULL) {
            root->left->hieght = Maximum (hieght (root->left->left), hieght (root->left->right)) + 1;
            root->left->parent = root;
        }
        
        root->hieght = Maximum (hieght (root->left), hieght (root->right)) + 1;
    }
    else if (root->data < number) {
        root->right = DeletionAVL (root->right, number);
        
        if (root->right != NULL) {
            root->right->hieght = Maximum (hieght (root->right->right), hieght (root->right->left)) + 1;
            root->right->parent = root;
        }
        
        root->hieght = Maximum (hieght (root->left), hieght (root->right)) + 1;
    }
    else {
        if (root->left == NULL) {
            return root->right;
        }
        else if (root->right == NULL) {
            return root->left;
        }
        else {
            Node *temp = root->right;
            while (temp->left != NULL) {
                temp = temp->left;
            }

            root->data = temp->data;
            root->right = DeletionAVL (root->right, root->data);

            if (root->right != NULL) {
                root->right->hieght = Maximum (hieght (root->right->right), hieght (root->right->left)) + 1;
                root->right->parent = root;
            }
            
            root->hieght = Maximum (hieght (root->left), hieght (root->right)) + 1;

            return root;
        }
    }

    if (root == NULL) {
        return root;
    }

    root->hieght = Maximum (hieght (root->left), hieght (root->right)) + 1;

    if (hieght (root->left) - hieght (root->right) > 1) {
        if (hieght(root->left->left) > hieght (root->left->right)) {
            root = RightRotate (root);
        }
        else {
            root->left = LeftRotate (root->left);
            root = RightRotate (root);
        }
    }
    else if (hieght (root->left) - hieght (root->right) < -1) {
        if (hieght (root->right->right) > hieght (root->right->left)) {
            root = LeftRotate (root);
        }
        else {
            root->right = RightRotate (root->right);
            root = LeftRotate (root);
        }
    }

    root->hieght = Maximum (hieght (root->left), hieght (root->right)) + 1;

    return root;
}

Node * BuildTree (Node *root, char exp[], long long len, long long hieghtbalanced) {
    long long multiply = 1;
    for (long long i=0;i<len;i++) {
        if (exp[i] == 'T' || exp[i] == 'H' || exp[i] == ' ') {
            continue;
        }

        if (exp[i] > 47 && exp[i] < 58) {
            long long num = exp[i++] - 48;
            while (exp[i] > 47 && exp[i] < 58) {
                num = num * 10 + exp[i] - '0';
                i++;
            }
            i--;

            if (num != 0) {
                if (multiply == 1) {
                    if (hieghtbalanced == 0) {
                        root = InsertionBST (root, num);
                    }
                    else if (hieghtbalanced == 1) {
                        root = InsertionAVL (root, num);
                    }
                }
                else {
                    if (hieghtbalanced == 0) {
                        root = DeletionBST (root, num);
                    }
                    else {
                        root = DeletionAVL (root, num);
                    }
                }
            }

            multiply = 1;
        }
        else if (exp[i] == '-') {
            multiply = -1;
        }
    }
    return root;
}

Node * AddNodes (Node *root, char exp[], long long len, long long hieghtbalanced) {
    long long multiply = 1;
    for (long long i=0;i<len;i++) {
        if (exp[i] == 'A' || exp[i] == ' ') {
            continue;
        }

        if (exp[i] > 47 && exp[i] < 58) {
            long long num = exp[i++] - 48;
            while (exp[i] > 47 && exp[i] < 58) {
                num = num * 10 + exp[i] - '0';
                i++;
            }
            i--;

            if (num != 0) {
                if (multiply == 1) {
                    if (hieghtbalanced == 0) {
                        root = InsertionBST (root, num);
                    }
                    else if (hieghtbalanced == 1) {
                        root = InsertionAVL (root, num);
                    }
                }
            }
            multiply = 1;
        }
        else if (exp[i] == '-') {
            multiply = -1;
        }
    }
    return root;
}

Node * DeleteNodes (Node *root, char exp[], long long len, long long hieghtbalanced) {
    long long multiply = 1;
    for (long long i=0;i<len;i++) {
        if (exp[i] == 'U' || exp[i] == ' ') {
            continue;
        }

        if (exp[i] > 47 && exp[i] < 58) {
            long long num = exp[i++] - 48;
            while (exp[i] > 47 && exp[i] < 58) {
                num = num * 10 + exp[i] - '0';
                i++;
            }
            i--;

            if (num != 0) {
                if (multiply == 1) {
                    if (hieghtbalanced == 0) {
                        root = DeletionBST (root, num);
                    }
                    else if (hieghtbalanced == 1) {
                        root = DeletionAVL (root, num);
                    }
                }
            }

            multiply = 1;
        }
        else if (exp[i] == '-') {
            multiply = -1;
        }
    }
    return root;
}

long long NodeIsPresent (Node *root, long long num) {
    if (root == NULL) {
        return 0;
    }

    if (root->data == num) {
        return 1;
    }

    if (root->data > num) {
        return NodeIsPresent (root->left, num);
    }

    if (root->data < num) {
        return NodeIsPresent (root->right, num);
    }
    return 0;
}

long long SearchTree (Node *root, char exp[], long long len) {
    long long multiply = 1;
    for (long long i=0;i<len;i++) {
        if (exp[i] == 'F' || exp[i] == ' ') {
            continue;
        }

        if (exp[i] > 47 && exp[i] < 58) {
            long long num = exp[i++] - 48;
            while (exp[i] > 47 && exp[i] < 58) {
                num = num * 10 + exp[i] - '0';
                i++;
            }
            i--;

            if (multiply == 1) {
                if (NodeIsPresent (root, num)) {
                    return 1;
                }
                else {
                    return 0;
                }
            }

            multiply = 1;
        }
        else if (exp[i] == '-') {
            multiply = -1;
        }
    }
    return 0;
}

long long CountLeaves (Node *root) {
    if (root == NULL) {
        return 0;
    }

    if (root->left == NULL && root->right == NULL) {
        return 1;
    }

    return (CountLeaves (root->left) + CountLeaves (root->right));
}

long long CountNodes (Node *root) {
    if (root == NULL) {
        return 0;
    }

    return (CountNodes (root->left) + CountNodes (root->right) + 1);
}

void PreOrderTraversal (Node *root) {
    if (root == NULL) {
        return;
    }

    Node *nodestack[1000];
    long long nodelen = 0;
    nodestack[nodelen++] = root;

    while (nodelen > 0) {
        root = nodestack[--nodelen];
        printf ("%lld ", root->data);

        if (root->right != NULL) {
            nodestack[nodelen++] = root->right;
        }

        if (root->left != NULL) {
            nodestack[nodelen++] = root->left;
        }
    }
    return;
}

void InOrderTraversal (Node *root) {
    if (root == NULL) {
        return;
    }

    InOrderTraversal (root->left);
    printf ("%lld ", root->data);
    InOrderTraversal (root->right);
}

void PostOrderTraversal (Node *root) {
    if (root == NULL) {
        return;
    }

    PostOrderTraversal (root->left);
    PostOrderTraversal (root->right);
    printf ("%lld ", root->data);
}

void LevelOrderTraversal (Node *root) {
    if (root == NULL) {
        return;
    }

    Queue *start = NULL, *end = NULL;
    start = (Queue *)malloc (sizeof (Queue));

    start->node = root;
    start->level = 0;
    start->next = NULL;
    start->prev = NULL;
    end = start;

    while (start != NULL) {
        root = end->node;
        long long level = end->level;
        printf ("%lld ", root->data);

        if (end == start) {
            end = start = NULL;
        }
        else {
            end = end->next;
            end->prev = NULL;
        }

        if (root->left != NULL) {
            if (start != NULL) {
                start->next = (Queue *) malloc (sizeof (Queue));
                start->next->prev = start;
                start = start->next;
                start->node = root->left;
                start->level = level + 1;
                start->next = NULL; 
            }
            else if (start == NULL) {
                start = (Queue *)malloc (sizeof (Queue));

                start->node = root->left;
                start->level = level + 1;
                start->next = NULL;
                start->prev = NULL;
                end = start;
            }
        }
        if (root->right != NULL) {
            if (start != NULL) {
                start->next = (Queue *) malloc (sizeof (Queue));
                start->next->prev = start;
                start = start->next;
                start->node = root->right;
                start->level = level + 1;
                start->next = NULL; 
            }
            else if (start == NULL) {
                start = (Queue *)malloc (sizeof (Queue));

                start->node = root->right;
                start->level = level + 1;
                start->next = NULL;
                start->prev = NULL;
                end = start;
            }
        }
    }

    return;
}

void Depth (Node *root) {
    printf ("Depth = %lld\n", hieght (root) + 1);
    return;
}

void WidthOfTree (Node *root) {
    if (root == NULL) {
        printf ("0\n");
        return;
    }

    Queue *start = NULL, *end = NULL, *moving = NULL;
    start = (Queue *) malloc (sizeof (Queue));
    end = start;
    moving = start;

    start->level = 0;
    start->next = start->prev = NULL;
    start->node = root;

    while (moving != NULL) {
        root = moving->node;
        long long level = moving->level;

        if (root->left != NULL) {
            start->next = (Queue *)malloc (sizeof (Queue));
            start->next->prev = start;
            start = start->next;

            start->level = level + 1;
            start->node = root->left;
            start->next = NULL;  
        }
        
        if (root->right != NULL) {
            start->next = (Queue *)malloc (sizeof (Queue));
            start->next->prev = start;
            start = start->next;

            start->level = level + 1;
            start->node = root->right;
            start->next = NULL;
        }

        moving = moving->next;
    }

    long long currentwidth = 0, maxwidth = 0, currentlevel = 0;
    while (end != NULL) {
        if (currentlevel != end->level) {
            if (currentwidth > maxwidth) {
                maxwidth = currentwidth;
            }

            currentwidth = 0;
            currentlevel++;
        }

        currentwidth++;
        end = end->next;
    }

    if (currentwidth > maxwidth) {
        maxwidth = currentwidth;
    }

    printf ("%lld\n", maxwidth);
}

long long LCA2 (Node *root, long long num1, long long num2) {
    if (root == NULL) {
        return 0;
    }

    if ((NodeIsPresent (root->left, num1) && NodeIsPresent (root->right, num2)) || (NodeIsPresent (root->right, num1) && NodeIsPresent (root->left, num2))) {
        return root->data;
    }

    if (NodeIsPresent (root->left, num1) && NodeIsPresent (root->left, num2)) {
        return LCA2 (root->left, num1, num2);
    }
    
    if (NodeIsPresent (root->right, num1) && NodeIsPresent (root->right, num2)) {
        return LCA2 (root->right, num1, num2);
    }

    return 0;
}

void LCA(Node *root, long long num1, long long num2) {
    if (NodeIsPresent (root, num1) != 1 || NodeIsPresent (root, num2) != 1) {
        printf ("-1\n");
        return;
    } 
    if (num1 == num2) {
        printf ("%lld \n", num1);
        return;
    }

    long long ancestor = LCA2 (root, num1, num2);

    printf ("%lld\n", ancestor);
} 

void LowestCommonAncestor (Node *root, char exp[], long long len) {
    long long multiply = 1, num1 = -1, num2 = -1;
    for (long long i=0;i<len;i++) {
        if (exp[i] == 'F' || exp[i] == ' ') {
            continue;
        }

        if (exp[i] > 47 && exp[i] < 58) {
            long long num = exp[i++] - 48;
            while (exp[i] > 47 && exp[i] < 58) {
                num = num * 10 + exp[i] - '0';
                i++;
            }
            i--;

            if (multiply == 1) {
                if (num1 == -1) {
                    num1 = num;
                }
                else {
                    num2 = num;
                    i = len;
                }
            }

            multiply = 1;
        }
        else if (exp[i] == '-') {
            multiply = -1;
        }
    }

    LCA (root, num1, num2);
}

void FindPath (Node *root, long long num1, long long num2) {
    if (root == NULL || (NodeIsPresent (root, num1) == 0 && NodeIsPresent (root, num2) == 0)) {
        printf ("Neither Source Exist nor Destination\n");
        return;
    }

    Node *temp = root;

    while (temp != NULL && temp->data != num1) {
        if (temp == NULL) {
            printf ("Source Does Not Exist\n");
            return;
        }

        if (temp->data > num1) {
            temp = temp->left;
        }
        else if (temp->data < num1) {
            temp = temp->right;
        }

        if (temp == NULL) {
            printf ("Source Does Not Exist\n");
            return;
        }
    }

   Node *temp2 = root;
   while (temp2->data != num2) {
        if (temp2 == NULL) {
            printf ("Destination Does Not Exist\n");
            return;
        }

        if (temp2->data > num2) {
            temp2 = temp2->left;
        }
        else if (temp2->data < num2) {
            temp2 = temp2->right;
        }
        else {
            break;
        }

        if (temp2 == NULL) {
            printf ("Destination Does Not Exist\n");
            return;
        }
    }

    if (num1 == num2) {
        printf ("%lld Reached %lld\n", num1, num2);
        return;
    }

    Node *temp3 = temp;
    while (temp3 != temp2) {
        if (temp3 == NULL || temp2 == NULL) {
            printf ("Unreachable\n");
            return;
        }

        if (temp3->data > temp2->data) {
            temp3 = temp3->left;
        }
        else if (temp3->data < temp2->data) {
            temp3 = temp3->right;
        }

        if (temp3 == NULL || temp2 == NULL) {
            printf ("Unreachable\n");
            return;
        }
    }

    printf ("%lld ", temp->data);
    
    while (temp != temp2) {
        if (temp->data > temp2->data) {
            temp = temp->left;
            printf ("Left %lld ", temp->data);
        }
        else if (temp->data < temp2->data) {
            temp = temp->right;
            printf ("Right %lld ", temp->data);
        }
    }
    printf ("\n");

    return;
}

void Route (Node *root, char exp[], long long len) {
    long long multiply = 1, num1 = -1, num2 = -1;
    for (long long i=0;i<len;i++) {
        if (exp[i] == 'F' || exp[i] == ' ') {
            continue;
        }

        if (exp[i] > 47 && exp[i] < 58) {
            long long num = exp[i++] - 48;
            while (exp[i] > 47 && exp[i] < 58) {
                num = num * 10 + exp[i] - '0';
                i++;
            }
            i--;

            if (multiply == 1) {
                if (num1 == -1) {
                    num1 = num;
                }
                else {
                    num2 = num;
                    i = len;
                }
            }

            multiply = 1;
        }
        else if (exp[i] == '-') {
            multiply = -1;
        }
    }

    FindPath (root, num1, num2);
}

long long Diameter (Node *root) {
    if (root == NULL) {
        return 0;
    }

    long long lefthieght = hieght (root->left) + 1;
    long long righthieght = hieght (root->right) + 1;

    long long leftdiameter = Diameter (root->left);
    long long rightdiameter = Diameter (root->right);

    return Maximum (lefthieght + righthieght + 1, Maximum (rightdiameter, leftdiameter));
}

long long LeavesSum (Node *root) {
    if (root == NULL) {
        return 0;
    }
    if (root->left == NULL && root->right == NULL) {
        return root->data;
    }

    return LeavesSum (root->left) + LeavesSum (root->right);
}

void Perimeter (Node *root) {
    long long sum = LeavesSum (root);
    Node *temp = root;
    if (root->left != NULL) {
        while (root->left != NULL || root->right != NULL) {
            if (root->left != NULL) {
                root = root->left;
            }
            else if (root->right != NULL) {
                root = root->right;
            }
            if (root->left != NULL || root->right != NULL) {
                sum += root->data;
            }
        }
    }

    root = temp;

    if (root->right != NULL) {
        while (root->left != NULL || root->right != NULL) {
            if (root->right != NULL) {
                root = root->right;
            }
            else if (root->left != NULL) {
                root = root->left;
            }

            if (root->left != NULL || root->right != NULL) {
                sum += root->data;
            }
        }
    }

    sum = sum + temp->data;

    printf ("%lld\n", sum);
} 

int main() {
    long long t;
    scanf ("%lld", &t);
    
    Node *root = NULL;
    long long hieghtbalanced = 0;
    
    while (t--) {
        long long tmp;
        char expression[1000];
        
        scanf ("%lld", &tmp);
        scanf ("%[^\n]%*c", expression);

        long long len = StringLen (expression);

        if (expression[0] == 'T') {                                 
            root = DeleteTree (root);
            root = BuildTree (root, expression, len, 0);

            hieghtbalanced = 0;
        }
        else if (expression[0] == 'H') {                           
            root = DeleteTree (root);
            root = BuildTree (root, expression, len, 1);

            hieghtbalanced = 1;
        }
        else if (expression[0] == 'A') {                                
            root = AddNodes (root, expression, len, hieghtbalanced);
        }
        else if (expression[0] == 'U') {                                   
            root = DeleteNodes (root, expression, len, hieghtbalanced);
        }
        else if (expression[0] == 'F') {
            if (SearchTree (root, expression, len) == 1) {
                printf ("Yes\n");
            }
            else {
                printf ("No\n");
            }
        }
        else if (expression[0] == 'Q') {                               
            long long numberofleaves = CountLeaves (root);

            printf ("%lld\n", numberofleaves);
        }
        else if (expression[0] == 'N') {                               
            long long numberofnodes = CountNodes (root);

            printf ("%lld\n", numberofnodes);
        }
        else if (expression[0] == 'P') {                               
            PreOrderTraversal (root);
            printf ("\n");
        }
        else if (expression[0] == 'I') {                                
            InOrderTraversal (root);
            printf ("\n");
        }
        else if (expression[0] == 'S') {                                
            PostOrderTraversal (root);
            printf ("\n");
        }
        else if (expression[0] == 'L') {                                
            LevelOrderTraversal (root);
            printf ("\n");
        }
        else if (expression[0] == 'D') {                                
            Depth (root);
        }
        else if (expression[0] == 'W') {                                
            WidthOfTree (root);
        }
        else if (expression[0] == 'C') {                                 
            LowestCommonAncestor (root, expression, len);
        }
        else if (expression[0] == 'R') {                                 
            Route (root, expression, len);
        }
        else if (expression[0] == 'X') {                                   
            printf ("%lld\n", Diameter (root));
        }
        else if (expression[0] == 'Y') {
            Perimeter (root);
        }
        else {
            printf ("WRONG INPUT\n");
        }
    }
    return 0;
}

/*--------------------------------------------------------------------
Made By - Gourav Wadhwa

Entry Number - 2017eeb1206
----------------------------------------------------------------------*/
