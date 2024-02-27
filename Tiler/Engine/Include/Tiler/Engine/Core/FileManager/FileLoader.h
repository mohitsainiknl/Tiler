#pragma once

#include <string>


namespace Tiler {

	class FileLoader {
	public:
		FileLoader(const std::string& filename);
		~FileLoader() = default;

		char* ReadFile();

	private:
		std::string m_FileName;
	};

}
