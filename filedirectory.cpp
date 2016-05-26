#include <iostream>
#include "filedirectory.h"
using namespace std;

FileDirectory::FileDirectory() {
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 32; j++)
			fileDirectory[i][j] = 0;
	for(int i = 0; i < 256; i++) fat16[i] = 0;
	for(int i = 0; i < 1024; i++) actual_memory[i] = 0;
}//FileDirectory::FileDirectory()

bool FileDirectory::create(char filename[], unsigned int numberBytes){
	bool unused_entry_found = false;
	unsigned int entry_index = 0;
	for(int i = 0; i < 4; i++)
		if(fileDirectory[i][0] == 0) {
			unused_entry_found = true;
			entry_index = i;
			break;
		}//if

	unsigned int required_clusters_for_data = (numberBytes + 4) / 4;
	unsigned int number_of_unused_clusters = 0;
	bool enough_unused_clusters = false;

	for(int i = 2; i < 256; i++)
	if(fat16[i] == 0 || fat16[i] == 1)
		number_of_unused_clusters++;

	if(required_clusters_for_data <= number_of_unused_clusters)
		enough_unused_clusters = true;

	if(unused_entry_found && enough_unused_clusters) {
		for(int j = 0; j < 8; j++)
			fileDirectory[entry_index][j] = filename[j];
		return true;
	}//if
}//FileDirectory::create(char filename[], unsigned int numberBytes)

bool FileDirectory::deleteFile(char filename[]){
	bool found = false;
	int i, j;
	unsigned short int first_sector, sectors[256];
	//look for it
	for(i = 0; i < 4; i++){
		for(j = 0; j < 8; j++)
			if(filename[j] != fileDirectory[i][j]) break;

		if(j == 8){
			found = true;
			break;
		}//if
	}//for

	if(found == false){
		return false;
	} else{
		for(j = 0; j < 8; j++) fileDirectory[i][j] = 0;
		first_sector = fileDirectory[i][26] * 256 + fileDirectory[i][27];
		i = 0;
		sectors[i] = first_sector;
		while(fat16[sectors[i]] != 0xFFFF){ //end of file
			sectors[i + 1] = fat16[sectors[i]];
			fat16[sectors[i]] = 0;
			i++;
		}//while
		fat16[sectors[i]] = 0;
	}//else

	return true;
}//FileDirectory::deleteFile(char filename[])

bool FileDirectory::read(char filename[]){
	bool found = false;
	int i, j;
	unsigned short int first_sector, sectors[256];
	for(i = 0; i < 4; i++){
		for(j = 0; j < 8; j++){
			if(filename[j] != fileDirectory[i][j]) break;
		}//for
		if(j == 8){
			found = true;
			break;
		}//if
	}//for

	if(i == 4) return false;

	unsigned int firstSector = fileDirectory[i][26] * 256 + fileDirectory[i][27];
	unsigned int date = fileDirectory[i][24] * 256 + fileDirectory[i][25];
	unsigned int time = fileDirectory[i][22] * 256 + fileDirectory[i][23];

	unsigned int year = 0, month = 0, day = 0, hour = 0, minute = 0, second = 0;

	month = (date >> 5) & 0xF;
	year = (date >> 9) + 1980;
	day = (date & 0x1F);
	second = (time & 0x1F) * 2;
	hour = time >> 11;
	minute = (time >> 5) & 0x3F;

    cout<<"NEW FILE:"<<endl;
	cout << "name:" << "\t" << "Date: " << "\t\t" << "Time: " << "\t\t"
            << "First cluster address: " << "\n";
	cout << filename << "\t" << month << "/" << day << "/" << year
        << "\t" << hour << ":" << minute << ":" << second << "\t" << firstSector << "\n\n";
}//FileDirectory::read(char filename[])

bool FileDirectory::write(char filename[], unsigned int numberBytes,
	unsigned char data[], unsigned int year, unsigned int month, unsigned int day,
	unsigned int hour, unsigned int minute, unsigned int second){
	//purpose: to write numberBytes bytes of data from data[] array into the file with the specified file name
	unsigned short int firstClusterAddress, fileNumber, date, time, fc;
	unsigned short int lastClusterAddress;

	for(firstClusterAddress = 2; firstClusterAddress < 256; firstClusterAddress++){
		if(fat16[firstClusterAddress] == 0)
			break;
	}//for
	if(firstClusterAddress == 256) return false;
	int j = 1;
	lastClusterAddress = firstClusterAddress;

	for(int m = 1; m < (numberBytes / 4) + ((numberBytes % 4 != 0) ? 1 : 0); m++){
		for(j = 2; j < 256; j++){
			if((fat16[j] == 0 || fat16[j] == 1) && j != lastClusterAddress){
				fat16[lastClusterAddress] = j;
				lastClusterAddress = j;
				break;
			}//if
		}//for
		if(j == 256) return false;
	}//for

	unsigned int sectors_required = j;

	unsigned int sectors[256];

	fat16[lastClusterAddress] = 0xFFFF; //end of file

	unsigned short int sector_num = 2;

	while (fat16[sector_num] != 0 && fat16[sector_num] != 1) sector_num++;

	unsigned int firstsector = sector_num;

	for(fileNumber = 0; fileNumber < 4; fileNumber++){
		if (fileDirectory[fileNumber][0] == 0) break;
	}
	if(fileNumber == 4) return false;	//file directory is full
	for(int j = 0; j < 8; j++) fileDirectory[fileNumber][j] = filename[j];	//write file name

	date = ((year - 1980) << 9) + (month << 5) + day;
	fileDirectory[fileNumber][24] = date >> 8;	//MSB
	fileDirectory[fileNumber][25] = date;	//LSB
	time = (hour << 11) + (minute << 5) + second / 2;
	fileDirectory[fileNumber][22] = time >> 8;	//MSB
	fileDirectory[fileNumber][23] = time;	//LSB

	fileDirectory[fileNumber][28] = numberBytes >> 24;	//MSB
	fileDirectory[fileNumber][29] = numberBytes >> 16;		//LSB
	fileDirectory[fileNumber][30] = numberBytes >> 8;		//MSB
	fileDirectory[fileNumber][31] = numberBytes;		//LSB

	fileDirectory[fileNumber][26] = firstClusterAddress >> 8;	//MSB
	fileDirectory[fileNumber][27] = firstClusterAddress;	//LSB

	for(int i = 0; i < sectors_required; i++) actual_memory[i] = data[i];
}//FileDirectory::write(...)

bool FileDirectory::printClusters(char filename[]){
	//print all clusters for file
	int i, j;
	for(i = 0; i < 4; i++){
		for(j = 0; j < 8; j++){
			if(fileDirectory[i][j] != filename[j])
				break;
		}//for
		if(j == 8) break;
	}//for
	if(i == 4) return false;	//no file with that name
	cout << "\n" << "clusters of " << filename << endl;

	unsigned int firstSector = fileDirectory[i][26] * 256 + fileDirectory[i][27];
	unsigned int sectorAddress = firstSector;
	int k = 1;

	while(sectorAddress != 0xFFFF){ //end of file
		cout << sectorAddress << " -> ";
		k++;
		sectorAddress = fat16[sectorAddress];
	}//for
	cout << "FF" << endl <<endl;
}//FileDirectory::printClusters(char filename[])


void FileDirectory::printDirectory(){
	cout << "ls: ";
	//Print the file name of all files that currently exist in the directory
	for (int i = 0; i < 4; i++){
		if (fileDirectory[i][0] != 0){
			for (int j = 0; j < 32; j++){
				//if eof
				if (fileDirectory[i][j] == '\0') break;
				cout << fileDirectory[i][j];
			}//for
			cout << " ";
		}//if
	}//for
	cout << "\n";
	return;
}//FileDirectory::printDirectory()

//Print the data put into a file
bool FileDirectory::printData(char filename[], unsigned int numberBytes){
	unsigned int sectors_required = (numberBytes + 4) / 4;
  cout<<"cat "<<filename<<endl;
	for (int i = 0; i < sectors_required; i++) cout << char(actual_memory[i]);
  cout<<endl<<endl;
	return true;
}//FileDirectory::printData(char filename[], unsigned int numberBytes)
