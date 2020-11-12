#pragma once

#include <map>
#include <string>

#include "Renderer/Surface.h"

#include "Renderer/Renderer3D/Mesh.h"
#include "Renderer/Material.h"

namespace Crimson {
	class AssetManager {
	private:
		std::map<std::string, std::string> m_textFiles;
		std::map<std::string, Surface> m_textures;
		std::map<std::string, Mesh*> m_meshes;
		std::map<std::string, Material*> m_materials;

		bool m_loadFromArchive;
	public:
		AssetManager(bool loadFromArchive);
		Surface* LoadSurface(const std::string& filePath, bool reload=false);
		std::string LoadText(const std::string& filePath, bool reload=false);
		Mesh* LoadMesh(const std::string& filePath);
		Material* LoadMaterial(const std::string& filePath);
		~AssetManager();

		std::vector<std::pair<std::string, std::string>> GetFilesFromDir(const std::string& dir);
	};
}
