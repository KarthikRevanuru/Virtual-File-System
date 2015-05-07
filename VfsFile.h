//VfsFile.h
#ifndef VFSFILE_H
#define VFSFILE_H
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<cstdlib>
#include <sys/stat.h>
//#include "VfsFileInfo.h"
class VfsFileInfo;
const int CHUNK_SIZE=1;
class VfsFile{
private:
	char data_bytes[CHUNK_SIZE];
	VfsFileInfo *vfsfileinfo;
public:
	VfsFile();
	void exportfile(std::string external_path,std::fstream& repo,std::streamoff file_offset,long file_bytes);//container to out
	long saveInVFS(std::string external_path,std::fstream& rep,std::streamoff &file_offset);//out to container
	//in is input parameter out is output 
	};

#endif
