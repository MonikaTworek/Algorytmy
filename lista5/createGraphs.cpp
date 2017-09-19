#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <math.h>

using namespace std;

struct Node {
    int data;
    int size; //size.left+size.right+1
    struct Node* left;
    struct Node* parent;
    struct Node* right;
};


struct Node* osSelect(struct Node* node, int searchedPosition, int* compares){
    int r;
    (*compares)++;

    if(node->left==nullptr)
        r = 0;
    else
        r = (node->left)->size;

    (*compares)++;

    if(searchedPosition == r)
        return node;
    else if(searchedPosition < r)
        return osSelect(node->left,searchedPosition,compares);
    else
        return osSelect(node->right,searchedPosition-(r+1),compares);
}


void runOsSelect(struct Node* root, int sizeOfSequence, int numberOfStep){
    if(numberOfStep==10){
        FILE *f = fopen("C:\\Users\\Mona\\Desktop\\lista5\\osSelect.txt", "w");
        fprintf(f, "");
        fclose(f);
    }

    int compares=0;
    int numberOfTests=100;
    int minCompare=0;
    int avgCompare=0;
    int maxCompare=0;
    int iteration=0;
    int i;
    int abc;
    struct Node* result;

    int searchedPosition;

    for(i=1; i<=numberOfTests; i++){
        compares = 0;
        searchedPosition = rand()*sizeOfSequence/RAND_MAX;
        result = osSelect(root,searchedPosition,&compares);

        avgCompare+=compares;

        if (compares > maxCompare)
            maxCompare = compares;
        if (compares < minCompare)
            minCompare = compares;
    }

    cout << compares << endl;

    avgCompare/=numberOfTests;
    FILE *f = fopen("C:\\Users\\Mona\\Desktop\\lista5\\osSelect.txt", "a");

    if(numberOfStep==10)
        fprintf(f, "%d %li %li %li", sizeOfSequence, minCompare, avgCompare, maxCompare);
    else
        fprintf(f, "\n%d %li %li %li", sizeOfSequence ,minCompare, avgCompare, maxCompare);

    fclose(f);
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
        ancestor = NULL;
        current = (*root);

        while(1){
            ancestor=current;
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


void appendToBST(struct Node** root, int start, int stop){
    for(int i=start; i<=stop;i++)
        insertBST(root,i);
}


int main(){
    struct Node* root;
    srand(time(NULL));

    root = (Node *)malloc(sizeof(Node*));
    root = NULL;
    int sizeOfTree = 10;
    int action;
    int start = 1;
    int numberOfStep = 10;

    while(1){
        printf("\nOS-Select");
        printf("\nChoose one of the following options:");
        printf("\n1. Generate Data");
        printf("\n2. Generate Graphs");

        printf("\nAction: ");
        scanf("%d", &action);

        switch(action) {
            case 1:
                for(int i=0; i<50;i++){
                    appendToBST(&root,start,sizeOfTree);
                    start = sizeOfTree+1;
                    runOsSelect(root,sizeOfTree,numberOfStep);
                    sizeOfTree+=10;
                    numberOfStep+=10;
                }
                break;
            case 2:
                system("C:\\Users\\Mona\\Desktop\\lista5\\runSelect.bat");
                break;
        }
    }
}
