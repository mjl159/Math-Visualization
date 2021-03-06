#ifndef ___GRAPHICSOBJECT_H___
#define ___GRAPHICSOBJECT_H___

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

class GraphicsObject
{
public:
	int ID;
	int type;
	GLuint VAO;
	GLuint VBO;
	int num_vertices;
	glm::vec3 position = { 0.0, 0.0, 0.0 };
	glm::vec4* position_array;
	glm::vec4* color_array;
	glm::vec2* texture_array;
	GLuint ctm_location;
	glm::mat4 ctm = { { 1.0, 0.0, 0.0, 0.0 },{ 0.0, 1.0, 0.0, 0.0 },{ 0.0, 0.0, 1.0, 0.0 },{ 0.0, 0.0, 0.0, 1.0 } };
	GLuint selected_location;
	int selected = 1;
private:

};

#endif