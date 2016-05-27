class FileDirectory{
private:
	//4 file directories. Each has 32 bytes.
	unsigned char fileDirectory[4][32];
	//Only 256 clusters
	unsigned short int fat16[256];
	/* actual_memory is an array that will hold all the data of all the clusters
	// since there are only 256 usable clusters, we allocate enough space
	// to hold 256 clusters = (256*4) bytes
	// index 0 is the start of sector 2 since sector 0 and 1 are reserved*/
	unsigned int actual_memory[1024];

public:
	FileDirectory();
	bool create(char filename[], unsigned int numberBytes);
		/*(1)	to check if there is an unused entry in the File Directory;
		//	Return false if not true.
		//(2)	to check if there are enough unused clusters to store the file with
		//	the numberBytes.Return false if not true.*/
	bool deleteFile(char filename[]);
		/*(0)	to check if the file to be deleted; filename[]; is in the Directory.
		//	If not; return false.
		//(1)	to change the first character of the file name in the File Directory
		//	to be zero;
		//(2)	to change all entries of the clusters of this file in the FAT to 1;
		//	i.e.; unused.*/
	bool read(char filename[]);
		/* purpose: to read  of data from data[] array from the file with
		//			the specified file name.
		//	(0)	to check if the file to be deleted; filename[];
		//		is in the Directory.If not; return false.
		//	(1)	use the file name to get the file information from the
		//		File Directory; including date; time; number of bytes and the
		//		first cluster address;
		//	(2)	use the first cluster address to get all the cluster addresses
		//		of this file from the FAT - 16;
		//	(3)	use all the cluster addresses to read the data from the disk / flash memory.*/
	bool write(char filename[], unsigned int numberBytes, char data[],
		unsigned int year, unsigned int month, unsigned int day, unsigned int hour,
		unsigned int minute, unsigned int second);
		/* purpose: to write numberBytes bytes of data from data[] array into
		//				the file with the specified file name
		//		 (0)	to look for the first unused entry(0 or 1) in the FAT - 16;
		//				and use it as the First Cluster Address.
		//		 (1)	to look for the next unused entry(0 or 1) in the FAT - 16;
		//				and use it as the Next Cluster Address; and write its value
		//				into the FAT - 16.
		//		 (2)	Repeat Step 2 until all clusters are found and the
		//				FAT - 16 is updated.
		//		 (3)	to write / update the file name; extension; date; time; file
		//				length and first cluster address into the first unused entry
		//				in the File Directory;*/
	bool printClusters(char filename[]);
		/* purpose: to print all the clusters of a file.
		//	 (1)	to check if the file to be printed; filename[];
		//	 		is in the Directory.If not; return false.
		//	 (2)	use the file name to get the file information from the File
		//	 		Directory; including the first cluster address;
		//	 (3)	use the first cluster address to get all cluster addresses
		//	 		from the FAT - 16;*/
	void printDirectory();
		/* prints all the  files of the directory.
		//	(1)	use the file name to get the file information from the
		//		File Directory; including the first cluster address;
		//	(2)	use the first cluster address to get all cluster addresses
		//		from the FAT - 16;*/
	bool printData(char filename[], unsigned int numberBytes);
	/*prints the data of a file.
	//		(1)	use the file name to get the file information from the
	//			File Directory; including the first cluster address;
	//		(2)	use the first cluster address to get all cluster addresses
	//			from the FAT - 16;
	//		(3)	use cluster address to read the data of the file.Use the file length
	//			to print these data in hexadecimal format.*/
};
