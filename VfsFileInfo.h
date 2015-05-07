//VfsFileInfo.h
#ifndef VFSFILEINFO_H
#define VFSFILEINFO_H

//#include "VfsFile.h"
//#include "VfsFolderInfo.h"
#include "VfsNodeInfo.h"
#include<cstring>
class VfsFile;
class VfsFolderInfo;
class VfsFileInfo : public VfsNodeInfo
{
private:
	//std::streamoff file_offset;
	std::string node_path;
	//long file_bytes;
	VfsFile *vfsfile;
	VfsFolderInfo *vfsfolderinfo;
public:
	std::streamoff file_offset;
	long file_bytes;
	VfsFileInfo(std::string nodename,std::string file_path);
	virtual void getHeader(HeaderRecord &hr2);
	void save(std::string ext_path,std::fstream& rep,std::string temp);
	virtual void load(std::string external_path,std::fstream& repo);
	virtual std::string getName();
	virtual std::string getPath();
	};
	//std::streamoff getOffset();
	//long getSize();


#endif
