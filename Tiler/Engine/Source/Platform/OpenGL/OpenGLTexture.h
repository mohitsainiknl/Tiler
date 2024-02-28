#pragma once

#include "Tiler/Engine/Core/Renderer/Texture.h"


namespace Tiler {

	class OpenGLTexture : public Texture {
	public:
		OpenGLTexture(const std::string& filePath);
		~OpenGLTexture() override;

		void Bind(uint32_t slot) const override;
		void Unbind(uint32_t slot) const override;

	private:
		uint32_t m_RendererID;

		std::string m_FilePath;

		uint32_t m_Width;
		uint32_t m_Height;
	};

}