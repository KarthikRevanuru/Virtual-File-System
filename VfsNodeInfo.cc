#include "VfsNodeInfo.h"
#include "VfsFolderInfo.h"
#include<cstring>
VfsFolderInfo *fobj;
VfsNodeInfo::VfsNodeInfo(std::string nodename,node_type x)
	{
	node_name=nodename;
	if(x==0)
		nodetype=FILE1;
	if(x==1)
		nodetype=FOLDER;
	}
void VfsNodeInfo::load(std::string external_path,std::fstream& repo)
	{}
/*long VfsNodeInfo::getSize()
	{}
std::streamoff VfsNodeInfo::getOffset()
	{}*/
/*void VfsNodeInfo::getHeader(HeaderRecord hr2)
	{
	strcpy(hr2.node_name,node_name.c_str());
	hr2.node_type=nodetype;
	strcpy(hr2.folder_path,(fobj->getPath()).c_str());
	}*/
