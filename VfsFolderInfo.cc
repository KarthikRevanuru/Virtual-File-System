#include "VfsFolderInfo.h"
using namespace std;
VfsFolderInfo::VfsFolderInfo(std::string nodename,std::string nodepath):VfsNodeInfo(nodename,FOLDER)
	{
	node_path=nodepath;
	}
void VfsFolderInfo::getHeader(HeaderRecord &hr2)
	{
	strcpy(hr2.node_name,node_name.c_str());
	hr2.node_type=1;
	strcpy(hr2.folder_path,node_path.c_str());
	}
/*void VfsFolderInfo::addChildFolder(VfsFolderInfo *f)
	{
	folderinfo.push_back(f);
	}
void VfsFolderInfo::setParentFolder(VfsFolderInfo *x)
	{
	 parent=x;
	}
void VfsFolderInfo::addChildFile(VfsFileInfo *f)
	{
	fileinfo.push_back(f);
	}*/
void VfsFolderInfo::addChildFile(VfsNodeInfo * childFile) 
{
	fileinfo.push_back(childFile);
}

void VfsFolderInfo::addChildFolder(VfsNodeInfo * childFolder) 
{
	folderinfo.push_back(childFolder);
}

void VfsFolderInfo::setParentFolder(VfsNodeInfo * parentFolder) 
{
	parent = parentFolder;
}
void VfsFolderInfo::showFiles(vector<string> & contents) 
{
	for(int i=0; i<fileinfo.size() ; i++)
	{
		string temp_path = fileinfo[i]->getPath();
		string temp_name = fileinfo[i]->getName();
		string full_name_str;
		if(temp_path!="/") 
			full_name_str = temp_path+"/"+temp_name;
		else
			full_name_str = temp_path+temp_name;
		contents.push_back(full_name_str);
		
	}	
}

void VfsFolderInfo::showFolders(vector<string> & contents) 
{
	for(int i=0; i<folderinfo.size(); i++) 
	{
		string temp_path = folderinfo[i]->getPath();
		string temp_name = folderinfo[i]->getName();
		string full_name_str;
		if(temp_path!="/") 
			full_name_str = temp_path+"/"+temp_name+"/";
		else
			full_name_str = temp_path+temp_name+"/";
		contents.push_back(full_name_str);
	}
}
string VfsFolderInfo::getPath() 
{
	return node_path;
}
string VfsFolderInfo::getName()
{
	return node_name;
}
