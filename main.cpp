#include"miniz.hpp"
#include<string>
#include<vector>
#include<iostream>
#include<filesystem>
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
void check_errors(const Args* arg);

int main(int argc, char** argv)
{
	auto* args = parse_args(argc, argv);
	check_errors(args);

	miniz_cpp::zip_file file(args->file_to_open);

	//show files if it required
	if (args->shoud_list)file.printdir();


	//add files to archive
	for (auto& f : args->files_to_add)
	{
		file.write(f);
	}
	file.save(args->file_to_open);


	//extract files from archive
	for (auto& f : args->files_to_extract)
	{
		if (file.has_file(f))
		{
			auto info = file.getinfo(f);
			file.extract(info, args->extracting_place);
		}
		else
		{
			std::cout << f << " is skipped. File doesn't exist." << std::endl;
		}
	}

	delete args;
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
void check_errors(const Args* arg)
{
	if (arg->file_to_open.empty())
	{
		std::cout << "no file to open! provide -o[file name] argument!";
		exit(-1);
	}
	if (!std::filesystem::exists(arg->file_to_open))
	{
		std::cout << arg->file_to_open << " doesn't exist!";
		exit(-1);
	}
	if (!arg->files_to_extract.empty() and arg->extracting_place.empty())
	{
		std::cout << "warning:files will be extracted in the current working directory.";
	}
	if (!std::filesystem::exists(arg->extracting_place))
	{
		std::cout << arg->extracting_place << " doesn't exist!";
		exit(-1);
	}
}