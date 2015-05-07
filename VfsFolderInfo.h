//VfsFolderInfo.h
#ifndef VFSFOLDERINFO_H
#define VFSFOLDERINFO_H

#include<string>
#include<vector>
#include<cstring>
#include<iostream>
#include "VfsNodeInfo.h"
class VfsFileInfo;
class VfsFolderInfo : public VfsNodeInfo{
public:
	VfsFolderInfo(std::string nodename,std::string nodepath);
	std::string node_path;
	std::vector <VfsNodeInfo*> fileinfo;
	std::vector <VfsNodeInfo*> folderinfo;
	VfsNodeInfo *parent;
	//std::string getPath();
	virtual void getHeader(HeaderRecord &hr2);
	//void addChildFolder(VfsFolderInfo *f);
	//void addChildFile(VfsFileInfo *f)
	//void setParentFolder(VfsFolderInfo *x);
	virtual void showFiles(std::vector<std::string> & contents);
	virtual void showFolders(std::vector<std::string> & contents);
	virtual std::string getPath();
	virtual std::string getName();
	virtual void addChildFolder(VfsNodeInfo * childFolder);
	virtual void addChildFile(VfsNodeInfo * childFile);
	virtual void setParentFolder(VfsNodeInfo * parentFolder);
	};

#endif
