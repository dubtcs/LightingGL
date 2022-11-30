
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "mine/allinclude.h"

const unsigned int W{ 1920 };
const unsigned int H{ 1080 };

int main() {
	MWindow window{ W, H };
	MShader shader{ "src/shaders/v.vert", "src/shaders/f.frag" };

	float verts[]{
		0.5, 0.5, 0.5, // FTR 0
		0.5, -0.5, 0.5, // FBR 1
		-0.5, -0.5, 0.5, // FBL 2
		-0.5, 0.5, 0.5, // FTL 3

		0.5, 0.5, -0.5, // BTR 4
		0.5, -0.5, -0.5, // BBR 5
		-0.5, -0.5, -0.5, // BBL 6
		-0.5, 0.5, -0.5 // BTL 7
	};
	unsigned int indices[]{
		0, 1, 2,
		0, 3, 2,

		0, 5, 1,
		4, 5, 0,

		4, 5, 7,
		7, 5, 6,

		7, 3, 6,
		3, 2, 6,

		0, 4, 3,
		3, 4, 7,

		1, 5, 2,
		2, 5, 6
	};

	unsigned int vertexArray;
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	unsigned int vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	unsigned int elementBuffer;
	glGenBuffers(1, &elementBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glm::mat4 UNIT{ 1.f };
	glm::mat4 toWorldSpace{ glm::rotate(UNIT, 0.f, glm::vec3{1.f, 0.f, 0.f,}) };
	glm::mat4 toViewSpace{ glm::translate(UNIT, glm::vec3{0.f, 0.f, -2.f}) };
	glm::mat4 toClipSpace{ glm::perspective(glm::radians(100.0f), (float)(W / H), 0.1f, 100.0f) };

	shader.Use();
	shader.Set("toWorldSpace", toWorldSpace);
	shader.Set("toViewSpace", toViewSpace);
	shader.Set("toClipSpace", toClipSpace);

	// LIGHTING
	unsigned int lightVertexArray;
	glGenVertexArrays(1, &lightVertexArray);
	glBindVertexArray(lightVertexArray);

	unsigned int lightVertexBuffer;
	glGenBuffers(1, &lightVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, lightVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	unsigned int lightElementBuffer;
	glGenBuffers(1, &lightElementBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lightElementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glm::vec3 lightPosition{ 2.f, 2.f, 2.f };
	glm::vec3 lightColor{ 1.f, 1.f, 1.f };
	glm::vec3 objectColor{ 1.f, 0.5f, 0.5f };
	glm::vec3 lightSize{ 0.25f,0.25f,0.25f };

	shader.Set("objectColor", objectColor);
	shader.Set("lightColor", lightColor);

	while (window.Running()) {

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		MCamera& cam = window.GetCamera();
		toViewSpace = glm::lookAt(cam.GetPosition(), cam.GetPosition() + cam.LookVector(), cam.UpVector());

		// BOX
		glBindVertexArray(vertexArray);
		toWorldSpace = glm::translate(UNIT, glm::vec3{ 0.f,0.f,0.f });
		shader.Set("toWorldSpace", toWorldSpace);
		shader.Set("objectColor", objectColor);
		shader.Set("toViewSpace", toViewSpace);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		// LIGHT
		glBindVertexArray(lightVertexArray);
		toWorldSpace = glm::translate(UNIT, lightPosition);
		toWorldSpace = glm::scale(toWorldSpace, lightSize);
		shader.Set("toWorldSpace", toWorldSpace);
		shader.Set("objectColor", lightColor);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		glfwPollEvents();
	}

}
