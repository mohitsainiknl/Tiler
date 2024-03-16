#pragma once

#include "glm/glm.hpp"

#include "Buffer/IndexBuffer.h"
#include "Buffer/VertexBuffer.h"
#include "Tiler/Engine/Core/Window.h"

#include <memory>

namespace tiler {

	class GraphicsAPI {
	public:
		enum class Type {
			AUTO   = 0,
			OPENGL = 1
		};

		static GraphicsAPI* create(Type type, void* inner_window);

		virtual ~GraphicsAPI() = default;

		virtual void initialize() = 0;
		virtual void shutdown()   = 0;

		virtual void setClearColor(const glm::vec4& color, bool do_clear) = 0;
		virtual void nextFrame(bool do_clear)                             = 0;
		virtual void setVSync(bool enabled)                               = 0;
		virtual bool isVSync() const                                      = 0;
		virtual void drawIndexed(
		    const std::shared_ptr<VertexBuffer>& vertexBuffer, const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

		struct Static {
			inline static void initialize(Type type, void* inner_window) { create(type, inner_window)->initialize(); }
			inline static void shutdown() { return m_instance->shutdown(); }

			inline static void setClearColor(const glm::vec4& color, bool do_clear = true) {
				return m_instance->setClearColor(color, do_clear);
			}
			inline static void nextFrame(bool do_clear = true) { return m_instance->nextFrame(do_clear); }
			inline static void setVSync(bool enabled) { return m_instance->setVSync(enabled); }
			inline static bool isVSync() { return m_instance->isVSync(); };
			inline static void drawIndexed(
			    const std::shared_ptr<VertexBuffer>& vertexBuffer, const std::shared_ptr<IndexBuffer>& indexBuffer) {
				return m_instance->drawIndexed(vertexBuffer, indexBuffer);
			}

			inline static Type getType() { return m_type; }
		};

	protected:
		GraphicsAPI() = default;

	private:
		static Type m_type;
		static GraphicsAPI* m_instance;
	};

}  // namespace tiler