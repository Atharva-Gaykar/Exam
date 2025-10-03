#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    int height;
} TreeNode;

TreeNode *root = NULL;

TreeNode *create_Node(int val) {
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(1);
    }
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height_cal(TreeNode *root) {
    if (root == NULL)
        return 0;
    int l = height_cal(root->left);
    int r = height_cal(root->right);
    return max(l, r) + 1;
}

TreeNode *rotate_right(TreeNode *p) {
    TreeNode *c = p->left;
    if (c == NULL)
        return p;
    TreeNode *t = c->right;
    c->right = p;
    p->left = t;
    printf("Right Rotation on node: %d\n", p->val);
    return c;
}

TreeNode *rotate_left(TreeNode *p) {
    TreeNode *c = p->right;
    if (c == NULL)
        return p;
    TreeNode *t = c->left;
    c->left = p;
    p->right = t;
    printf("Left Rotation on node: %d\n", p->val);
    return c;
}

TreeNode *rotate(TreeNode *root) {
    if (height_cal(root->left) - height_cal(root->right) > 1) {
        if (height_cal(root->left->left) - height_cal(root->left->right) > 0) {
            return rotate_right(root);
        } else {
            root->left = rotate_left(root->left);
            return rotate_right(root);
        }
    }

    if (height_cal(root->right) - height_cal(root->left) > 1) {
        if (height_cal(root->right->right) - height_cal(root->right->left) > 0) {
            return rotate_left(root);
        } else {
            root->right = rotate_right(root->right);
            return rotate_left(root);
        }
    }

    return root;
}

TreeNode *FindMin(TreeNode *node) {
    while (node->left != NULL)
        node = node->left;
    return node;
}

TreeNode *insert(TreeNode *root, int key) {
    if (root == NULL)
        return create_Node(key);
    if (key < root->val)
        root->left = insert(root->left, key);
    else
        root->right = insert(root->right, key);

    root->height = max(height_cal(root->left), height_cal(root->right)) + 1;
    return rotate(root);
}

TreeNode *Delete(TreeNode *node, int key) {
    if (!node)
        return NULL;

    if (key < node->val)
        node->left = Delete(node->left, key);
    else if (key > node->val)
        node->right = Delete(node->right, key);
    else {
        if (!node->left && !node->right) {
            free(node);
            return NULL;
        } else if (!node->left) {
            TreeNode *temp = node->right;
            free(node);
            return temp;
        } else if (!node->right) {
            TreeNode *temp = node->left;
            free(node);
            return temp;
        } else {
            TreeNode *temp = FindMin(node->right);
            node->val = temp->val;
            node->right = Delete(node->right, temp->val);
        }
    }

    node->height = max(height_cal(node->left), height_cal(node->right)) + 1;
    return rotate(node);
}

void inorder(TreeNode *root) {
    if (root == NULL)
        return;
    inorder(root->left);
    printf("%d ", root->val);
    inorder(root->right);
}

int main() {
    int values[] = {30, 20, 10, 25, 40, 50, 45};
    int n = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < n; i++) {
        root = insert(root, values[i]);
    }

    printf("Inorder traversal of AVL tree: ");
    inorder(root);
    printf("\n");

    printf("Enter value to delete: ");
    int del_val;
    scanf("%d", &del_val);
    root = Delete(root, del_val);

    printf("Inorder traversal after deletion: ");
    inorder(root);
    printf("\n");

    return 0;
}