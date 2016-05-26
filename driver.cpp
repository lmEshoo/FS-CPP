#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "filedirectory.h"
using namespace std;

static const char randy[] ="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

int main(int argc, char **argv){

	FileDirectory cpp;

	unsigned char data[1024];
	srand(time(0));
	for (unsigned int i = 0; i < 1024; ++i)
		data[i] = randy[rand() % (sizeof(randy)-1)]; //change it to ascii after

	cpp.write("file1", 40, data, 2014, 1, 9, 15, 26, 32);
	cpp.read("file1");
	cpp.printData("file1",40);
	cpp.printDirectory();
	cpp.printClusters("file1");

	cpp.write("file2", 200, data, 1984, 2, 8, 1, 2, 2);
	cpp.read("file2");
	cpp.printData("file2",200);
	cpp.printDirectory();
	cpp.printClusters("file2");

	cpp.write("file3", 300, data, 1996, 3, 19, 16, 17, 18);
	cpp.read("file3");
	cpp.printData("file3",300);
	cpp.printDirectory();
	cpp.printClusters("file3");

	cpp.write("file4", 500, data, 2004, 17, 4, 17, 18, 18);
	cpp.read("file4");
	cpp.printData("file4",500);
	cpp.printDirectory();
	cpp.printClusters("file4");

	cout << "deleting file2" << endl;
	cpp.deleteFile("file2");
	cpp.printDirectory();

	return 0;
}
