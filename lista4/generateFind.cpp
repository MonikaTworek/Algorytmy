#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#include <time.h>
#include <process.h>
#include <malloc.h>
#include <iostream>
#include <vector>

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
            }
            else {
                current = current->left;
                if(current == NULL){
                    parent->left=temporaryNode;
                    return;
                }
            }
        }
    }
}

int searchBST(struct Node **root, int searchedValue){
    struct Node *current = (*root);
    struct Node *next = NULL;
    int compares=1;
    while(current->data != searchedValue){
        compares++;
        if(searchedValue >= current->data){
            compares++;
            next = current->right;
            if( next == NULL){
                return 0;
            }
            else {
                current=current->right;
            }
        }
        else {
            compares++;
            next = current->left;
            if( next == NULL){
                return 0;
            } else {
                current=current->left;
            }
        }
    }
    return compares;
}

int maximumBST(struct Node *root){
    struct Node* current = root;
    while(current->right != NULL){
        current = current->right;
    }
    return current->data;
}

void printMax(struct Node *root){
    int maximum = maximumBST(root);
    cout << "maximum = " << maximum << endl;
}

void runSearch(struct Node **root, struct Node **avgRoot, int numberOfStep, vector<int>* valuesInsideBST){
    if(numberOfStep==1){
        FILE *f = fopen("C:\\Users\\Mona\\Desktop\\lol\\lista_4\\find.txt", "w");
        fprintf(f, "");
        fclose(f);
    }

    int numberOfTests=10;
    int minCompare=0;
    int avgCompare=0;
    int maxCompare=0;
    int i;

    int randomRange = (*valuesInsideBST).size();
    int searchRandom;

    for(i=0;i<numberOfTests;i++){
        searchRandom = valuesInsideBST->at(rand()%randomRange);
        minCompare += searchBST(root,1);
        avgCompare += searchBST(avgRoot,searchRandom);
        maxCompare += searchBST(root,numberOfStep);
    }

    minCompare /= numberOfTests;
    avgCompare /= numberOfTests;
    maxCompare /= numberOfTests;
    FILE *f = fopen("C:\\Users\\Mona\\Desktop\\lol\\lista_4\\find.txt", "a");
    if(numberOfStep==1){
        fprintf(f, "%d %li %li %li", numberOfStep, minCompare, avgCompare, maxCompare);
    } else {
        printf("\n%d %li %li %li", numberOfStep, minCompare, avgCompare, maxCompare);
        fprintf(f, "\n%d %li %li %li", numberOfStep, minCompare, avgCompare, maxCompare);
    }
    fclose(f);
}


void runTesting(struct Node **root, struct Node **avgRoot){

    int numberOfTests = 10000;
    int randomValue;
    vector<int> valuesInsideBST;


    for(int i=1; i<=numberOfTests; i++){

        randomValue = rand() % numberOfTests; //random value from 0 to 10k
        valuesInsideBST.push_back(randomValue); //marked as IN

        insertBST(root,i);
        insertBST(avgRoot,randomValue);

        runSearch(root,avgRoot,i,&valuesInsideBST);
    }
}


int main(){

    int action;

    struct Node* root= nullptr;
    struct Node* avgRoot = nullptr;

    srand(time(NULL));

    while(1){

        printf("\nNumber of compares used in find procedure");
        printf("\nChoose one of the following options:");
        printf("\n1. Generate Plots");
        printf("\n2. Show Plots");

        printf("\nAction: ");
        scanf("%d", &action);


        switch(action){
            case 1:
                runTesting(&root,&avgRoot);
                printMax(root);
                break;
            case 2:
                system("C:\\Users\\Mona\\Desktop\\lol\\lista_4\\run.bat");
                break;
        }
    }
}
