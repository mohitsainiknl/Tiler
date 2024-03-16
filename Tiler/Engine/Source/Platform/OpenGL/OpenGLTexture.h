#pragma once

#include "Tiler/Engine/Core/Renderer/Texture.h"

namespace tiler {

	class OpenGLTexture : public Texture {
	public:
		OpenGLTexture(const std::string& filePath);
		~OpenGLTexture() override;

		void bind(uint32_t slot) const override;
		void unbind(uint32_t slot) const override;

	private:
		uint32_t m_rendererID;

		std::string m_filePath;

		uint32_t m_width;
		uint32_t m_height;
	};

}  // namespace tiler