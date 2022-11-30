
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
	unsigned int indices[]{ // Absolutely munted cube with holes but atleast it's there lol
		0, 1, 2, // Face 1
		2, 3, 0,

		0, 1, 4, // Face 2
		4, 5, 0,

		3, 7, 6, // Face 3
		6, 2, 3,

		4, 5, 6, // Face 4
		6, 7, 4,

		0, 3, 4, // Face 5
		4, 7, 0,

		1, 2, 5, // Face 6
		5, 6, 1
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
	glm::mat4 toWorldSpace{ glm::rotate(UNIT, glm::radians(45.f), glm::vec3{1.f, 0.f, 0.f,}) };
	glm::mat4 toViewSpace{ glm::translate(UNIT, glm::vec3{0.f, 0.f, -2.f}) };
	glm::mat4 toClipSpace{ glm::perspective(glm::radians(100.0f), (float)(W / H), 0.1f, 100.0f) };

	shader.Use();
	shader.Set("toWorldSpace", toWorldSpace);
	shader.Set("toViewSpace", toViewSpace);
	shader.Set("toClipSpace", toClipSpace);

	while (window.Running()) {

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindVertexArray(vertexArray);

		MCamera& cam = window.GetCamera();
		toViewSpace = glm::lookAt(cam.GetPosition(), cam.GetPosition() + cam.LookVector(), cam.UpVector());
		shader.Set("toViewSpace", toViewSpace);

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		glfwPollEvents();
	}

}
