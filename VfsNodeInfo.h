//VfsNodeInfo.h
#ifndef VFSNODEINFO_H
#define VFSNODEINFO_H

#include<string>
#include "VfsRepository.h"
enum node_type {FILE1,FOLDER};
class VfsRepository;
struct HeaderRecord;
class VfsNodeInfo{
public:
	std::string node_name;
	//void getHeader(HeaderRecord hr2);
	enum node_type nodetype;
	VfsRepository *vfsrepository;
	virtual void getHeader(HeaderRecord &hr2)=0;
	/*virtual std::streamoff getOffset();
	virtual long getSize();*/
	virtual void load(std::string external_path,std::fstream& repo);
	VfsNodeInfo(std::string nodename,node_type x);
	virtual void showFolders(std::vector<std::string>&){}
	virtual void showFiles(std::vector <std::string>&){}
	virtual std::string getPath(){}
	virtual std::string getName(){}
	virtual void setParentFolder(VfsNodeInfo*){}
	virtual void addChildFolder(VfsNodeInfo*){}
	virtual void addChildFile(VfsNodeInfo*){}
	};


#endif
