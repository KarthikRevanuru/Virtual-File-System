#include "VfsFile.h"
#include<fstream>
#include<sstream>
#include<cstdlib>
#include <sys/stat.h>
using namespace std;
bool fileExist(const std::string& filename) 
{
	struct stat buf;
	if (stat(filename.c_str(), &buf) != -1) {
		return true;
	}
	return false;
}
VfsFile::VfsFile()
	{
	}
long VfsFile::saveInVFS(std::string external_path,fstream& repo,streamoff &file_offset)
	{
	long size;
	fstream external;
	external.open(external_path, ios::in | /*ios::out | ios::ate |*/ ios::binary);
	if(!external) throw "VFS_COPYIN: Error accessing source file in host";
	repo.seekp(0,ios::end);
	file_offset=repo.tellp();
	int i=0;
	/*external.read((char*)&data_bytes,CHUNK_SIZE);
	repo.write((char*)&data_bytes,CHUNK_SIZE);*/
	while(external.read((char*)&data_bytes,CHUNK_SIZE))
		{
		//cout<<"1"<<endl;
		repo.write((char*)&data_bytes,CHUNK_SIZE);
		i++;
		if(external.eof())
			break;
		}
	size=CHUNK_SIZE*i;
	//cout<<size<<"---"<</*repo.tellp()-file_offset*/i<<endl;
	external.close();
	repo.close();
	return size;
	}
void VfsFile::exportfile(std::string external_path,fstream& repo,std::streamoff file_offset,long file_bytes)
	{
	fstream external;
	external.open(external_path, ios::out |/* ios::out | ios::ate |*/ ios::binary);
	external.close();
	external.open(external_path, ios::in | ios::out | ios::ate | ios::binary);
	repo.seekg(file_offset,ios::beg);
	//int size=1;
	//size=file_bytes/CHUNK_SIZE;
	//cout<<size<<"---"<<file_bytes<<endl;
	/*repo.read((char*)&data_bytes,CHUNK_SIZE);
	external.write((char*)&data_bytes,CHUNK_SIZE);*/
	while(repo.read((char*)&data_bytes,CHUNK_SIZE))
		{
		external.write((char*)&data_bytes,CHUNK_SIZE);
		if(repo.tellg()==file_offset+file_bytes)
			break;
		}
	external.close();
	if(!fileExist(external_path))
		throw "VFS_COPYOUT: Unable to save file in host";
	repo.close();
	}
