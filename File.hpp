#pragma once
#include "Framework.hpp"
#include "Log.hpp"

#include <iostream>
#include <fstream>
#include <string>

namespace File {

	

	block Read(std::string& buffor, const char* mapFilePath) {
		std::ifstream file(mapFilePath);
		std::string temp;

		size current;

		while (std::getline(file, temp)) {
			//while()
			//DEBUG Log::Info("line");
			buffor += temp;
			buffor += '\n';
		}

		//file.seekg(0, std::ios::end);
		//float fileLength = file.tellg();

		file.close();
	}

}