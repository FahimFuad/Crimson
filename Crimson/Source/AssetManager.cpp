#include "AssetManager.h"

#include "Logger.h"

#include <physfs.h>
#include <tuple>
#include <filesystem>
#include <algorithm>

#include "Utils/stb_image.h"

#include "DefaultAssets/GridTexture.h"
#include "DefaultAssets/StandardShader.h"
#include "DefaultAssets/ParticleShader.h"

namespace Crimson {
	AssetManager::AssetManager(bool loadFromArchive, const std::string& workingDir) :
	 	m_workingDir(workingDir), m_loadFromArchive(loadFromArchive) {
		if (loadFromArchive) {
			PHYSFS_init(NULL);
			PHYSFS_mount("Data.pck", "/", 1);

			// Replace all \\ in the working directory with /, so that it works on windows as well
			std::replace(m_workingDir.begin(), m_workingDir.end(), '\\', '/');

			if (!m_workingDir.empty()) {
				if (m_workingDir.back() != '/') {
					m_workingDir += '/';
				}
			}
		}

		m_meshes["Cube"] = new Mesh(
			std::vector<Vertex> {
				{glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.625, 0.500)},
				{glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.875, 0.500)},
				{glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.875, 0.750)},
				{glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.625, 0.500)},
				{glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.875, 0.750)},
				{glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.625, 0.750)},
				{glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.375, 0.750)},
				{glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.625, 0.750)},
				{glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.625, 1.0f)},
				{glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.375, 0.750)},
				{glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.625, 1.0f)},
				{glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.375, 1.0f)},
				{glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.375, 0.0f)},
				{glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.625, 0.0f)},
				{glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.625, 0.250)},
				{glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.375, 0.0f)},
				{glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.625, 0.250)},
				{glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.375, 0.250)},
				{glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.125, 0.500)},
				{glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.375, 0.500)},
				{glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.375, 0.750)},
				{glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.125, 0.500)},
				{glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.375, 0.750)},
				{glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.125, 0.750)},
				{glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.375, 0.500)},
				{glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.625, 0.500)},
				{glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.625, 0.750)},
				{glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.375, 0.500)},
				{glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.625, 0.750)},
				{glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.375, 0.750)},
				{glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.375, 0.250)},
				{glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.625, 0.250)},
				{glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.625, 0.500)},
				{glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.375, 0.250)},
				{glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.625, 0.500)},
				{glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.375, 0.500)},
			},
			std::vector<unsigned int> {
				0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
			}
		);

		m_textures["Default"] = Surface{1023,1007,3,GridTexture};

		m_textFiles["Standard"] = StandardShader;
		m_textFiles["Particle"] = ParticleShader;

		m_materials["Default"] = new Material(
			R"(
				shader = "Standard"

				albedo = "Default"

				material = {
				    color = {1, 1, 1},
					 smoothness = 1,
					 shininess = 20
				}

			)", *this);
	}

	AssetManager::~AssetManager() {
		for (auto& surface : m_textures) {
			if (surface.first != "Default") {
				stbi_image_free(surface.second.pixels);
			}
		}

		for (auto& m : m_meshes) {
			delete m.second;
		}

		for (auto& m : m_materials) {
			delete m.second;
		}

		if (m_loadFromArchive) {
			PHYSFS_unmount("data.pck");
			PHYSFS_deinit();
		}
	}

	static std::string GetExtension(const std::string& fname) {
		auto idx = fname.rfind('.');
		std::string extension;

		if(idx != std::string::npos) {
			extension = fname.substr(idx+1);
		}

		return "." + extension;
	}

	static std::vector<std::pair<std::string, std::string>> GetDirReleaseMode(const std::string& dir) {
		std::vector<std::pair<std::string, std::string>> result;

		char **rc = PHYSFS_enumerateFiles(dir.c_str());
		char **i;
		for (i = rc; *i != NULL; i++) {
			PHYSFS_Stat stat;
			std::string fname = dir + "/" + *i;
			PHYSFS_stat(fname.c_str(), &stat);

			std::pair<std::string, std::string> currentEntry;

			if (stat.filetype == PHYSFS_FILETYPE_DIRECTORY) {
				auto a = result;
				auto b = GetDirReleaseMode(fname);
				a.insert(a.end(), b.begin(), b.end());
				result = a;
			} else {
				currentEntry.first = fname;
				currentEntry.second = GetExtension(fname);
				result.push_back(currentEntry);
			}

		}
		PHYSFS_freeList(rc);

		return result;
	}

	Surface* AssetManager::LoadSurface(const std::string& f, bool reload) {
		std::string filePath = f;
		if (f != "Default") {
			filePath = m_workingDir + f;
		}

		if (m_textures.count(filePath) == 0 && !reload) {
			unsigned char* imageData;
			size_t fileSize;

			if (m_loadFromArchive) {
				PHYSFS_file* file = PHYSFS_openRead(filePath.c_str());
				if (file == NULL) {
					CR_LOG_ERROR("Failed to load file: %s.\n", filePath.c_str());
					return NULL;
				}

				fileSize = PHYSFS_fileLength(file);

				imageData = (unsigned char*)malloc(fileSize);
				size_t bytesRead = PHYSFS_readBytes(file, imageData, fileSize);

				PHYSFS_close(file);
			} else {
				FILE* file = fopen(filePath.c_str(), "rb");
				if (file == NULL) {
					CR_LOG_ERROR("Failed to load file: %s.\n", filePath.c_str());
					return NULL;
				}

				fseek(file, 0L, SEEK_END);
				fileSize = ftell(file);
				rewind(file);

				imageData = (unsigned char*)malloc(fileSize);

				size_t bytesRead = fread(imageData, sizeof(char), fileSize, file);

				fclose(file);
			}

			int x,y;
			int n = 4;
			unsigned char* pixels = stbi_load_from_memory(imageData, fileSize, &x, &y, &n, 0);
			if (pixels == NULL) {
				CR_LOG_ERROR("Failed to load file: %s. Reason for failure: %s\n", filePath.c_str(), stbi_failure_reason());
				return NULL;
			}

			m_textures[filePath] = Surface{x,y,n,pixels};
		}

		return &m_textures[filePath];
	}

	std::string AssetManager::LoadText(const std::string& f, bool reload, bool useWorkingDir) {
		std::string filePath = f;
		if (f != "Standard" && f != "Particle" && useWorkingDir) {
			filePath = m_workingDir + f;
		}

		if (m_textFiles.count(filePath) == 0 && !reload) {
			char* buffer;

			if (m_loadFromArchive) {
				PHYSFS_file* file = PHYSFS_openRead(filePath.c_str());
				if (file == NULL) {
					CR_LOG_ERROR("Failed to load file: %s.\n", filePath.c_str());
					return "";
				}

				size_t fileSize = PHYSFS_fileLength(file);

				buffer = (char*)malloc(fileSize + 1);
				size_t bytesRead = PHYSFS_readBytes(file, buffer, fileSize);

				buffer[bytesRead] = '\0';

				PHYSFS_close(file);
			} else {
				FILE* file = fopen(filePath.c_str(), "r");
				if (file == NULL) {
					CR_LOG_ERROR("Failed to load file: %s.\n", filePath.c_str());
					return "";
				}

				fseek(file, 0L, SEEK_END);
				size_t fileSize = ftell(file);
				rewind(file);

				buffer = (char*)malloc(fileSize + 1);

				size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);

				buffer[bytesRead] = '\0';

				fclose(file);
			}

			m_textFiles[filePath] = buffer;
			free(buffer);
		}
		return m_textFiles[filePath];
	}

	Mesh* AssetManager::LoadMesh(const std::string& f) {
		if (m_meshes.count(f) == 0) {
			m_meshes[f] = new Mesh(LoadText(f).c_str());
		}
		return m_meshes[f];
	}

	Material* AssetManager::LoadMaterial(const std::string& f) {
		if (m_materials.count(f) == 0) {
			m_materials[f] = new Material(LoadText(f).c_str(), *this);
		}
		return m_materials[f];
	}

	std::vector<std::pair<std::string, std::string>> AssetManager::GetFilesFromDir(const std::string& d) {
		std::string dir = m_workingDir + d;

		std::vector<std::pair<std::string, std::string>> result;

		if (m_loadFromArchive) {
			result = GetDirReleaseMode(dir);
		} else {
			std::string path = dir;
			for (const auto& entry : std::filesystem::recursive_directory_iterator(path)) {
				if (!entry.is_directory()) {
					result.push_back({entry.path().string(), entry.path().extension().string()});
				}
			}
		}

		return result;
	}

}
