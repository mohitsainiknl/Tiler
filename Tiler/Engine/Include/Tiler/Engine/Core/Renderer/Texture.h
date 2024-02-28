#pragma once

#include <string>


namespace Tiler {

	class Texture {
	public:
		Texture(const std::string& filePath);
		virtual ~Texture() = default;

		virtual void Bind(uint32_t slot) const = 0;
		virtual void Unbind(uint32_t slot) const = 0;

		static Texture* Create(const std::string& filePath);

	protected:
		Texture() = default;
	};

}