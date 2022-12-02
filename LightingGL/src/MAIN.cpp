
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <functional>

#include "mine/allinclude.h"

const unsigned int W{ 1920 };
const unsigned int H{ 1080 };

int main() {
	MWindow window{ W, H };
	//MShader shader{ "src/shaders/v.vert", "src/shaders/f.frag" };

	MShader objectShader{ "src/shaders/box.vert", "src/shaders/box.frag" };
	MShader lightShader{ "src/shaders/light.vert", "src/shaders/light.frag" };

	MTexture objectTexture{ "src/textures/container2.png", GL_TEXTURE0, true };
	MTexture objectSpecular{ "src/textures/container2_specular.png", GL_TEXTURE1, true };
	MTexture ariesFace{ "src/textures/aries.png", GL_TEXTURE2, true };

	float verts[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};

	unsigned int vertexArray;
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	unsigned int vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// LIGHTING
	unsigned int lightVertexArray;
	glGenVertexArrays(1, &lightVertexArray);
	glBindVertexArray(lightVertexArray);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glm::vec3 lightPosition{ 2.f, 2.f, 2.f };
	glm::vec3 lightColor{ 1.f, 1.f, 1.f };
	glm::vec3 lightDirection{ -0.34f, 0.4f, 0.2f };
	glm::vec3 objectColor{ 1.f, 0.5f, 0.5f };
	glm::vec3 lightSize{ 0.25f,0.25f,0.25f };

	glm::mat4 UNIT{ 1.f };
	glm::mat4 toWorldSpace{ glm::rotate(UNIT, 0.f, glm::vec3{1.f, 0.f, 0.f,}) };
	glm::mat4 toViewSpace{ glm::translate(UNIT, glm::vec3{0.f, 0.f, -2.f}) };
	glm::mat4 toClipSpace{ glm::perspective(glm::radians(100.0f), (float)(W / H), 0.1f, 100.0f) };

	objectShader.Use();
	objectShader.Set("toWorldSpace", toWorldSpace);
	objectShader.Set("toViewSpace", toViewSpace);
	objectShader.Set("toClipSpace", toClipSpace);
	objectShader.Set("objectColor", objectColor);
	objectShader.Set("lightColor", lightColor);

	objectShader.Set("material.diffuse", 0);
	objectShader.Set("materialInfo.specular", 1);
	objectShader.Set("materialInfo.shine", (0.3f * 128.f));

	glm::vec3 lightAmbientStrength{ 0.1f, 0.1f, 0.1f };
	glm::vec3 lightDiffuseStrength{ 0.75f, 0.75f, 0.75f };
	glm::vec3 lightSpecularStrength{ 1.f, 1.f, 1.f };
	objectShader.Set("lightInfo.ambient", lightAmbientStrength);
	objectShader.Set("lightInfo.diffuse", lightDiffuseStrength);
	objectShader.Set("lightInfo.specular", lightSpecularStrength);
	objectShader.Set("lightInfo.position", lightPosition);
	objectShader.Set("lightInfo.kc", 1.0f);
	objectShader.Set("lightInfo.kLinear", 0.09f);
	objectShader.Set("lightInfo.kQuadratic", 0.032f);
	
	MCamera& camera = window.GetCamera();
	objectShader.Set("lightInfo.cutoff", glm::cos(glm::radians(25.f))); // Get the cosine value here on CPU instead of GPU
	objectShader.Set("lightInfo.position", camera.GetPosition());
	objectShader.Set("lightInfo.direction", camera.LookVector());
	objectShader.Set("lightInfo.innerCutoff", glm::cos(glm::radians(20.f)));

	lightShader.Use();
	lightShader.Set("toWorldSpace", toWorldSpace);
	lightShader.Set("toViewSpace", toViewSpace);
	lightShader.Set("toClipSpace", toClipSpace);
	lightShader.Set("lightColor", lightColor);
	lightShader.Set("lightPosition", lightPosition);

	// Returns a vec3 vertex position
	std::function<glm::vec3(int)> GetVertex = [verts](int index) {
		index *= 3;
		glm::vec3 vertex{ verts[index], verts[index + 1], verts[index + 2] };
		return vertex;
	};

	// Normal matrix is the transpose of the inverse of the top left 3x3 matrix in the toWorldView matrix

	while (window.Running()) {

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		MCamera& cam = window.GetCamera();
		glm::vec3 cameraPos = cam.GetPosition();
		toViewSpace = glm::lookAt(cameraPos, cameraPos + cam.LookVector(), cam.UpVector());

		// BOX
		objectShader.Use();
		glBindVertexArray(vertexArray);
		float bruh = std::sin(glfwGetTime()) * 5; //  Just moves the cube so I can see light effects
		toWorldSpace = glm::translate(UNIT, glm::vec3{ bruh, 0.f, bruh });
		toWorldSpace = glm::rotate(toWorldSpace, (glm::radians(35.f) * (float)glfwGetTime()), glm::vec3{ 1.7f, 3.4f, 2.f });
		objectShader.Set("toWorldSpace", toWorldSpace);
		objectShader.Set("toViewSpace", toViewSpace);
		objectShader.Set("eyePosition", cameraPos);

		objectShader.Set("lightInfo.cutoff", glm::cos(glm::radians(25.f))); // Get the cosine value here on CPU instead of GPU
		objectShader.Set("lightInfo.position", cameraPos);
		objectShader.Set("lightInfo.direction", cam.LookVector());

		glDrawArrays(GL_TRIANGLES, 0, 36);
		//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		// LIGHT
		lightShader.Use();
		glBindVertexArray(lightVertexArray);
		toWorldSpace = glm::translate(UNIT, lightPosition);
		toWorldSpace = glm::scale(toWorldSpace, lightSize);
		lightShader.Set("toWorldSpace", toWorldSpace);
		lightShader.Set("toViewSpace", toViewSpace);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		glfwPollEvents();
	}

}
