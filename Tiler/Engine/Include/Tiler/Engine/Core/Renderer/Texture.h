#pragma once

#include <string>

namespace tiler {

	class Texture {
	public:
		Texture(const std::string& filePath);
		virtual ~Texture() = default;

		virtual void bind(uint32_t slot) const   = 0;
		virtual void unbind(uint32_t slot) const = 0;

		static Texture* create(const std::string& filePath);

	protected:
		Texture() = default;
	};

}  // namespace tiler