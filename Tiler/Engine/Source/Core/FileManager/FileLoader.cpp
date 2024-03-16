#include "Tiler/Engine/Core/FileManager/FileLoader.h"

#include "Tiler/Engine/Base.h"

#include <fstream>

namespace tiler {

	FileLoader::FileLoader(const std::string& filename) : m_fileName(filename) {
	}

	char* FileLoader::readFile() {
		std::ifstream file(m_fileName, std::ios::binary | std::ios::ate);
		if (!file.is_open()) {
			TL_CORE_ERROR("Error opening file : {0}", m_fileName);
			return nullptr;
		}

		std::streampos fileSize = file.tellg();
		file.seekg(0, std::ios::beg);

		char* buffer = new char[fileSize];
		file.read(buffer, fileSize);
		file.close();

		return buffer;
	}

}  // namespace tiler