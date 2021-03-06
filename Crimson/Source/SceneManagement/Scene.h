#pragma once

#include <entt.hpp>

#include "Renderer/Renderer.h"
#include "Renderer/Renderer3D/LightScene.h"
#include "Renderer/Renderer3D/Skybox.h"
#include "Physics/PhysicsScene.h"
#include "AssetManager.h"
#include "Scripting/ScriptManager.h"

#include "GUID.h"

#include <reactphysics3d/reactphysics3d.h>

#include <future>

namespace rp3d = ::reactphysics3d;

namespace Crimson {

	class Entity;
	class RenderTarget;
	struct MeshFilterComponent;

	typedef entt::entity EntityHandle;

	struct SceneConfig {
		std::string name{"Untitled Scene"};

		glm::vec3 clearColor = glm::vec3(0.0f, 0.0f, 0.0f);

		bool useSkybox{false};

		std::string skyboxPosX{"Default"};
		std::string skyboxNegX{"Default"};
		std::string skyboxPosY{"Default"};
		std::string skyboxNegY{"Default"};
		std::string skyboxPosZ{"Default"};
		std::string skyboxNegZ{"Default"};
	};

	class Scene {
	private:
		entt::registry m_registry;

		friend class Entity;
		friend class SceneSerialiser;

		Camera* GetMainCamera();

		void ApplyLighting();
		void RenderShadows(Camera* mainCamera);
		void RenderMeshes(Camera* mainCamera, float delta);

		void PhysicsComponentCreate(entt::registry& r, entt::entity ent);
		void ScriptComponentCreate(entt::registry& r, entt::entity ent);
		void ScriptComponentDestroy(entt::registry& r, entt::entity ent);

		SceneConfig m_config;

		std::shared_ptr<Skybox> m_skybox;

		std::vector<std::future<void>> m_meshFutures;
		std::vector<std::future<void>> m_materialFutures;

	public:
		bool m_isUpdating{false};

		AssetManager m_assetManager;
		Scene(bool release);
		~Scene();

		std::shared_ptr<LightScene> m_lightScene;
		std::shared_ptr<PhysicsScene> m_physicsScene;
		std::shared_ptr<ScriptManager> m_scriptManager;

		template <class T>
		std::vector<Entity> GetEntitiesWithComponent() {
			std::vector<Entity> result;

			auto view = m_registry.view<T>();
			for (auto ent : view) {
				result.emplace_back(ent, this);
			}

			return result;
		}

		Entity CreateEntity(const std::string& name = "Unnamed Entity", const std::string& tag = "Default", const GUID& guid="");
		void DestroyEntity(Entity ent);
		Entity GetEntityByGUID(const GUID& guid);

		void LoadSkybox();
		void LoadScripts();
		void LoadMeshes();
		void LoadMaterials();

		// Events
		void Init();
		void Update(float delta);
		void PhysicsUpdate(float delta);
		void UpdateTransforms();
		void Render(RenderTarget& renderTarget, float delta);
		void Render(RenderTarget& renderTarget, Camera* camera, float delta);
		void DrawWireframe(Entity ent);
		void Render(float delta);
		void ContactStay(rp3d::CollisionBody* body, rp3d::CollisionBody* other);
		void ContactEnter(rp3d::CollisionBody* body, rp3d::CollisionBody* other);
		void ContactExit(rp3d::CollisionBody* body, rp3d::CollisionBody* other);

		float GetScriptEngineUpdateTime();
		unsigned int GetScriptEngineMemoryUsage();
		float GetPhysicsEngineUpdateTime();

		void UpdateViewport(std::pair<int, int> size);

		inline PhysicsScene* GetPhysicsScene() {
			return &*m_physicsScene;
		}

		inline SceneConfig& GetConfig() {return m_config;}
	};

}
