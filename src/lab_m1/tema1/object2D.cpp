#include "object2D.h"


Mesh* object2D::CreateSquare(
	const std::string& name,
	glm::vec3 centerPoint,
	float length,
	glm::vec3 color,
	bool fill)
{
	float offset = length / 2;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(centerPoint + glm::vec3(offset, offset, 0), color),
		VertexFormat(centerPoint + glm::vec3(-offset, offset, 0), color),
		VertexFormat(centerPoint + glm::vec3(-offset, -offset, 0), color),
		VertexFormat(centerPoint + glm::vec3(offset, -offset, 0), color)
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned int> indices = { 0, 1, 2, 3 };

	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// Draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	square->InitFromData(vertices, indices);
	return square;
}


Mesh* object2D::CreateCircle(
	const std::string& name,
	glm::vec3 centerPoint,
	float radius,
	int noPoints,
	glm::vec3 color,
	bool fill)
{
	std::vector<VertexFormat> vertices;
	std::vector<unsigned int> indices;
	glm::vec3 norm = glm::vec3(0.2, 0.8, 0.6);

	// Insert center point of circle
	vertices.push_back(VertexFormat(centerPoint, color, norm));

	// Generate the rest of the points
	for (int i = 1; i <= noPoints + 1; i++)
	{
		float x, y;

		x = radius * cos(i * 2 * M_PI / noPoints);
		y = radius * sin(i * 2 * M_PI / noPoints);

		vertices.push_back(VertexFormat(glm::vec3(x, y, centerPoint.z), color, norm));
	}

	// Generate indices
	for (int i = 0; i < vertices.size(); i++)
		indices.push_back(i);

	// Create mesh
	Mesh* circle = new Mesh(name);
	circle->InitFromData(vertices, indices);
	circle->SetDrawMode(GL_TRIANGLE_FAN);

	return circle;
}
