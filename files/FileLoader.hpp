#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <cerrno>

namespace FileLoader {
	
	inline void Read(std::string& out, const char* path) {
		std::ifstream in(path, std::ios::binary);
		if(in) {
			std::string contents;
			in.seekg(0, std::ios::end);
			contents.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&contents[0], contents.size());
			in.close();
			out = contents;
		} else {
			std::cout << "File not found!\n";
		}
	}



}
