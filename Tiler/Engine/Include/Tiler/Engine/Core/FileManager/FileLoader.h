#pragma once

#include <string>

namespace tiler {

	class FileLoader {
	public:
		FileLoader(const std::string& filename);
		~FileLoader() = default;

		char* readFile();

	private:
		std::string m_fileName;
	};

}  // namespace tiler
