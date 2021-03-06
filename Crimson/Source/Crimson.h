#pragma once

#include <imgui.h>

#include "Logger.h"
#include "AssetManager.h"
#include "Layer.h"
#include "Transform.h"
#include "Input.h"

// Rendering
#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "Renderer/Material.h"
#include "Renderer/Renderer3D/Mesh.h"
#include "Renderer/Renderer3D/Camera.h"
#include "Renderer/Renderer3D/LightScene.h"
#include "Renderer/RenderTarget.h"
#include "Renderer/ParticleSystem/Particle.h"
#include "Renderer/ParticleSystem/ParticleSystem.h"

// Physics
#include "Physics/PhysicsScene.h"
#include "Physics/Rigidbody.h"

// Scripting
#include "Scripting/ScriptManager.h"
#include "Scripting/Linter.h"

// UI
#include "UI/UIElement.h"
#include "UI/UIManager.h"

// ImGui
#include "ImGuiImpl/ImGuizmo.h"

// Scene management
#include "SceneManagement/Scene.h"
#include "SceneManagement/Components.h"
#include "SceneManagement/Entity.h"
#include "SceneManagement/SceneSerialiser.h"

// Utils
#include "Utils/MeshConverter.h"
#include "Utils/FolderCompressor.h"
#include "GUID.h"
#include "Utils/ProjectConfig.h"


#include "Game.h"
