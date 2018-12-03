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

using namespace std;


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

int main()
{
    deque<string> myWords; //new deck with no words
    string dir = string("sm_doc_set");
    vector<string> files = vector<string>();

    getdir(dir,files);

    for (unsigned int i = 0;i < files.size();i++) {
        cout << i << files[i] << endl;
    }

    ifstream inFile;
    cout<<endl;
    cout<<files[2];
    cout<<endl;
    cout<<getdir(dir,files);
    string str = "sm_doc_set/" + files[2]; //change to 2
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
            if (s[i] < 97 || s[i] > 122) {
                s.erase(i,1);
                i--;
            }
            i++;
        }
        myWords.push_back(s);
    }
    cout<<endl;

    deque<string>::iterator it = myWords.begin();

    while (myWords.size() > 6) {
        for (int i = 0; i < 6; i++) {
            cout << *it << " ";
            it++;
        }
        myWords.pop_front();
        it = myWords.begin();
        cout<<endl;
    }


    return 0;
}


