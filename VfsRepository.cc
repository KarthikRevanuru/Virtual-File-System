#include "VfsRepository.h"
#include "VfsNodeInfo.h"
#include "VfsFolderInfo.h"
#include "VfsFileInfo.h"
#include "PathString.h"
#include<fstream>
#include<cstring>
#include<iostream>
#include<map>
#include <sys/stat.h>
#include "vfs_errors_def.h"
#include<algorithm>
using namespace std;
map<string ,VfsNodeInfo*> mapheader;
VfsRepository::VfsRepository(){}
bool fileExists(const std::string& filename)
	{
    	struct stat buf;
        if (stat(filename.c_str(), &buf) != -1)
	    {
	    return true;
	    }
	return false;
	}
void VfsRepository::create(string name,string external_path)
	{
	repo_name=name;
	repo_file_path=external_path;
	fstream file;
	if( fileExists(repo_file_path) )
		{
		file.open((repo_file_path/*+repo_name*/).c_str(),ios::in | ios::out | ios::binary);
		if (!file.good())
			throw VFS_CREATE_01;

		}
	else
	{
	file.open((repo_file_path/*+repo_name*/).c_str(),ios::out | ios::binary);
	if (!file.good())
		throw VFS_CREATE_01;
	file.close();
	file.open((repo_file_path/*+repo_name*/).c_str(),ios::in | ios::out | ios::binary);
	if (!file.good())
		throw VFS_CREATE_01;

	}
	int i=0;
	file.write((char*)&num_nodes,sizeof(num_nodes));
	while(i<MAX_NODES)
		{
		HeaderRecord hr;
		file.write((char*)&hr,sizeof(HeaderRecord));
		i++;
		num_nodes++;
		}
	file.close();
	}
void VfsRepository::open(string name,string external_path)
	{
	repo_name=name;
	repo_file_path=external_path;
	fstream file;
	if(repostatus==OPEN)
	      throw "Repository Already Open";
	file.open(repo_file_path.c_str(), ios::in | ios::binary);
	if (!file.good())
		throw VFS_OPEN_01;
	repostatus=OPEN;
	file.read((char*)&num_nodes,sizeof(num_nodes));
	HeaderRecord hr1;
	for(int i=0;i<num_nodes;i++)
		{
		file.read((char*) &hr1,sizeof(HeaderRecord));
		if(hr1.node_type==0)
        	{
		string node_name_str(hr1.node_name);
		string file_path_str(hr1.folder_path);
		if(file_path_str!="/")
			{
			string full_name_str(file_path_str+"/"+node_name_str);
			VfsFileInfo *f = new VfsFileInfo(node_name_str,file_path_str);
			f->file_offset=hr1.offset;
			f->file_bytes=hr1.size;
			mapheader[full_name_str]=f;
			mapheader[file_path_str]->addChildFile(f);
			f->setParentFolder(mapheader[file_path_str]);
			}
		else if(file_path_str=="/")
			{
			string full_name_str(file_path_str+node_name_str);
			VfsFileInfo *f = new VfsFileInfo(node_name_str,file_path_str);
			f->file_offset=hr1.offset;
			f->file_bytes=hr1.size;
			mapheader[full_name_str]=f;
			mapheader[file_path_str]->addChildFile(f);
			f->setParentFolder(mapheader[file_path_str]);
			}

        	}
        	else if(hr1.node_type==1)
        	{                              //it is a folder
            	string node_name_str(hr1.node_name);
            	string folder_path_str(hr1.folder_path);
            	string full_name_str;
            	if(folder_path_str=="")
            		{
                	makeDir("","");
            		}
            	else if (folder_path_str=="/" )
            		{
                	makeDir("",node_name_str);
            		}
            	else
                	makeDir(folder_path_str,node_name_str);
        	}
		}
	file.clear();
	file.close();
	}
void VfsRepository::close()
	{
	fstream file;
	if (repostatus != OPEN)
	    {
	     	throw VFS_GEN_01;
	    }
	file.open(repo_file_path.c_str(), ios::in | ios::out | ios::binary);
	if (!file.good())
		throw VFS_CLOSE_01;
	file.read((char*)&num_nodes,sizeof(num_nodes));
	num_nodes=0;
	HeaderRecord hr2;
	for(auto i=mapheader.cbegin();i!=mapheader.cend();++i)
		{
		(i->second)->getHeader(hr2);
		file.write((char*) &hr2,sizeof(HeaderRecord));
		num_nodes++;
		delete i->second;
		}
	file.seekg(0,ios::beg);
	file.write((char*)&num_nodes,sizeof(num_nodes));
	mapheader.clear();
	repostatus=CLOSE;
	file.clear();
	file.close();
	}
void VfsRepository::makeDir(std::string path , std::string fname)
	{
	auto search=mapheader.find(path+"/"+fname);
	if (repostatus == CLOSE)
    		throw VFS_GEN_01;
	if(search!=mapheader.end())
		throw VFS_MAKEDIR_02;
	int temp_count=0;
	string full_path_str = path+"/"+fname;
	auto im=mapheader.begin();
	HeaderRecord hr;
	if(path=="" && fname=="") 
	{
		temp_count=1;
		VfsFolderInfo * newFolder = new VfsFolderInfo("/","");
		mapheader["/"]=newFolder;
	}
	else if (path=="" && fname!="") 
	{
		temp_count=1;
		path="/";
		for(im=mapheader.begin(); im!=mapheader.end(); im++) 
		{
			if(path==(im->first)) 
			{
				VfsFolderInfo * newFolder = new VfsFolderInfo(fname,"/");
				
				newFolder->setParentFolder(im->second);
				im->second->addChildFolder(newFolder);
				mapheader[path+fname]=newFolder;
				break;
			}
		}
	}
	else 
	{
		for(im=mapheader.begin(); im!=mapheader.end(); im++) 
		{
			if(path==(im->first)) 
			{
				temp_count=1;
				VfsFolderInfo * newFolder = new VfsFolderInfo(fname,path); 
				newFolder->setParentFolder(im->second); 
				im->second->addChildFolder(newFolder);
				mapheader[full_path_str]=newFolder;
				break;
			}
		}	
	}
	if(temp_count==0) 
	{
		throw VFS_MAKEDIR_01;
	}
	}
void VfsRepository::list(string folder,vector<string> &contents)
	{
	if (repostatus != OPEN)
	    {
	     	throw VFS_GEN_01;
	    }
	auto search=mapheader.find(folder);
		if(search!=mapheader.end())
			{
			mapheader[folder]->showFiles(contents);
			mapheader[folder]->showFolders(contents);
			}
	else 
		throw VFS_LISTDIR_01;
	sort(contents.begin(),contents.end());
	}
void VfsRepository::copyIn(string external_path, string internal_path)
	{
	if( !fileExists(external_path) )
		throw VFS_COPYIN_03;
	if(mapheader.count(internal_path)==0)
		{
		//cout<<"3"<<mapheader.count(internal_path)<<endl;
		PathString p (internal_path,"/");
		string temp=p.excludeLast();
		string f_name=p.getLast();
		if(temp=="")
			temp+="/";
		if(mapheader.count(temp)==0)
			{
			throw VFS_COPYIN_01;
			}
		else
			{
			fstream repo;
			repo.open(repo_file_path.c_str(), ios::binary | ios::ate | ios::out | ios::in);
			VfsFileInfo *f = new VfsFileInfo(f_name,temp);
			mapheader[internal_path]=f;
			mapheader[temp]->addChildFile(f);
			f->setParentFolder(mapheader[temp]);
			f->save(external_path,repo,temp);
			}
		}
	else
		throw VFS_COPYIN_02;
	}
void VfsRepository::copyOut(string internal_path,string external_path)
	{
	if (repostatus == CLOSE)
    		throw VFS_GEN_01;
	auto search = mapheader.find(internal_path);
	if(search==mapheader.end())
		throw VFS_COPYOUT_01;
	streamoff pos;
	long size;
	VfsNodeInfo *n;
	//n=mapheader[internal_path];
	fstream repo;
	repo.open(repo_file_path.c_str(), ios::binary | ios::ate | ios::out | ios::in);
	mapheader[internal_path]->load(external_path,repo);
	}
