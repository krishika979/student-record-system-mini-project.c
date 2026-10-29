#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct studentnode {
    char Student_name[50];
    int enrollment_id;
    char Department[50];
    struct studentnode* left;
    struct studentnode* right;
} studentnode;


studentnode* createnode(int id, const char* name, const char* dept) {
    studentnode* newNode = (studentnode*)malloc(sizeof(studentnode));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    newNode->enrollment_id = id;
    strcpy(newNode->Student_name, name);
    strcpy(newNode->Department, dept);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

studentnode* searchnode(studentnode* root, int id) {
    if (root == NULL || root->enrollment_id == id)
        return root;
    if (id < root->enrollment_id)
        return searchnode(root->left, id);
    return searchnode(root->right, id);
}

studentnode* insert(studentnode* root, int id, char name[], char department[]) {
    if (root == NULL) 
        return createnode(id, name, department);
    
    if (id < root->enrollment_id)
        root->left = insert(root->left, id, name, department);
    else if (id > root->enrollment_id)
        root->right = insert(root->right, id, name, department);
    else
        printf("Duplicate is not allowed.\n");
        
    return root;
}

studentnode* minimum(studentnode* root) {
    while (root && root->left)
        root = root->left;
    return root;
}

studentnode* deleteNode(studentnode* root, int id) {
    studentnode* ptr1;
    if (root == NULL) 
        return NULL;
        
    if (id < root->enrollment_id)
        root->left = deleteNode(root->left, id);
    else if (id > root->enrollment_id)
        root->right = deleteNode(root->right, id);
    else {
        
        if (root->left == NULL) {
            ptr1 = root->right;
            free(root);
            return ptr1;
        }
        if (root->right == NULL) {
            ptr1 = root->left;
            free(root);
            return ptr1;
        }
    
        ptr1 = minimum(root->right);
        root->enrollment_id = ptr1->enrollment_id;
        strcpy(root->Student_name, ptr1->Student_name);
        strcpy(root->Department, ptr1->Department);
        root->right = deleteNode(root->right, ptr1->enrollment_id);
    }
    return root;
}

// Inorder Traversal
void inorder(studentnode* root) {
    if (!root) return;
    inorder(root->left);
    printf("ID: %d | Name: %s | Department: %s\n", root->enrollment_id, root->Student_name, root->Department);
    inorder(root->right);
}

// Preorder Traversal
void preorder(studentnode* root) {
    if (root) {
        printf("%d ", root->enrollment_id);
        preorder(root->left);
        preorder(root->right);
    }
}

// Postorder Traversal
void postorder(studentnode* root) {
    if (root) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->enrollment_id);
    }
}

void freeTree(studentnode* root) {
    if (root) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    studentnode* root = NULL;
    studentnode* found = NULL;
    int id, choice;
    char name[50], department[50];

    do {
        printf("\n==== Student Record BST ====\n");
        printf("1. Insert Student\n");
        printf("2. Search Student by ID\n");
        printf("3. Delete Student by ID\n");
        printf("4. Display Students (Inorder)\n");
        printf("5. Preorder Traversal\n");
        printf("6. Postorder Traversal\n");
        printf("7. Load Sample Records\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            break;
        }

        switch (choice) {
            case 1:
                printf("Enter enrolment ID: ");
                if (scanf("%d", &id) != 1) break;
                if (searchnode(root, id)) {
                    printf("Duplicate ID not allowed.\n");
                    continue;
                }
                printf("Enter student name (one word): ");
                scanf("%49s", name);
                printf("Enter department (one word): ");
                scanf("%49s", department);
                root = insert(root, id, name, department);
                printf("Record inserted.\n");
                break;
                
            case 2:
                printf("Enter ID to search: ");
                if (scanf("%d", &id) != 1) break;
                found = searchnode(root, id);
                if (!found)
                    printf("Student not found.\n");
                else
                    printf("ID: %d | Name: %s | Department: %s\n", found->enrollment_id, found->Student_name, found->Department);
                break;
                
            case 3:
                printf("Enter ID to delete: ");
                if (scanf("%d", &id) != 1) break;
                if (!searchnode(root, id))
                    printf("Student not found.\n");
                else {
                    root = deleteNode(root, id);
                    printf("Record deleted.\n");
                }
                break;
                
            case 4:
                if (!root) printf("Tree is empty.\n");
                else inorder(root);
                break;
                
            case 5:
                if (!root) printf("Tree is empty.\n");
                else {
                    printf("Preorder IDs: ");
                    preorder(root);
                    printf("\n");
                }
                break;
                
            case 6:
                if (!root) printf("Tree is empty.\n");
                else {
                    printf("Postorder IDs: ");
                    postorder(root);
                    printf("\n");
                }
                break;
                
            case 7: {
                int ids[] = {20, 23, 78, 64, 34, 90};
                char* names[] = {"krishika", "Sonam", "khushi", "Neetu", "shivani", "Divanshi"};
                char* deps[] = {"CSE", "ECE", "CSE", "IT", "ME", "AIML"};
                
                for (int i = 0; i < 6; i++) {
                    if (!searchnode(root, ids[i])) {
                        root = insert(root, ids[i], names[i], deps[i]);
                    }
                }
                printf("Sample records loaded; existing IDs were skipped.\n");
                break;
            }
            case 0:
                printf("Program ended.\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 0);

    freeTree(root);
    return 0;
}
