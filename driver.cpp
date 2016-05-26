#include "stdafx.h"
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

int stringLength = sizeof(randy)-1;
//To generate random data to store
char genRandom(){ return randy[rand() % stringLength];}


int main(int argc, char **argv){
	// create an instance of a FAT-based filesystem
	FileDirectory cpp;

	// declare an array that will contain the data to be written pertaining
	// to a particular file
	unsigned char data[1024];
	srand(time(0));
	std::string Str;
	for (unsigned int i = 0; i < 1024; ++i){
		data[i] = genRandom();
	}

	// 1. creating and writing a file, "file1", with a size of 40 bytes
	cout << "creating \"file1\"" << endl << endl;
	// creating "file1"
	cpp.write("file1", 40, data, 2014, 1, 9, 15, 26, 32);
	//cout << endl << "printing the directory" << endl;
	// printing the contents of the directory
	cpp.read("file1");
	//cpp.printDirectory();
	// printing the clusters that hold "file1"
	cpp.printClusters("file1");
	//cpp.printData("file1", 40);

	// 2. create and write a file, "file2", with a size of 200 bytes
	//cout << "creating \"file2\"" << endl << endl;
	// creating "file2"
	cpp.write("file2", 200, data, 1984, 2, 8, 1, 2, 2);
	//cout << endl << "printing the directory" << endl;
	// printing the contents of the directory
	cpp.printDirectory();
	// printing the clusters that hold "file2"
	cpp.printClusters("file2");

	// 3. create and write a file, "file3", with a size of 300 bytes
	//cout << "creating \"file3\"" << endl;
	// creating "file3"
	cpp.write("file3", 300, data, 1996, 3, 19, 16, 17, 18);
	//cout << endl << "printing the directory" << endl;
	// printing the contents of the directory
	cpp.printDirectory();
	// printing the cluster that hold "file3"
	cpp.printClusters("file3");

	// 4. create and write a file, "file4", with a size of 500 bytes
	cout << "creating file4" << endl;
	// creating "file4"
	cpp.write("file4", 500, data, 2004, 17, 4, 17, 18, 18);
	// printing the contents of the directory
	cpp.printDirectory();
	// printing the clusters that hold "file 4"
	cpp.printClusters("file4");

	// 5. delete files
	cout << "deleting file2" << endl;
	// deleting "file2"
	//cpp.delete_file("file3");
	cpp.deleteFile("file2");
	cout << endl << "printing the directory" << endl;
	// printing the contents of the directory
	cpp.printDirectory();

	cout << "creating file4" << endl;
	// since we know that creating "file4" previously
	// will fail, we will try again
	cpp.write("file4", 500, data, 2015, 8, 10, 10, 0, 20);
	cout << endl << "printing the directory" << endl;
	// printing the contents of the directory
	cpp.printDirectory();
	// attempting to print the clusters that hold "file4"
	// if it exists
	cpp.printClusters("file4");

	return 0;
}
