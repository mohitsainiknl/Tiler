#include "Tiler/Engine/Core/FileManager/FileLoader.h"

#include "Tiler/Engine/Base.h"

#include <fstream>


namespace Tiler {

	FileLoader::FileLoader(const std::string& filename) : m_FileName(filename) {

	}

	char* FileLoader::ReadFile() {
		std::ifstream file(m_FileName, std::ios::binary | std::ios::ate);
		if (!file.is_open()) {
			TL_CORE_ERROR("Error opening file : {0}", m_FileName);
			return nullptr;
		}

		std::streampos fileSize = file.tellg();
		file.seekg(0, std::ios::beg);

		char* buffer = new char[fileSize];
		file.read(buffer, fileSize);
		file.close();

		return buffer;
	}

}