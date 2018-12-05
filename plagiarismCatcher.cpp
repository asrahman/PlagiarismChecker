//
// Created by Shania Paul on 12/2/2018.
//

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <deque>
#include <cmath>
#include <stdlib.h>

using namespace std;

static const int tableSize = 103801;      //random prime number

struct FileNode
{
    int fileIndex;
    FileNode* next;
};

FileNode* HashTable[tableSize];



int hashFunction(string chunk){
    double sum=0;
    double prime = 13;
    for(int i=0; i<chunk.length(); i++){
        sum += chunk[chunk.length()-1-i]*pow(prime,i);
    }
    return (int) fmod(sum,tableSize);
}


int getdir (string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}

int main(int argc, char* argv[])
{
    deque<string> myWords; //new deck with no words
    //string dir = string(argv[1]);
    string dir = string("sm_doc_set");
    vector<string> files = vector<string>();

    //int chunkSize = atoi(argv[2]);
    int chunkSize = 8;

    getdir(dir,files);

    for (unsigned int i = 0;i < files.size();i++) {
        cout << i << files[i] << endl;
    }

    ifstream inFile;
    cout<<endl;
    cout<<files[2];
    cout<<endl;
    cout<<getdir(dir,files);
    //cout<<argv[1]<<endl;
    //string str = string(argv[1]) + "/" + files[2]; //change to 2
    string str = string("sm_doc_set/" + files[2]);
    inFile.open(str.c_str());
    if(inFile.is_open()){
        cout << "File Open" << endl;
    }

    string s;
    //inFile >> s;

    //cout << s << endl;
    cout<<endl;
    while(inFile) {
        inFile>>s;
        cout<<s<<" ";

        int i = 0;
        while (i<s.length()) {
            if (s[i] > 64 && s[i] < 91) {
                s[i] = s[i] + 32;
            }
            if ((s[i] < 97 || s[i] > 122) && (s[i]<48 || s[i]>57)) {
                s.erase(i,1);
                i--;
            }
            i++;
        }
        myWords.push_back(s);
    }
    cout<<endl;

    deque<string>::iterator it = myWords.begin();

    for(int i = 0; i<tableSize; i++){
        HashTable[i] = NULL;
    }

    while (myWords.size() > chunkSize) {
        string str1 = "";
        for (int i = 0; i < chunkSize; i++) {
            //cout << *it << " ";
            str1 += *it;
            it++;
        }
        int tableIndex = hashFunction(str1);
        if(HashTable[tableIndex] == NULL) {
            HashTable[tableIndex]->fileIndex = 2;
            HashTable[tableIndex]->next = NULL;
        }else{
            FileNode* temp = HashTable[tableIndex];
            HashTable[tableIndex]->fileIndex = 2;
            HashTable[tableIndex]->next = temp;
        }
        cout << tableIndex << endl;
        cout << HashTable[tableIndex]->fileIndex;
        myWords.pop_front();
        it = myWords.begin();
        //cout<<endl;
    }


    return 0;
}


