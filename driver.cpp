#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "filedirectory.h"
using namespace std;

static const char randy[] =
"0123456789"
"!@#$%^&*"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz";

int main(int argc, char **argv){

	FileDirectory cpp;

	unsigned char data[1024];
	srand(time(0));
	for (unsigned int i = 0; i < 1024; ++i)
		data[i] = randy[rand() % (sizeof(randy)-1)];


	cout << "creating \"file1\"" << endl << endl;
	cpp.write("file1", 40, data, 2014, 1, 9, 15, 26, 32);
	cpp.read("file1");
	cpp.printClusters("file1");

	cpp.write("file2", 200, data, 1984, 2, 8, 1, 2, 2);
	cout << endl << "printing the directory" << endl;
	cpp.printDirectory();
	cpp.printClusters("file2");

	cpp.write("file3", 300, data, 1996, 3, 19, 16, 17, 18);
	cout << endl << "printing the directory" << endl;
	cpp.printDirectory();
	cpp.printClusters("file3");

	cpp.write("file4", 500, data, 2004, 17, 4, 17, 18, 18);
	cout << endl << "printing the directory" << endl;
	cpp.printDirectory();
	cpp.printClusters("file4");

	cout << "deleting file2" << endl;
	cpp.deleteFile("file2");
	cout << endl << "printing the directory" << endl;
	cpp.printDirectory();

	cpp.write("file4", 500, data, 2015, 8, 10, 10, 0, 20);
	cout << endl << "printing the directory" << endl;
	cpp.printDirectory();
	cpp.printClusters("file4");

	return 0;
}
