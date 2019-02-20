#include "../headers/graphics.h"

void Graphics::init(void) {
	shaderMap["simple_color_shader"] = Shader("../Math-Visualization/shaders/simple_color_shader.vs", "../Math-Visualization/shaders/simple_color_shader.frag");

	projection_location = glGetUniformLocation(shaderMap["simple_color_shader"].ID, "projection");
	model_view_location = glGetUniformLocation(shaderMap["simple_color_shader"].ID, "model_view");

	model_view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

	generateGrid(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0, 0.0, 0.1);
	//TODO: Skybox maybe
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
}

void Graphics::clean(void) {

}

void Graphics::display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (!objects.empty()) {
		for (std::vector<GraphicsObject>::iterator it = objects.begin(); it != objects.end(); ++it) {
			switch (it->type) {
			case 0:
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

				shaderMap["simple_color_shader"].use();
				glBindVertexArray(it->VAO);
				glUniformMatrix4fv(projection_location, 1, GL_FALSE, (GLfloat *)&projection);
				glUniformMatrix4fv(model_view_location, 1, GL_FALSE, (GLfloat *)&model_view);
				glUniformMatrix4fv(it->ctm_location, 1, GL_FALSE, (GLfloat *)&it->ctm);
				glDrawArrays(GL_TRIANGLES, 0, it->num_vertices);
				break;
			case 1:
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

				shaderMap["simple_color_shader"].use();
				glBindVertexArray(it->VAO);
				glUniformMatrix4fv(projection_location, 1, GL_FALSE, (GLfloat *)&projection);
				glUniformMatrix4fv(model_view_location, 1, GL_FALSE, (GLfloat *)&model_view);
				glUniformMatrix4fv(it->ctm_location, 1, GL_FALSE, (GLfloat *)&it->ctm);
				glDrawArrays(GL_LINES, 0, it->num_vertices);
				break;
			}
		}
	}

	glfwSwapBuffers(window);
}

void Graphics::idle(void) {
	/*for (std::vector<GraphicsObject>::iterator it = objects.begin(); it != objects.end(); ++it) {
		if(it->ID == 1) {
			glm::vec3 highlight = cameraPos + 3.0f * cameraFront;
			highlight.x = (int)highlight.x;
			highlight.y = (int)highlight.y;
			highlight.z = (int)highlight.z;
			it->ctm = glm::translate({ { 1.0, 0.0, 0.0, 0.0 },{ 0.0, 1.0, 0.0, 0.0 },{ 0.0, 0.0, 1.0, 0.0 },{ 0.0, 0.0, 0.0, 1.0 } }, highlight);
		}
	}*/

	display();
}

void Graphics::generateGrid(GLfloat minX, GLfloat maxX, GLfloat minY, GLfloat maxY, GLfloat minZ, GLfloat maxZ, int minorLines, GLfloat resolution) {
	GraphicsObject grid;
	//int it;
	//GLfloat i, j, k;
	//int num_vert = 0;

	/*if (fmod(minX,resolution) == 0.0) {
		num_vert += 2;
	}
	if (fmod(minY, resolution) == 0.0) {
		num_vert += 2;
	}
	if (fmod(minZ, resolution) == 0.0) {
		num_vert += 2;
	}
	for (i = minX; i <= maxX; i += resolution) {	
		for (j = minY; j <= maxY; j += resolution) {
			for (k = minZ; k <= maxZ; k += resolution) {
				num_vert += 2;
			}
		}
	}*/

	grid.ID = 0;
	grid.type = 1;
	grid.num_vertices = 6; // num_vert;

	grid.position_array = (glm::vec4*)malloc(sizeof(glm::vec4) * (grid.num_vertices));
	grid.color_array = (glm::vec4*)malloc(sizeof(glm::vec4) * (grid.num_vertices));

	/*if (minX <= 0.0 && maxX >= 0.0) {

	}
	if (minY <= 0.0 && maxY >= 0.0) {

	}
	if (minZ <= 0.0 && maxZ >= 0.0) {

	}*/

	grid.position_array[0] = glm::vec4(minX, 0.0, 0.0, 1.0);
	grid.position_array[1] = glm::vec4(maxX, 0.0, 0.0, 1.0);
	grid.position_array[2] = glm::vec4(0.0, minY, 0.0, 1.0);
	grid.position_array[3] = glm::vec4(0.0, maxY, 0.0, 1.0);
	grid.position_array[4] = glm::vec4(0.0, 0.0, minZ, 1.0);
	grid.position_array[5] = glm::vec4(0.0, 0.0, maxZ, 1.0);
	grid.color_array[0] = glm::vec4(1.0, 0.0, 0.0, 1.0);
	grid.color_array[1] = glm::vec4(1.0, 0.0, 0.0, 1.0);
	grid.color_array[2] = glm::vec4(0.0, 1.0, 0.0, 1.0);
	grid.color_array[3] = glm::vec4(0.0, 1.0, 0.0, 1.0);
	grid.color_array[4] = glm::vec4(0.0, 0.0, 1.0, 1.0);
	grid.color_array[5] = glm::vec4(0.0, 0.0, 1.0, 1.0);

	glGenVertexArrays(1, &grid.VAO);
	glBindVertexArray(grid.VAO);
	glGenBuffers(1, &grid.VBO);
	glBindBuffer(GL_ARRAY_BUFFER, grid.VBO);
	glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(glm::vec4) * grid.num_vertices, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec4) * grid.num_vertices, grid.position_array);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * grid.num_vertices, sizeof(glm::vec4) * grid.num_vertices, grid.color_array);
	vPosition = glGetAttribLocation(shaderMap["simple_color_shader"].ID, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	vColor = glGetAttribLocation(shaderMap["simple_color_shader"].ID, "vColor");
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid *)(sizeof(glm::vec4) * grid.num_vertices));

	grid.ctm_location = glGetUniformLocation(shaderMap["simple_color_shader"].ID, "ctm");

	objects.push_back(grid);

	return;
}

void Graphics::generateGraph(Graph graph) {
	GraphicsObject graph_object;
	int it, i, j;
	
	graph_object.ID = 1;
	graph_object.type = 0;
	graph_object.num_vertices = graph.size * graph.size * 6;

	graph_object.position_array = (glm::vec4*)malloc(sizeof(glm::vec4) * (graph_object.num_vertices));
	graph_object.color_array = (glm::vec4*)malloc(sizeof(glm::vec4) * (graph_object.num_vertices));

	it = 0;
	for (i = 0; i < graph.size; i++) {
		for (j = 0; j < graph.size; j++) {
			graph_object.position_array[it] = glm::vec4(graph.minX + graph.resX * i, graph.f[i][j], graph.minY + graph.resY * j,  1.0);
			graph_object.position_array[it+1] = glm::vec4(graph.minX + graph.resX * (i + 1), graph.f[i + 1][j], graph.minY + graph.resY * j,  1.0);
			graph_object.position_array[it+2] = glm::vec4(graph.minX + graph.resX * (i + 1), graph.f[i + 1][j + 1], graph.minY + graph.resY * (j + 1),  1.0);
			graph_object.position_array[it+3] = glm::vec4(graph.minX + graph.resX * i, graph.f[i][j], graph.minY + graph.resY * j,  1.0);
			graph_object.position_array[it+4] = glm::vec4(graph.minX + graph.resX * (i + 1), graph.f[i + 1][j + 1], graph.minY + graph.resY * (j + 1),  1.0);
			graph_object.position_array[it+5] = glm::vec4(graph.minX + graph.resX * i, graph.f[i][j + 1], graph.minY + graph.resY * (j + 1),  1.0);
			it += 6;
		}
	}

	for (it = 0; it < graph_object.num_vertices; it++) {
		graph_object.color_array[it] = glm::vec4(1.0, 1.0, 1.0, 1.0);
	}

	glGenVertexArrays(1, &graph_object.VAO);
	glBindVertexArray(graph_object.VAO);
	glGenBuffers(1, &graph_object.VBO);
	glBindBuffer(GL_ARRAY_BUFFER, graph_object.VBO);
	glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(glm::vec4) * graph_object.num_vertices, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec4) * graph_object.num_vertices, graph_object.position_array);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * graph_object.num_vertices, sizeof(glm::vec4) * graph_object.num_vertices, graph_object.color_array);
	vPosition = glGetAttribLocation(shaderMap["simple_color_shader"].ID, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	vColor = glGetAttribLocation(shaderMap["simple_color_shader"].ID, "vColor");
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid *)(sizeof(glm::vec4) * graph_object.num_vertices));

	graph_object.ctm_location = glGetUniformLocation(shaderMap["simple_color_shader"].ID, "ctm");

	objects.push_back(graph_object);

	return;
}

void Graphics::updateGraph(Graph graph) {
	int it, i, j;

	GraphicsObject object = objects[1];

	it = 0;
	for (i = 0; i < graph.size; i++) {
		for (j = 0; j < graph.size; j++) {
			object.position_array[it] = glm::vec4(graph.minX + graph.resX * i, graph.f[i][j], graph.minY + graph.resY * j, 1.0);
			object.position_array[it + 1] = glm::vec4(graph.minX + graph.resX * (i + 1), graph.f[i + 1][j], graph.minY + graph.resY * j, 1.0);
			object.position_array[it + 2] = glm::vec4(graph.minX + graph.resX * (i + 1), graph.f[i + 1][j + 1], graph.minY + graph.resY * (j + 1), 1.0);
			object.position_array[it + 3] = glm::vec4(graph.minX + graph.resX * i, graph.f[i][j], graph.minY + graph.resY * j, 1.0);
			object.position_array[it + 4] = glm::vec4(graph.minX + graph.resX * (i + 1), graph.f[i + 1][j + 1], graph.minY + graph.resY * (j + 1), 1.0);
			object.position_array[it + 5] = glm::vec4(graph.minX + graph.resX * i, graph.f[i][j + 1], graph.minY + graph.resY * (j + 1), 1.0);
			it += 6;
		}
	}

	glBindBuffer(GL_ARRAY_BUFFER, object.VBO);
	glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(glm::vec4) * object.num_vertices, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec4) * object.num_vertices, object.position_array);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * object.num_vertices, sizeof(glm::vec4) * object.num_vertices, object.color_array);

	return;
}

/*
Camera Movement:
0 = Forward, 1 = Left, 2 = Back, 3 = Right, 4 = Up, 5 = Down
6 = Movement Modifier
*/
void Graphics::moveCamera(int action, GLfloat modifier)
{
	switch (action) {
	case 0:
		cameraPos = cameraPos + camera_move_speed * cameraFront;
		break;
	case 1:
		cameraPos = cameraPos - camera_move_speed * glm::normalize(glm::cross(cameraFront, cameraUp));
		break;
	case 2:
		cameraPos = cameraPos - camera_move_speed * cameraFront;
		break;
	case 3:
		cameraPos = cameraPos + camera_move_speed * glm::normalize(glm::cross(cameraFront, cameraUp));
		break;
	case 4:
		cameraPos = cameraPos + camera_move_speed * cameraUp;
		break;
	case 5:
		cameraPos = cameraPos - camera_move_speed * cameraUp;
		break;
	case 6:
		camera_move_speed = modifier;
		break;
	}
	model_view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void Graphics::look(GLfloat xOffset, GLfloat yOffset)
{
	theta_xz += camera_look_speed_vertical * xOffset;
	theta_y += camera_look_speed_horizontal * yOffset;
	if (theta_xz > 360.0f) {
		theta_xz -= 360.0f;
	}
	if (theta_xz < 0.0f) {
		theta_xz += 360.0f;
	}
	if (theta_y > 179.0f) {
		theta_y = 179.0f;
	}
	if (theta_y < 1.0f) {
		theta_y = 1.0f;
	}
	cameraFront = glm::normalize(glm::vec3(glm::sin(glm::radians(theta_xz)) * glm::sin(glm::radians(theta_y)), glm::cos(glm::radians(theta_y)), glm::cos(glm::radians(theta_xz)) * glm::sin(glm::radians(theta_y))));
	model_view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}