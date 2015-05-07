#include "VfsFileInfo.h"
#include "VfsFile.h"
using namespace std;
string temp1;
VfsFileInfo::VfsFileInfo(std::string nodename,std::string file_path):VfsNodeInfo(nodename,FILE1)
	{
	node_path=file_path;
	}
void VfsFileInfo::save(std::string external_path,fstream& repo,string temp)
	{
	VfsFile *vf=new VfsFile();
	temp1=temp;
	file_bytes=vf->saveInVFS(external_path,repo,file_offset);
	//cout<<file_offset<<"--"<<file_bytes<<endl;	
	delete vf;
	}
void VfsFileInfo::getHeader(HeaderRecord &hr2)
	{
	strcpy(hr2.node_name,node_name.c_str());
	hr2.node_type=0;
	hr2.offset=file_offset;
	hr2.size=file_bytes;
	strcpy(hr2.folder_path,node_path.c_str());
        }
string VfsFileInfo::getPath()
{
	return node_path;
}
string VfsFileInfo::getName()
{
	return node_name;
}

/*std::streamoff VfsFileInfo::getOffset()
	{
	return file_offset();
	}
long VfsFileInfo::getSize()
	{
	return file_bytes;
	}*/
void VfsFileInfo::load(string external_path,fstream& repo)
	{
	VfsFile *vf=new VfsFile();
	vf->exportfile(external_path,repo,file_offset,file_bytes);
	delete vf;
	}
