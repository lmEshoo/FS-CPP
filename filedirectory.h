#ifndef FileDirectory_H
#define FileDirectory_H

class FileDirectory{
private:
	//4 file directories. Each has 32 bytes.
	unsigned char fileDirectory[4][32];

	//Only 256 clusters
	unsigned short int fat16[256];

	// actual_memory is an array that will hold all the data of all the
	// clusters
	//
	// since there are only 256 usable clusters, we allocate enough space
	// to hold 256 clusters = (256*4) bytes
	// index 0 is the start of sector 2 since sector 0 and 1 are reserved

	unsigned int actual_memory[1024];

public:

	FileDirectory();

	bool create(char filename[], unsigned int numberBytes);

	bool deleteFile(char filename[]);

	bool read(char filename[]);

	bool write(char filename[], unsigned int numberBytes, unsigned char data[],
		unsigned int year, unsigned int month, unsigned int day, unsigned int hour,
		unsigned int minute, unsigned int second);

	bool printClusters(char filename[]);

	void printDirectory();

	bool printData(char filename[], unsigned int numberBytes);
};

#endif /* FileDirectory_H */
