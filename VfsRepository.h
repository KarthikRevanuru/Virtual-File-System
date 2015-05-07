//VfsRepository.h
#ifndef VFSREPOSITORY_H
#define VFSREPOSITORY_H

#include<string>
#include<vector>
//#include"VfsNodeInfo.h"
class VfsFolderInfo;
enum repo_status {CLOSE,OPEN};
class VfsNodeInfo;
const int MAX_NAME_LEN=200;
const int MAX_PATH_LEN=200;
const int MAX_NODES=2000;
struct HeaderRecord
	{
	char node_name[MAX_NAME_LEN];
	//enum nodetype {FILE1,FOLDER};
	//enum node_type nodetype;
	int node_type;
     	int offset;
        int size;
	char folder_path[MAX_PATH_LEN];//200
	};/*used to store empty headers*/

class VfsRepository{
private:
	std::string repo_name;
	enum repo_status repostatus;
	std::string repo_file_path;
	std::vector <VfsNodeInfo*> vfsnodeinfo;
	void loaderHeader();
	void saveHeader();
	int num_nodes;

public:
	VfsRepository();
	void create(std::string external_path,std::string name);
	void open(std::string external_path,std::string name);
	void close();
	void makeDir(std::string dir_path , std::string folder_name);
	void list(std::string folder,std::vector<std::string> &contents);
	void copyIn(std::string external_path, std::string internal_path);
	void copyOut(std::string internal_path,std::string external_path);

};
#endif
