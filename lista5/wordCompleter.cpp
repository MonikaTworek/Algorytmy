#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

vector<string> ae;
vector<string> fj;
vector<string> ko;
vector<string> pt;
vector<string> uz;


bool contains(vector< vector<char> > suggestedWords, vector<char> word){
    find(suggestedWords.begin(), suggestedWords.end(), word) != suggestedWords.end() ? true : false;
}

bool checkComplinaceOfWords(vector<char> firstWord, vector<char> secondWord){
    int size = firstWord.size();
    for(int i=0; i<size; i++){
        if(firstWord.at(i) != secondWord.at(i))
            return false;
    }
    return true;
}

vector<char> createWord(string word){
    vector<char> wordVector;
    for(int i=0; i<word.length(); i++)
        wordVector.push_back(word.at(i));
    return wordVector;
}

int getMinimum(int** editDistanceArray, int i, int j, bool equals){
    int minimum;
    int a = editDistanceArray[i-1][j]+1;
    int b = editDistanceArray[i][j-1]+1;
    int c = editDistanceArray[i-1][j-1];

    if(!equals)
        c++;
    if(a < b){
        if(a<c)
            minimum = a;
        else
            minimum = c;
    } else {
        if(b < c)
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

    for(i=0; i<height; i++)
        editDistanceArray[i][0] = i;

    for(j=0; j<width; j++)
        editDistanceArray[0][j] = j;

    for(i=1; i<height; i++){
        for(j=1;j<width;j++){
            if(first.at(i-1) == second.at(j-1))
                editDistanceArray[i][j] = getMinimum(editDistanceArray,i,j,true);
            else
                editDistanceArray[i][j] = getMinimum(editDistanceArray,i,j,false);
        }
    }
    return editDistanceArray[height-1][width-1];
}

void findSimiliarWords(vector<char> givenWord, vector<string> searchedWords, int maximumDistance){
    int distance = 0;
    vector<char> searched;
    int sizeOfGivenWord = givenWord.size();
    int maximumNumberOfSuggestions = 0;
    vector< vector<char> > suggestedWords;

    cout << "Did you mean: " << endl;

    for(int i=0; i<searchedWords.size();i++){
        if(maximumNumberOfSuggestions == 3)
            break;
        searched = createWord(searchedWords.at(i));
        if(checkComplinaceOfWords(givenWord,searched) && searched.size() >= sizeOfGivenWord && !contains(suggestedWords,searched)){
            distance = runEditDistance(givenWord,searched);
            if( distance <= maximumDistance){
                for(i=0; i<searched.size(); i++)
                    cout << searched.at(i);
                cout << endl;
                maximumNumberOfSuggestions++;
                suggestedWords.push_back(searched);
            }
        }
    }
    if(suggestedWords.size() == 0)
        cout << "No word found in dictionary" << endl;
}

void runWordSuggest(vector<char> givenWord, char firstLetter, int maximumDistance){
    if(firstLetter >= 'a' && firstLetter <= 'e')
        findSimiliarWords(givenWord, ae, maximumDistance);
    else if(firstLetter >= 'f' && firstLetter <= 'j')
        findSimiliarWords(givenWord, fj, maximumDistance);
    else if(firstLetter >= 'k' && firstLetter <= 'o')
        findSimiliarWords(givenWord, ko, maximumDistance);
    else if(firstLetter >= 'p' && firstLetter <= 't')
        findSimiliarWords(givenWord, pt, maximumDistance);
    else if(firstLetter >= 'u' && firstLetter <= 'z')
        findSimiliarWords(givenWord, uz, maximumDistance);
}

void loadData(){
    string line;
    std::ifstream dictionary ("C:\\Users\\Mona\\Desktop\\lista5\\dictionary.txt");
    if(dictionary.is_open()){
        while(getline(dictionary,line)){
            if(line.at(0) >= 'a' && line.at(0) <= 'e')
                ae.push_back(line);
            else if(line.at(0) >= 'f' && line.at(0) <= 'j')
                fj.push_back(line);
            else if(line.at(0) >= 'k' && line.at(0) <= 'o')
                ko.push_back(line);
            else if(line.at(0) >= 'p' && line.at(0) <= 't')
                pt.push_back(line);
            else if(line.at(0) >= 'u' && line.at(0) <= 'z')
                uz.push_back(line);
        }
    } else
        cout << "Unable to open file!";
}

int main() {
    char firstLetter;
    string firstString;
    vector<char> first;

    loadData();
    cout << "Welcome to Word-Completer program" << endl;

    while(true){
        cout << "Enter string: ";
        getline(cin,firstString);
        firstLetter = firstString.at(0);
        first = createWord(firstString);
        runWordSuggest(first, firstLetter, 4);
    }
}