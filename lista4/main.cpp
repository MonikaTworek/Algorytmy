#include <iostream>
#include <stdlib.h>
#include <malloc.h>
#include <fstream>
#include <vector>
#include <assert.h>

using namespace std;

struct Node{
    int data;
    struct Node* left;
    struct Node* right;
};

void insertBST(struct Node **root, int dataToInsert){
    struct Node *temporaryNode = (struct Node*)malloc(sizeof(struct Node));

    temporaryNode->data = dataToInsert;
    temporaryNode->left = NULL;
    temporaryNode->right = NULL;

    struct Node *current;
    struct Node *parent;

    if( (*root) == NULL){
        (*root) = temporaryNode;
    }
    else {
        parent=NULL;
        current=(*root);
        while(1){
            parent=current;
            if(dataToInsert >= parent->data){
                current = current->right;
                if(current == NULL){
                    parent->right=temporaryNode;
                    return;
                }
            } else {
                current = current->left;
                if(current == NULL){
                    parent->left=temporaryNode;
                    return;
                }
            }
        }
    }
}

int minimumBST(struct Node *root){
    struct Node* current = root;
    while(current->left != NULL){
        current = current->left;
    }
    return current->data;
}

int maximumBST(struct Node *root){
    struct Node* current = root;
    while(current->right != NULL){
        current = current->right;
    }
    return current->data;
}

int searchBST(struct Node *root, int searchedValue){
    struct Node *current = root;
    struct Node *next = NULL;
    while(current->data != searchedValue){
        if(searchedValue >= current->data){
            next = current->right;
            if( next == NULL){
                return 0;
            }
            else {
                current=current->right;
            }
        } else {
            next = current->left;
            if( next == NULL){
                return 0;
            }
            else {
                current=current->left;
            }
        }
    }
    return 1;
}

struct Node* deleteBST(struct Node **root, int valueToDelete){
    Node *pointer, *parent;
    Node *parentReplacement, *replacement;
    Node *child_ptr;

    int isLeft = 0; // 1 for left. 0 for right.
    parent = NULL;
    pointer = (*root);

    //znajdujemy node
    while(pointer != NULL){
        if (valueToDelete == pointer->data){
            break;
        } else if (valueToDelete < pointer->data){
            parent = pointer;
            isLeft = 1;
            pointer = pointer->left;
        } else {
            parent = pointer;
            isLeft = 0;
            pointer = pointer->right;
        }
    }

    if (pointer == NULL){
        return *root;
    }

    //jesli nie ma dzieci
    if ((pointer->left == NULL) && (pointer->right == NULL)){
        if (parent == NULL){
            assert(pointer == *root);
            free(pointer);
            (*root) = NULL;
        }
        else {
            free(pointer);
            if (isLeft){
                parent->left = NULL;
            } else{
                parent->right = NULL;
            }
        }
    }
    else
    if ((pointer->left != NULL) || (pointer->right != NULL)){
        if (pointer->left != NULL){
            child_ptr = pointer->left;
        }
        else {
            child_ptr = pointer->right;
        }
        if (parent == NULL){
            assert(pointer == *root);
            (*root) = child_ptr;
            free(pointer);
        }
        else {
            if (isLeft){
                parent->left = child_ptr;
            }
            else
                parent->right =  child_ptr;

            free(pointer);
        }
    }
    else {
        parentReplacement = pointer;
        replacement =  pointer->left;
        isLeft = 1;

        while(replacement->right != NULL){
            parentReplacement = replacement;
            replacement = replacement->right;
            isLeft = 0;
        }

        pointer->data = replacement->data;

        if (isLeft) {
            assert(replacement->right == NULL);
            pointer->left = replacement->left;
            free(replacement);
        } else {
            parentReplacement->right = replacement->left;
            free(replacement);
        }
    }
    return *root;
}


void printSearch(struct Node *root, int searchedValue){
    if(root == NULL){
        cout << endl;
    }
    else {
        int result = searchBST(root,searchedValue);
        cout << result << endl;
    }
}

void printMin(struct Node *root) {
    if(root==NULL){
        cout << endl;
    }
    else {
        int minimum = minimumBST(root);
        cout <<"minimum = " << minimum << endl;
    }
}

void printMax(struct Node *root){
    if(root==NULL){
        cout << endl;
    }
    else {
        int maximum = maximumBST(root);
        cout << "maximum = " << maximum << endl;
    }
}

void getData(vector<int> *operations,vector<int> *values){
    int n;
    string line;
    string token1;
    string token2;
    int noOfLine = 0;
    string delimiter = " ";
    ifstream bstData ("C:\\Users\\Mona\\Desktop\\lol\\lista_4\\input.txt");

    if (bstData.is_open()){
        while ( getline(bstData,line) ){
            if(noOfLine==0){
                n = atoi(line.c_str());
                noOfLine++;
            }
            else {
                if (line.find(delimiter) != string::npos){
                    size_t position = line.find(delimiter);
                    token1 = line.substr(0,position);
                    token2 = line.substr(position+1,line.length());

                    (*values).push_back(atoi(token2.c_str()));

                    if(token1.compare("insert")==0){
                        (*operations).push_back(4);
                    }
                    else if(token1.compare("delete")==0){
                        (*operations).push_back(5);
                    }
                    else if(token1.compare("find")==0){
                        (*operations).push_back(6);
                    }
                }
                else {
                    if(line.compare("min")==0){
                        (*operations).push_back(1);
                    }
                    else if(line.compare("max")==0){
                        (*operations).push_back(2);
                    }
                    else if(line.compare("inorder")==0){
                        (*operations).push_back(3);
                    }
                }
            }
        }
        bstData.close();
    }
    else {
        cout << "Unable to open file";
    }
}


void inorder(struct Node *root){
    if(root!=NULL){
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

void printInOrder(struct Node *root){
    if(root==NULL){
        cout << endl;
    } else {
        inorder(root);
        cout << endl;
    }
}

int main(){
    int j=0;
    vector<int> values;
    vector<int> operations;
    struct Node* root=NULL;
    getData(&operations,&values);

    for(int i=0;i<operations.size();i++) {

        if(operations.at(i) == 1){
            printMin(root);
        }
        else if(operations.at(i) == 2){
            printMax(root);
        }
        else if(operations.at(i) == 3){
            printInOrder(root);
        }
        else if(operations.at(i) == 4){
            insertBST(&root,values.at(j));
            j++;
        }
        else if(operations.at(i) == 5){
            deleteBST(&root,values.at(j));
            j++;
        }
        else if(operations.at(i) == 6){
            printSearch(root,values.at(j));
            j++;
        }
    }
    return 0;
}
