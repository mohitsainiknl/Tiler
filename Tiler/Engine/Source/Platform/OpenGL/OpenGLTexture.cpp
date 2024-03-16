#include "OpenGLTexture.h"

#include "glad/glad.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Tiler/Engine/Base.h"

namespace tiler {

	OpenGLTexture::OpenGLTexture(const std::string& filePath) {
		int channels;
		int width, height;
		stbi_set_flip_vertically_on_load(1);
		unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &channels, 0);

		if (!data) {
			TL_CORE_ERROR("Failed to load texture!\n"
			              "	Path : {0}",
			    filePath);
			TL_DEBUG_BREAK();
			return;
		}

		m_width  = width;
		m_height = height;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_rendererID);
		glTextureStorage2D(m_rendererID, 1, GL_RGBA8, m_width, m_height);

		glTextureParameteri(m_rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_rendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureSubImage2D(m_rendererID, 0, 0, 0, m_width, m_height, GL_RGBA, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture::~OpenGLTexture() {
		glDeleteTextures(1, &m_rendererID);
	}

	void OpenGLTexture::bind(uint32_t slot) const {
		glBindTextureUnit(slot, m_rendererID);
	}

	void OpenGLTexture::unbind(uint32_t slot) const {
		glBindTextureUnit(slot, 0);
	}

}  // namespace tiler