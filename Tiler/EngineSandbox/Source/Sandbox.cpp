#include "Tiler/Engine.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class EampleLayer : public tiler::Layer {
public:
	EampleLayer()
	    : Layer("Example"), m_camera(-1.6f, 1.6f, -0.9f, 0.9f), m_cameraPosition(0.0f), m_cameraRotation(0.0f) {
		m_cameraPosition.z = 5.0f;

		// clang-format off
		float cubeVertices[6 * 8] = {
			///// Position /////      ///// Color /////
			-1.0f,  1.0f,  1.0f,      1.0f, 0.0f, 0.0f,  // Front face (red)
			 1.0f,  1.0f,  1.0f,      0.0f, 1.0f, 0.0f,  // Front face (green)
			-1.0f, -1.0f,  1.0f,      0.0f, 0.0f, 1.0f,  // Front face (blue)
			 1.0f, -1.0f,  1.0f,      1.0f, 1.0f, 0.0f,  // Front face (yellow)
			-1.0f,  1.0f, -1.0f,      0.0f, 1.0f, 1.0f,  // Back face (cyan)
			 1.0f,  1.0f, -1.0f,      1.0f, 0.0f, 1.0f,  // Back face (magenta)
			-1.0f, -1.0f, -1.0f,      0.5f, 0.5f, 0.5f,  // Back face (gray)
			 1.0f, -1.0f, -1.0f,      1.0f, 1.0f, 1.0f   // Back face (white)
		};
		// clang-format on

		m_cubeVB.reset(tiler::VertexBuffer::create(cubeVertices, sizeof(cubeVertices)));
		tiler::BufferLayout cube_layout = {
		    {tiler::ShaderDataType::FLOAT3, "a_Position"},
		    {tiler::ShaderDataType::FLOAT3,    "a_Color"},
		};
		m_cubeVB->setLayout(cube_layout);

		// clang-format off
		uint32_t cubeIndices[6 * 6]{
			0, 1, 2, // Front face
			1, 3, 2,
			4, 0, 6, // Top face
			0, 2, 6,
			1, 5, 3, // Right face
			5, 7, 3,
			4, 6, 5, // Back face
			5, 6, 7,
			0, 4, 1, // Left face
			4, 5, 1,
			2, 3, 6, // Bottom face
			3, 7, 6
		};
		// clang-format on
		m_cubeIB.reset(tiler::IndexBuffer::create(cubeIndices, sizeof(cubeIndices) / sizeof(uint32_t)));

		std::string cubeVertexSource = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec3 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Color;

			void main() {
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string cubeFragmentSource = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Color;

			void main() {
				color = vec4(v_Color, 1.0);
			}
		)";

		m_cubeShader.reset(tiler::Shader::create(cubeVertexSource, cubeFragmentSource));

		float starVertices[5 * 4] = {///// Position /////  /// TXT COORD ///
		    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f, -0.5f, 0.5f,
		    0.0f, 0.0f, 1.0f};

		m_starVB.reset(tiler::VertexBuffer::create(starVertices, sizeof(starVertices)));
		// clang-format off
		tiler::BufferLayout layout = {
		    {tiler::ShaderDataType::FLOAT3, "a_Position"},
            {tiler::ShaderDataType::FLOAT2, "a_TexCoord"}
        };
		m_starVB->setLayout(layout);

		float starVertices[5 * 4] = {
			///// Position /////  /// TXT COORD ///
			-0.5f, -0.5f, 0.0f,      0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f,      1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f,      1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f,      0.0f, 1.0f
		};
		// clang-format on

		m_starTexture.reset(tiler::Texture::create("Assets/Textures/Star.png"));

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

		m_starShader.reset(tiler::Shader::create(vertexSource, fragmentSource));

		m_starShader->bind();
		m_starShader->setUniform("u_Texture", 0);

		float squareVertices[3 * 4] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 0.0f, -0.5f, 0.5f, 0.0f};

		// clang-format off
		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};
		// clang-format on

		m_squareVB.reset(tiler::VertexBuffer::create(squareVertices, sizeof(squareVertices)));
		m_squareVB->setLayout({
		    {tiler::ShaderDataType::FLOAT3, "a_Position"},
		});

		uint32_t squareIndices[6]{0, 1, 2, 2, 3, 0};
		m_squareIB.reset(tiler::IndexBuffer::create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));

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

		m_backShader.reset(tiler::Shader::create(backVertexSource, backFragmentSource));
	}

	void onRender(float timestep) override {
		if (tiler::Input::isKeyPressed(TL_KEY_LEFT)) {
			m_cameraPosition.x -= m_cameraMoveSpeed * timestep;
		} else if (tiler::Input::isKeyPressed(TL_KEY_RIGHT)) {
			m_cameraPosition.x += m_cameraMoveSpeed * timestep;
		}

		if (tiler::Input::isKeyPressed(TL_KEY_UP)) {
			m_cameraPosition.y += m_cameraMoveSpeed * timestep;
		} else if (tiler::Input::isKeyPressed(TL_KEY_DOWN)) {
			m_cameraPosition.y -= m_cameraMoveSpeed * timestep;
		}

		if (tiler::Input::isKeyPressed(TL_KEY_N)) {
			m_cameraPosition.z += m_cameraMoveSpeed * timestep;
		} else if (tiler::Input::isKeyPressed(TL_KEY_M)) {
			m_cameraPosition.z -= m_cameraMoveSpeed * timestep;
		}

		if (tiler::Input::isKeyPressed(TL_KEY_W)) {
			m_cameraRotation.z += m_cameraRotationSpeed * timestep;
		} else if (tiler::Input::isKeyPressed(TL_KEY_S)) {
			m_cameraRotation.z -= m_cameraRotationSpeed * timestep;
		}

		if (tiler::Input::isKeyPressed(TL_KEY_A)) {
			m_cameraRotation.x += m_cameraRotationSpeed * timestep;
		} else if (tiler::Input::isKeyPressed(TL_KEY_D)) {
			m_cameraRotation.x -= m_cameraRotationSpeed * timestep;
		}

		if (tiler::Input::isKeyPressed(TL_KEY_Q)) {
			m_cameraRotation.y += m_cameraRotationSpeed * timestep;
		} else if (tiler::Input::isKeyPressed(TL_KEY_E)) {
			m_cameraRotation.y -= m_cameraRotationSpeed * timestep;
		}

		tiler::GraphicsAPI::Static::setClearColor({0.1f, 0.1f, 0.1f, 1});
		tiler::GraphicsAPI::Static::setVSync(true);

		m_camera.setPosition(m_cameraPosition);
		m_camera.setRotation(m_cameraRotation);

		tiler::Renderer::sceneBegin(m_camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		for (int y = -10; y < 10; ++y) {
			for (int x = -10; x < 10; ++x) {
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				tiler::Renderer::submit(m_backShader, m_squareVB, m_squareIB, transform);
			}
		}
		m_starTexture->bind(0);
		tiler::Renderer::submit(m_starShader, m_starVB, m_starIB, glm::scale(glm::mat4(1.0f), glm::vec3(0.5f)));

		tiler::Renderer::submit(m_cubeShader, m_cubeVB, m_cubeIB, glm::scale(glm::mat4(1.0f), glm::vec3(0.3f)));

		tiler::Renderer::sceneEnd();
	}

	void onEvent(const tiler::Event& event) override {}

private:
	std::shared_ptr<tiler::Shader> m_cubeShader;
	std::shared_ptr<tiler::IndexBuffer> m_cubeIB;
	std::shared_ptr<tiler::VertexBuffer> m_cubeVB;

	std::shared_ptr<tiler::Shader> m_backShader;
	std::shared_ptr<tiler::IndexBuffer> m_squareIB;
	std::shared_ptr<tiler::VertexBuffer> m_squareVB;

	std::shared_ptr<tiler::Texture> m_starTexture;
	std::shared_ptr<tiler::Shader> m_starShader;
	std::shared_ptr<tiler::IndexBuffer> m_starIB;
	std::shared_ptr<tiler::VertexBuffer> m_starVB;

	tiler::CameraOrthographic m_camera;

	glm::vec3 m_cameraPosition;
	glm::vec3 m_cameraRotation;

	float m_cameraMoveSpeed     = 5.0f;
	float m_cameraRotationSpeed = 180.0f;
};

class Sandbox : public tiler::Application {
public:
	Sandbox() { pushOverlay(new EampleLayer()); }
	~Sandbox() {}
};

tiler::Application* tiler::createApplication() {
	return new Sandbox();
}
