#include "Tiler/Engine.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/glm.hpp"



class EampleLayer : public Tiler::Layer {
public:
	EampleLayer() : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f) {

		float starVertices[5 * 4] = {
			///// Position /////  /// TXT COORD ///
			-0.5f, -0.5f, 0.0f,      0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f,      1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f,      1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f,      0.0f, 1.0f
		};

		m_StarVB.reset(Tiler::VertexBuffer::Create(starVertices, sizeof(starVertices)));
		Tiler::BufferLayout layout = {
			{ Tiler::ShaderDataType::FLOAT3, "a_Position" },
			{ Tiler::ShaderDataType::FLOAT2, "a_TexCoord" }
		};
		m_StarVB->SetLayout(layout);

		uint32_t starIndices[6]{ 0, 1, 2, 2, 3, 0 };
		m_StarIB.reset(Tiler::IndexBuffer::Create(starIndices, sizeof(starIndices) / sizeof(uint32_t)));

		m_StarTexture.reset(Tiler::Texture::Create("Assets/Textures/Star.png"));

		std::string vertexSource = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec2 v_TexCoord;

			void main() {
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSource = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec2 v_TexCoord;

			uniform sampler2D u_Texture;

			void main() {
				color = texture(u_Texture, v_TexCoord);
			}
		)";

		m_StarShader.reset(Tiler::Shader::Create(vertexSource, fragmentSource));

		m_StarShader->Bind();
		m_StarShader->SetUniform("u_Texture", 0);



		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		m_SquareVB.reset(Tiler::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		m_SquareVB->SetLayout({
			{ Tiler::ShaderDataType::FLOAT3, "a_Position" },
		});

		uint32_t squareIndices[6]{ 0, 1, 2, 2, 3, 0 };
		m_SquareIB.reset(Tiler::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));


		std::string backVertexSource = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main() {
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
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

		m_BackShader.reset(Tiler::Shader::Create(backVertexSource, backFragmentSource));
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

		Tiler::GraphicsAPI::Static::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Tiler::GraphicsAPI::Static::SetVSync(true);

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Tiler::Renderer::SceneBegin(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		for (int y = -10; y < 10; ++y) {
			for (int x = -10; x < 10; ++x) {
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Tiler::Renderer::Submit(m_BackShader, m_SquareVB, m_SquareIB, transform);
			}
		}
		m_StarTexture->Bind(0);
		Tiler::Renderer::Submit(m_StarShader, m_StarVB, m_StarIB, glm::scale(glm::mat4(1.0f), glm::vec3(0.5f)));

		Tiler::Renderer::SceneEnd();
	}

	void OnEvent(const Tiler::Event& event) override {

	}

private:
	std::shared_ptr<Tiler::Shader> m_BackShader;
	std::shared_ptr<Tiler::IndexBuffer> m_SquareIB;
	std::shared_ptr<Tiler::VertexBuffer> m_SquareVB;

	std::shared_ptr<Tiler::Texture> m_StarTexture;
	std::shared_ptr<Tiler::Shader> m_StarShader;
	std::shared_ptr<Tiler::IndexBuffer> m_StarIB;
	std::shared_ptr<Tiler::VertexBuffer> m_StarVB;

	Tiler::CameraOrthographic m_Camera;

	glm::vec3 m_CameraPosition;
	float m_CameraRotation = 0.0f;

	float m_CameraMoveSpeed = 5.0f;
	float m_CameraRotationSpeed = 180.0f;
};


class Sandbox : public Tiler::Application {
public:
	Sandbox() {
		PushOverlay(new EampleLayer());
	}
	~Sandbox() {

	}
};

Tiler::Application* Tiler::CreateApplication() {

	return new Sandbox();
}

