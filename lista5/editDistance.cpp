#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int getMinimum(int** editDistanceArray, int i, int j, bool equals){
    int minimum;

    int a = editDistanceArray[i-1][j]+1;
    int b = editDistanceArray[i][j-1]+1;
    int c = editDistanceArray[i-1][j-1];

    if(!equals)
        c++;

    if(a<b){
        if(a<c)
            minimum = a;
        else
            minimum = c;
    } else {
        if(b<c)
            minimum = b;
        else
            minimum = c;
    }

    return minimum;
}


int runEditDistance(vector<char> first, vector<char> second){
    int i;
    int j;
    int height = first.size()+1;//size of string + 1 for 0's
    int width = second.size()+1;

    int **editDistanceArray = new int *[height];

    for(i=0; i<height; i++)
        editDistanceArray[i] = new int[width];

    for(i=0;i<height;i++)
        editDistanceArray[i][0] = i;

    for(j=0;j<width;j++)
        editDistanceArray[0][j] = j;

    for(i=1;i<height;i++){
        for(j=1;j<width;j++){
            if(first.at(i-1) == second.at(j-1))
                editDistanceArray[i][j] = getMinimum(editDistanceArray,i,j,true);
            else
                editDistanceArray[i][j] = getMinimum(editDistanceArray,i,j,false);
        }
    }
    return editDistanceArray[height-1][width-1];
}

int main() {
    string firstString, secondString;
    vector<char> first, second;
    int i;

    cout << "Welcome to Edit-Distance program" << endl;
    cout << "Enter first string: ";
    getline(cin,firstString);

    cout << "Enter second string: ";
    getline(cin,secondString);

    for(i=0;i<firstString.length();i++)
        first.push_back(firstString.at(i));

    for(i=0;i<secondString.length();i++)
        second.push_back(secondString.at(i));

    int edit = runEditDistance(first,second);
    cout << "result = "<<edit;
}