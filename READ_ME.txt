READ_ME

This program consists of the file plagiarismCatcher.cpp, a makefile, and this READ_ME. The program will check for the similarities between text files and print out the names of files that are above a set threshold for similarity, in order of files with the most similarities. It may not work for larger document sets.

Input parameters:
1. Enter the path to the folder containing the documents
2. Enter the chunk size -- the number of words in a row to check for
3. Enter the minimum number of individual similarities needed to consider two files as similar.

Put the plagiarismCatcher.cpp file and the makefile in the same folder. To run the program, first enter "make" in the command line. This will make an executable program called plagiarismCatcher. Then type ./plagiarismCatcher and the input parameters listed above.  

Example:

./plagiarismCatcher /User/Documents/PlagiarismChecker/sm_doc_set 6 200