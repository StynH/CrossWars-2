#include "ModelManager.h"
#include "Defines.h"
#include <GLEW/glew.h>


ModelManager::ModelManager()
{
}


ModelManager::~ModelManager()
{
}

ModelData* ModelManager::loadModelToVao(std::vector<GLfloat> t_vertex_positions, std::vector<GLint> t_indices)
{
	GLuint id = createVao();
	bindIndices(t_indices);
	storeData(0, 3, t_vertex_positions);
	unbindVao();

	return new ModelData(id, t_indices.size());
}

GLuint ModelManager::createVao()
{
	GLuint vaoID;
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);

	m_vao_vector.push_back(vaoID);

	return vaoID;
}

void ModelManager::storeData(int t_attribute_num, int t_coord_size, std::vector<GLfloat> t_data)
{
	GLuint vboID;
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, t_data.size() * sizeof(GLfloat), &t_data.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(t_attribute_num, t_coord_size, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	m_vbo_vector.push_back(vboID);

	//Unbinding
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ModelManager::bindIndices(std::vector<GLint> t_indices)
{
	GLuint vboID;
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, t_indices.size() * sizeof(GLint), &t_indices.front(), GL_STATIC_DRAW);

	m_vbo_vector.push_back(vboID);
}

void ModelManager::unbindVao()
{
	glBindVertexArray(0);
}


void ModelManager::cleanUp()
{
	for(auto id : m_vao_vector)
	{
		glDeleteVertexArrays(1, &id);
	}

	for (auto id : m_vbo_vector)
	{
		glDeleteBuffers(1, &id);
	}
}
