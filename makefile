final: plagiarismCatcher.o
	g++ -o plagiarismCatcher plagiarismCatcher.o
driver: plagiarismCatcher.cpp
	g++ -c plagiarismCatcher.cpp