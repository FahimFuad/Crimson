#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Crimson {
	struct Transform {
		glm::vec3 position;
		glm::vec3 scale;
		glm::quat rotation;

		inline glm::mat4 GetModel() const {
			glm::mat4 positionMatrix = glm::translate(glm::mat4(1.0f), position);
			glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);
			glm::mat4 rotationMatrix = glm::toMat4(rotation);

			return positionMatrix * rotationMatrix * scaleMatrix;
		}
	};
}
