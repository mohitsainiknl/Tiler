#include "Tiler/Tiler.h"


class EampleLayer : public Tiler::Layer {
public:
	EampleLayer() : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f) {

		m_VertexArray.reset(Tiler::VertexArray::Create());

		float vertices[3 * 7] = {
			///// Position /////    /////// Color ///////
			-0.58f, -0.50f, 0.0f,   0.8f, 0.2f, 0.8f, 1.0f,
			 0.58f, -0.50f, 0.0f,   0.2f, 0.3f, 0.8f, 1.0f,
			 0.00f,  0.50f, 0.0f,   0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<Tiler::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Tiler::VertexBuffer::Create(vertices, sizeof(vertices)));
		Tiler::BufferLayout layout = {
			{ Tiler::ShaderDataType::FLOAT3, "a_Position" },
			{ Tiler::ShaderDataType::FLOAT4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3]{ 0, 1, 2 };
		std::shared_ptr<Tiler::IndexBuffer> indexBuffer;
		indexBuffer.reset(Tiler::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);


		m_SquareVA.reset(Tiler::VertexArray::Create());
		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<Tiler::VertexBuffer> squareVB;
		squareVB.reset(Tiler::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Tiler::ShaderDataType::FLOAT3, "a_Position" },
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6]{ 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Tiler::IndexBuffer> squareIB;
		squareIB.reset(Tiler::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSource = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main() {
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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

		m_Shader = std::make_shared<Tiler::Shader>(vertexSource, fragmentSource);

		std::string backVertexSource = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;

			void main() {
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string backFragmentSource = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main() {
				color = vec4(0.2, 0.2, 0.2, 1.0);
			}
		)";

		m_BackShader = std::make_shared<Tiler::Shader>(backVertexSource, backFragmentSource);
	}

	void OnRender(float timestep) override {
		if (Tiler::Input::IsKeyPressed(TL_KEY_LEFT)) {
			m_CameraPosition.x -= m_CameraMoveSpeed * timestep;
		}
		else if (Tiler::Input::IsKeyPressed(TL_KEY_RIGHT)) {
			m_CameraPosition.x += m_CameraMoveSpeed * timestep;
		}

		if (Tiler::Input::IsKeyPressed(TL_KEY_UP)) {
			m_CameraPosition.y += m_CameraMoveSpeed * timestep;
		}
		else if (Tiler::Input::IsKeyPressed(TL_KEY_DOWN)) {
			m_CameraPosition.y -= m_CameraMoveSpeed * timestep;
		}

		if (Tiler::Input::IsKeyPressed(TL_KEY_A)) {
			m_CameraRotation += m_CameraRotationSpeed * timestep;
		}
		else if (Tiler::Input::IsKeyPressed(TL_KEY_D)) {
			m_CameraRotation -= m_CameraRotationSpeed * timestep;
		}

		Tiler::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Tiler::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Tiler::Renderer::SceneBegin(m_Camera);

		Tiler::Renderer::Submit(m_BackShader, m_SquareVA);
		Tiler::Renderer::Submit(m_Shader, m_VertexArray);

		Tiler::Renderer::SceneEnd();
	}

	void OnEvent(const Tiler::Event& event) override {

	}

private:
	std::shared_ptr<Tiler::Shader> m_Shader;
	std::shared_ptr<Tiler::VertexArray> m_VertexArray;

	std::shared_ptr<Tiler::Shader> m_BackShader;
	std::shared_ptr<Tiler::VertexArray> m_SquareVA;

	Tiler::CameraOrthographic m_Camera;

	glm::vec3 m_CameraPosition;
	float m_CameraRotation = 0.0f;

	float m_CameraMoveSpeed = 5.0f;
	float m_CameraRotationSpeed = 180.0f;
};


class Launcher : public Tiler::Application {
public:
	Launcher() {
		PushOverlay(new EampleLayer());
	}
	~Launcher() {

	}
};

Tiler::Application* Tiler::CreateApplication() {

	return new Launcher();
}

