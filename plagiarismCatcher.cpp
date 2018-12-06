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
#include <algorithm>

using namespace std;

static const int tableSize = 500009;      //random prime number

struct FileNode                   //For the linked list of nodes containing the index to the file vector
{
    int fileIndex;
    FileNode* next;
};

struct FileInfo                      //contains how many similarities and the two files being compared
{
    int num_collision;
    int file1;
    int file2;
};

vector<FileInfo*> collision_data; //structs of file data     vector of structs

//int num_similar = 200; //change to argv[3]

FileNode* HashTable[tableSize];            //creates hash table array

bool compareCollision (const FileInfo* file1, const FileInfo* file2) {
    return file1->num_collision > file2->num_collision;                 //need for sorting vector
}


int hashFunction(string chunk){
    double sum=0;
    double prime = 7;                                     //returns an index to the hash table
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
    deque<string> myWords;                  // creates new deck with no words
    string dir = string(argv[1]);
    //string dir = string("sm_doc_set");
    vector<string> files = vector<string>();     //creates a vector of file names

    int chunkSize = atoi(argv[2]);
    //int chunkSize = 8;

    int num_similar = atoi(argv[3]);        //threshold for suspicious activity

    getdir(dir,files);

    for(int i=0; i<files.size(); i++){                  //removes file if . or ..
        if(files[i] == "." || files[i] == ".."){
            files.erase(files.begin()+i);
            i--;
        }
    }

    for (unsigned int i = 0;i < files.size();i++) {         //print all file names
        //cout << i << files[i] << endl;
    }

    for (int i = 0; i < tableSize; i++) {         //initialize table to NULL
        HashTable[i] = NULL;
    }

for(int fileIndex=0; fileIndex < files.size(); fileIndex++) {   //big loop that goes through each file

    ifstream inFile;
    string str = string(argv[1]) + "/" + files[fileIndex]; //change to 2
    //string str = string("sm_doc_set/" + files[fileIndex]);
    inFile.open(str.c_str());
    if (inFile.is_open()) {                     //opens file
        //cout << "File Open" << endl;
    }

    string s;
    //inFile >> s;

    //cout << s << endl;
    //cout << endl;
    while (inFile) {
        inFile >> s;                  //reads word from file
        //cout << s << " ";

        int i = 0;
        while (i < s.length()) {
            if (s[i] > 64 && s[i] < 91) {         //changes capital letters to lowercase
                s[i] = s[i] + 32;
            }
            if ((s[i] < 97 || s[i] > 122) && (s[i] < 48 || s[i] > 57)) {     //removes special characters
                s.erase(i, 1);
                i--;
            }
            i++;
        }
        myWords.push_back(s);      //adds word to vector
    }
    //cout << endl;

    deque<string>::iterator it = myWords.begin();     //create vector iterator

    while (myWords.size() > chunkSize) {
        string str1 = "";
        for (int i = 0; i < chunkSize; i++) {    //create a concatenated string of entire chunk of words
            //cout << *it;
            str1 += *it;
            it++;
        }
        int tableIndex = hashFunction(str1);         //get an index from hash function

        if (HashTable[tableIndex] == NULL) {                        //if empty, add file node
                HashTable[tableIndex] = new FileNode;
                HashTable[tableIndex]->fileIndex = fileIndex;
                HashTable[tableIndex]->next = NULL;
        } else if(HashTable[tableIndex]->fileIndex != fileIndex) {  //if not empty, add to head of linked list
                FileNode *temp = new FileNode;
                temp->fileIndex = fileIndex;              //dont add repeats
                temp->next = HashTable[tableIndex];
                HashTable[tableIndex] = temp;
        }

        myWords.pop_front();           //remove front word and increment iterator to get next chunk
        it = myWords.begin();
        //cout<<endl;
    }
}

int grid[files.size()][files.size()];          //create a 2d array to contain number of similarities

for(int k=0; k<files.size(); k++){
    for(int l=0; l<files.size(); l++){        //initialize grid to 0
        grid[k][l] = 0;
    }
}

    for(int i=0; i<tableSize; i++){        //traverse through hash table

        if(HashTable[i] == NULL){
        }else {                             //if not empty
            FileNode *cur = HashTable[i];
            vector<int> nodes;
            while (cur != NULL) {
                //cout << cur->fileIndex << " ";
                nodes.push_back(cur->fileIndex);   //store all nodes in a temp vector
                cur = cur->next;
            }
            //cout << endl;

            for(int m=0; m<nodes.size()-1; m++){         //go through vector and increment in grid
                for(int n=m+1; n<nodes.size();n++){
                    grid[nodes[n]][nodes[m]]++;
                }
            }

        }

    }

    for(int k=0; k<files.size(); k++){          //traverse through grid
        for(int l=0; l<files.size(); l++){
            //cout << grid[k][l] << " ";
            if (grid[k][l] >= num_similar) {  //find cells that have more than/equal the amount of similarities as threshold
                FileInfo* temp = new FileInfo;
                temp->file1 = k;                       //create fileinfo node with the 2 files and count
                temp->file2 = l;
                temp->num_collision = grid[k][l];
                collision_data.push_back(temp);          //add to vector
            }
        }
        //cout << endl;
    }

    sort(collision_data.begin(),collision_data.end(),compareCollision);   //sort the vector

    for (int i = 0; i < collision_data.size(); i++) {
        cout<<collision_data[i]->num_collision<<": "<<files[collision_data[i]->file1]<<", "<<files[collision_data[i]->file2]<<endl;
    }

    //print final results

    return 0;
}


