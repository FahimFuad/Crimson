#pragma once

#include "Scene.h"
#include "Entity.h"

#include "Utils/tinyxml2.h"

namespace Crimson {
	class SceneSerialiser {
	private:
		Scene& m_scene;

		Entity ParseEntity(tinyxml2::XMLElement* node);
		void ParseEntities(tinyxml2::XMLElement* node, Entity parent=Entity());
	public:
		SceneSerialiser(Scene& scene);

		std::string SerialiseString();

		std::string SerialiseText(const std::string& filePath);
		void SerialiseBinary(const std::string& filePath);

		bool DeserialiseText(const std::string& text);
		bool DeserialiseBinary(const std::string& text);
	};
}
