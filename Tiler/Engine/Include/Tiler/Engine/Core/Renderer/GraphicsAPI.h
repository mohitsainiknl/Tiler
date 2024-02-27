#pragma once

#include "glm/glm.hpp"

#include "Tiler/Engine/Core/Window.h"
#include "Buffer/VertexBuffer.h"
#include "Buffer/IndexBuffer.h"

#include <memory>


namespace Tiler {

	class GraphicsAPI {
	public:
		enum class Type {
			Auto = 0,
			OpenGL = 1
		};

		static GraphicsAPI* Create(Type type, void* inner_window);

		virtual ~GraphicsAPI() = default;

		virtual void Initialize() = 0;
		virtual void Shutdown() = 0;

		virtual void SetClearColor(const glm::vec4& color, bool do_clear) = 0;
		virtual void NextFrame(bool do_clear) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;
		virtual void DrawIndexed(const std::shared_ptr<VertexBuffer>& vertexBuffer, const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

		struct Static {
			inline static void Initialize(Type type, void* inner_window) { Create(type, inner_window)->Initialize(); }
			inline static void Shutdown() { return ms_Instance->Shutdown(); }

			inline static void SetClearColor(const glm::vec4& color, bool do_clear = true) { return ms_Instance->SetClearColor(color, do_clear); }
			inline static void NextFrame(bool do_clear = true) { return ms_Instance->NextFrame(do_clear); }
			inline static void SetVSync(bool enabled) { return ms_Instance->SetVSync(enabled); }
			inline static bool IsVSync() { return ms_Instance->IsVSync(); };
			inline static void DrawIndexed(const std::shared_ptr<VertexBuffer>& vertexBuffer, const std::shared_ptr<IndexBuffer>& indexBuffer) { return ms_Instance->DrawIndexed(vertexBuffer, indexBuffer); }

			inline static Type GetType() { return ms_Type; }
		};


	protected:
		GraphicsAPI() = default;

	private:
		static Type ms_Type;
		static GraphicsAPI* ms_Instance;
	};

}