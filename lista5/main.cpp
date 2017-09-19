#include <iostream>
#include <vector>

using namespace std;

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

int runLCS(vector<char> first, vector<char> second){
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
            if(first.at(i-1) == second.at(j-1))
                lcsArray[i][j] = lcsArray[i-1][j-1]+1;
            else
                lcsArray[i][j] = max(lcsArray[i][j-1],lcsArray[i-1][j]);
        }
    }

    vector<char> lcs = getLCS(lcsArray,first,second,height,width);
    cout << "LCS = ";
    for(i=0;i<lcs.size();i++)
        cout << lcs.at(i);
    cout << endl;
    return lcsArray[height-1][width-1];
}

int main() {
    string firstString, secondString;
    vector<char> first, second;
    int i;
    cout << "Welcome to LCS program" << endl;
    cout << "Enter first string: ";
    getline(cin,firstString);
    cout << "Enter second string: ";
    getline(cin,secondString);

    for(i=0;i<firstString.length();i++)
        first.push_back(firstString.at(i));
    for(i=0;i<secondString.length();i++)
        second.push_back(secondString.at(i));
    int result = runLCS(first,second);
    cout << result << endl;
}