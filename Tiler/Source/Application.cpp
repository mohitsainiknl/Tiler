
#include "Tiler/Application.h"

#include "glad/glad.h"

#include "Tiler/Core.h"
#include "Tiler/Window.h"
#include "Tiler/Layer.h"
#include "Tiler/Events/KeyEvent.h"
#include "Tiler/Events/MouseEvent.h"
#include "Tiler/Events/ApplicationEvent.h"
#include "Tiler/Input.h"
#include "Tiler/ImGui/ImGuiLayer.h"
#include "Tiler/Renderer/Shader.h"
#include "Tiler/Renderer/Buffer.h"


namespace Tiler {

	Application* CreateApplication();

	Application* Application::s_Instance = nullptr;

	static GLenum ShaderDataType_to_OpenGLBaseType(ShaderDataType type) {
		switch (type)
		{
			case Tiler::ShaderDataType::FLOAT:	  return GL_FLOAT;
			case Tiler::ShaderDataType::FLOAT2:	  return GL_FLOAT;
			case Tiler::ShaderDataType::FLOAT3:	  return GL_FLOAT;
			case Tiler::ShaderDataType::FLOAT4:	  return GL_FLOAT;
			case Tiler::ShaderDataType::INT:	  return GL_INT;
			case Tiler::ShaderDataType::INT2:	  return GL_INT;
			case Tiler::ShaderDataType::INT3:	  return GL_INT;
			case Tiler::ShaderDataType::INT4:	  return GL_INT;
			case Tiler::ShaderDataType::BOOL:	  return GL_BOOL;
		}

		TL_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	Application::Application() {
		Log::init();
		TL_CORE_TRACE("Logs Initialized!");

		TL_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		Input::Initialize();
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		m_EventDispatcher = EventDispatcher();
		m_EventDispatcher.Subscribe(EventType::WINDOW_CLOSE, BIND_EVENT_FN(Application::onWindowClose));
		m_EventDispatcher.Subscribe(BIND_EVENT_FN_CUSTOM(m_LayerStack, LayerStack::OnEvent));

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		float vertices[3 * 7] = {
			//// Position ////    /////// Color ///////
			-0.5f, -0.5f, 0.0f,   0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f,   0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f,   0.8f, 0.8f, 0.2f, 1.0f
		};
		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		{
			BufferLayout layout = {
				{ ShaderDataType::FLOAT3, "a_Position" },
				{ ShaderDataType::FLOAT4, "a_Color" }
			};
			m_VertexBuffer->SetLayout(layout);
		}


		uint32_t index = 0;
		const auto& layout = m_VertexBuffer->GetLayout();
		for (const auto& element : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index,
				element.GetComponentCount(),
				ShaderDataType_to_OpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset
			);
			index++;
		}

		uint32_t indices[3]{ 0, 1, 2 };
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		std::string vertexSource = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			void main() {
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSource = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main() {
				color = vec4(v_Position + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader = std::make_unique<Shader>(vertexSource, fragmentSource);
	}

	Application::~Application() {
		Input::Distroy();
	}

	void Application::OnEvent(const Event& event) {
		m_EventDispatcher.Dispatch(event);
	}



	void Application::Run() {

		m_EventDispatcher.Subscribe(EventType::KEY_PRESSED, [](const Event& event) {
			const KeyPressedEvent& keyPressedEvent = static_cast<const KeyPressedEvent&>(event);
			int keyCode = keyPressedEvent.GetKeyCode();
			TL_CORE_DEBUG("Key pressed: {0}", (char)keyCode);
		});

		// Frame Rendering Loop
		while (m_Running) {
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->Bind();
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

			m_ImGuiLayer->OnRenderBegin();
			m_LayerStack.RenderLayers();
			m_ImGuiLayer->OnRenderEnd();
			m_Window->Update();
		}
	}

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay) {
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::onWindowClose(const Event& event) {
		m_Running = false;
	}

} // namespace Tiler


