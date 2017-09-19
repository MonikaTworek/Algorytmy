#include <iostream>
#include <assert.h>

using namespace std;

struct Node {
    int data;
    int size; //size.left+size.right+1
    struct Node* left;
    struct Node* parent;
    struct Node* right;
};


int osRank(struct Node* root, struct Node* searchedNode){
    int r;

    if(searchedNode->left==nullptr)
        r = 1;
    else
        r = (searchedNode->left)->size+1;

    struct Node *y = searchedNode;

    while(y != root){
        if(y == y->parent->right){
            if (y->parent->left == nullptr)
                r++;
            else
                r = r + y->parent->left->size+1;
        }
        y = y->parent;
    }
    return r;
}


void runOsRank(struct Node* root, struct Node* searchedNode){
    int result = osRank(root,searchedNode);
    cout << endl << "Position of searched node is " << result;
}


struct Node* osSelect(struct Node* node, int searchedPosition){
    int r;

    if(node->left==nullptr)
        r = 0;
    else
        r = (node->left)->size;

    if(searchedPosition == r)
        return node;
    else if(searchedPosition < r)
        return osSelect(node->left,searchedPosition);
    else
        return osSelect(node->right,searchedPosition-(r+1));
}


void runOsSelect(struct Node* root, int searchedPosition){
    struct Node* result;
    result = osSelect(root,searchedPosition);

    cout << "Position = " << searchedPosition << " data = " << result->data;
}


void insertBST(struct Node **root, int dataToInsert){
    struct Node *temporaryNode = (struct Node*)malloc(sizeof(struct Node));
    temporaryNode->data = dataToInsert;
    temporaryNode->left = NULL;
    temporaryNode->right = NULL;
    temporaryNode->parent = NULL;
    temporaryNode->size = 1;

    struct Node *current;
    struct Node *ancestor;

    if((*root) == NULL)
        (*root) = temporaryNode;
    else {
        current = (*root);

        while(1){
            ancestor = current;
            ancestor->size++;

            if(dataToInsert >= ancestor->data){
                current = current->right;
                if(current == NULL){
                    ancestor->right=temporaryNode;
                    temporaryNode->parent=ancestor;
                    return;
                }
            } else {
                current = current->left;
                if(current == NULL){
                    ancestor->left=temporaryNode;
                    temporaryNode->parent=ancestor;
                    return;
                }
            }
        }
    }
}

struct Node* deleteBST(struct Node **root, int valueToDelete){
    Node *current, *parent;
    Node *parentReplacement, *replacement;
    Node *child_ptr;

    int isLeft = 0; // 1 for left. 0 for right.

    parent = NULL;
    current = (*root);

    //znajdz szukany node
    while(current != NULL){
        if (valueToDelete == current->data){
            break;
        } else if (valueToDelete < current->data){
            (current->size)--;
            parent = current;
            isLeft = 1;
            current = current->left;
        } else {
            (current->size)--;
            parent = current;
            isLeft = 0;
            current = current->right;
        }
    }

    if (current == NULL){
        return *root;
    }
    //jesli nie ma dzieci
    if ((current->left == NULL) && (current->right == NULL)){
        //is root
        if (parent == NULL){
            assert(current == *root);
            free(current);
            (*root) = NULL;
        } else {
            free(current);
            if (isLeft){
                parent->left = NULL;
            } else{
                parent->right = NULL;
            }
        }
    } else if ((current->left == NULL) || (current->right == NULL)){
        if (current->left != NULL){
            child_ptr = current->left;
        } else {
            child_ptr = current->right;
        }
        if (parent == NULL){
            assert(current == *root);
            (*root) = child_ptr;
            free(current);
        } else {
            if (isLeft)
                parent->left = child_ptr;
            else
                parent->right =  child_ptr;

            free(current);
        }
    } else {
        parentReplacement = current;
        replacement =  current->left;
        isLeft = 1;

        while(replacement->right != NULL){
            parentReplacement = replacement;
            replacement = replacement->right;
            isLeft = 0;
        }

        current->data = replacement->data;

        if (isLeft) {
            assert(replacement->right == NULL);
            current->left = replacement->left;
            free(replacement);
        } else {
            parentReplacement->right = replacement->left;
            free(replacement);
        }
    }
    return *root;
}


void prepareTree(struct Node** root){
    insertBST(root,5);
    insertBST(root,6);
    insertBST(root,2);
    insertBST(root,3);
    insertBST(root,1);
    insertBST(root,4);
}

int maximumBST(struct Node *root){
    struct Node* current = root;
    while(current->right != NULL)
        current = current->right;
    return current->data;
}

void printMax(struct Node *root){
    if(root==NULL)
        cout << "empty" << endl;
    else {
        int maximum = maximumBST(root);
        cout << maximum << endl;
    }
}


int main(){
    struct Node* root=NULL;
    prepareTree(&root);

    runOsSelect(root,5);

    runOsRank(root,root->left);

    return 0;
}
