#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

vector<char> getRandomWord(int lengthOfWord){
    vector<char> word;
    char randomLetter;

    for(int i=0;i<lengthOfWord;i++){
        randomLetter = 'a' + rand()%26;
        word.push_back(randomLetter);
    }
    return word;
}

vector<char> getLCS(int** lcsArray, vector<char> first, vector<char> second, int i, int j){
    vector<char>lcsString;
    i--;
    j--;

    while(i>0 && j>0){
        if(first.at(i-1) == second.at(j-1)){
            lcsString.insert(lcsString.begin(),first.at(i-1));
            i--;
            j--;
        } else if(lcsArray[i-1][j] > lcsArray[i][j-1])
            i--;
        else
            j--;
    }
    return lcsString;
}


void runLCS(vector<char> first, vector<char> second, int* compares){
    int i;
    int j;
    int height = first.size()+1;//size of string + 1 for 0's
    int width = second.size()+1;
    int **lcsArray = new int *[height];

    for(i=0; i<height; i++)
        lcsArray[i] = new int[width];
    for(i=0;i<height;i++)
        lcsArray[i][0] = 0;
    for(j=0;j<width;j++)
        lcsArray[0][j] = 0;
    for(i=1;i<height;i++){
        for(j=1;j<width;j++){
            (*compares)++;
            if(first.at(i-1) == second.at(j-1))
                lcsArray[i][j] = lcsArray[i-1][j-1]+1;
            else
                lcsArray[i][j] = max(lcsArray[i][j-1],lcsArray[i-1][j]);
        }
    }

    vector<char> lcs = getLCS(lcsArray,first,second,height,width);
}

void runTests(int numberOfStep){
    if(numberOfStep == 1){
        FILE *f = fopen("C:\\Users\\Mona\\Desktop\\lista5\\lcs.txt", "w");
        fprintf(f, "");
        fclose(f);
    }

    int compares = 0;
    int numberOfTests = 100;
    int avgCompare = 0;
    int i;
    int length1;
    int length2;
    int abc;

    vector<char> firstWord;
    vector<char> secondWord;

    for(i=1; i<=numberOfTests; i++){
        //drawing two lengths
        length1 = 0 + (rand() % (int)(numberOfStep - 0 + 1));
        length2 = 0 + (rand() % (int)(numberOfStep - 0 + 1));

        firstWord = getRandomWord(length1);
        secondWord = getRandomWord(length2);

        runLCS(firstWord,secondWord,&compares);
        avgCompare += compares;
    }

    avgCompare/=numberOfTests;
    cout << avgCompare << endl;
    FILE *f = fopen("C:\\Users\\Mona\\Desktop\\lista5\\lcs.txt", "a");

    if(numberOfStep == 1)
        fprintf(f, "%d %d", numberOfStep, avgCompare);
    else
        fprintf(f, "\n%d %d", numberOfStep, avgCompare);

    fclose(f);
}

int main() {
    int action;
    int numberOfStep=1;

    while(1){
        printf("\nLongest Common Subsequence");
        printf("\nChoose one of the following options:");
        printf("\n1. Generate Plots");
        printf("\n2. Show Plots");

        printf("\nAction: ");
        scanf("%d", &action);

        switch(action){
            case 1:
                for(int i=0; i<100; i++){
                    runTests(numberOfStep);
                    numberOfStep++;
                }
                break;
            case 2:
                system("C:\\Users\\Mona\\Desktop\\lista5\\runLCS.bat");
                break;
        }
    }
}