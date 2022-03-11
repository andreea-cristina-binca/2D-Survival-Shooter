#pragma once

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"
#include "core/engine.h"

#include <string>
#include <vector>


namespace object2D
{

	// Create square with given bottom left corner, length and color
	Mesh* CreateSquare(const std::string& name, glm::vec3 centerPoint, float length, glm::vec3 color, bool fill = false);
	Mesh* CreateCircle(const std::string& name, glm::vec3 centerPoint, float radius, int noPoints, glm::vec3 color, bool fill = false);

}
