#include"miniz.hpp"
#include<string>
#include<vector>
#include<iostream>
struct Args
{
	std::string file_to_open, extracting_place;
	std::vector<std::string> files_to_add;
	std::vector<std::string> files_to_extract;
	bool shoud_list;
	Args():shoud_list(false){}
	~Args(){}
};
Args* parse_args(int argc, char** argv);
std::vector<std::string>& split(const std::string& s, 
								char delim, 
								std::vector<std::string>& elems);

int main(int argc, char** argv)
{
	auto* args = parse_args(argc, argv);

	return 0;
}
Args* parse_args(int argc, char** argv)
{
	Args* args = new Args;
	for (int i = 1; i < argc; i++)
	{
		std::string arg = argv[i];
		std::string sub = arg.substr(0,2);
		if (sub == "-l")args->shoud_list = true;
		if (sub == "-o")args->file_to_open = arg.substr(2);
		if (sub == "-a")split(arg.substr(2, arg.size()), ',', args->files_to_add);
		if (sub == "-e")split(arg.substr(2, arg.size()), ',', args->files_to_extract);
		if (sub == "-d")args->extracting_place = arg.substr(2);
	}

	return args;
}
std::vector<std::string>& split(const std::string& s,
								char delim,
								std::vector<std::string>& elems)
{
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) 
	{
		if(!item.empty())elems.push_back(item);
	}
	return elems;

}
