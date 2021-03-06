#include "Material.h"

#include <string>
#include <vector>
#include <tuple>
#include <sstream>

extern "C" {
	#include <lua.h>
	#include <lauxlib.h>
	#include <lualib.h>
}

#include "Logger.h"
#include "AssetManager.h"

bool CheckLua(lua_State* L, int r) {
	if (r != LUA_OK) {
		CR_LOG_ERROR("Error loading material: %s", lua_tostring(L, -1));
		return false;
	}
	return true;
}

namespace Crimson {
	Material::Material(const std::string& config, AssetManager& assetManager) {
		Load(config, assetManager);
	}

	void Material::Load(const std::string& config, AssetManager& assetManager) {
		lua_State* L;

		L = luaL_newstate();

		if (!CheckLua(L, luaL_dostring(L, config.c_str()))) {
			goto end;
		}

		lua_getglobal(L, "shader");
		if (lua_isstring(L, -1)) {
			m_shader = std::make_shared<Shader>(assetManager.LoadText(lua_tostring(L, -1)));
		} else {
			CR_LOG_FATAL_ERROR("Unable to load shader for material: %s", lua_tostring(L, -1));
			goto end;
		}
		lua_pop(L, 1);

		lua_getglobal(L, "albedo");
		if (lua_isstring(L, -1)) {
			auto surface = assetManager.LoadSurface(lua_tostring(L, -1));

			if (surface) {
				m_albedo = std::make_shared<Texture>(surface);
			} else {
				m_albedo = std::make_shared<Texture>(assetManager.LoadSurface("Default"));
			}
		}
		lua_pop(L, 1);

		m_shader->Bind();

		lua_getglobal(L, "material");
		if (!lua_istable(L, -1)) {goto end;};

		lua_pushnil(L);
		while (lua_next(L, -2) != 0) {
			if (lua_isnumber(L, -1)) {
				m_shader->SetFloat("u_material." + std::string(lua_tostring(L, -2)), lua_tonumber(L, -1));
			} else if (lua_istable(L, -1)) {
				int size = lua_rawlen(L, -1);

				if (size == 2) {
					lua_pushnil(L);
					glm::vec2 v;

					lua_rawgeti(L, -1, 1);
					if (lua_isnumber(L, -1)) {
						v.x = lua_tonumber(L, -1);
					}
					lua_pop(L, 1);

					lua_rawgeti(L, -1, 2);
					if (lua_isnumber(L, -1)) {
						v.y = lua_tonumber(L, -1);
					}
					lua_pop(L, 1);

					lua_pop(L, 1);

					m_shader->SetVec2("u_material." + std::string(lua_tostring(L, -2)), v);
				} else if (size == 3) {
					lua_pushnil(L);
					glm::vec3 v;

					lua_rawgeti(L, -1, 1);
					if (lua_isnumber(L, -1)) {
						v.x = lua_tonumber(L, -1);
					}
					lua_pop(L, 1);

					lua_rawgeti(L, -1, 2);
					if (lua_isnumber(L, -1)) {
						v.y = lua_tonumber(L, -1);
					}
					lua_pop(L, 1);

					lua_rawgeti(L, -1, 3);
					if (lua_isnumber(L, -1)) {
						v.z = lua_tonumber(L, -1);
					}
					lua_pop(L, 1);

					lua_pop(L, 1);

					m_shader->SetVec3("u_material." + std::string(lua_tostring(L, -2)), v);
				} else if (size == 4) {
					lua_pushnil(L);
					glm::vec4 v;

					lua_rawgeti(L, -1, 1);
					if (lua_isnumber(L, -1)) {
						v.x = lua_tonumber(L, -1);
					}
					lua_pop(L, 1);

					lua_rawgeti(L, -1, 2);
					if (lua_isnumber(L, -1)) {
						v.y = lua_tonumber(L, -1);
					}
					lua_pop(L, 1);

					lua_rawgeti(L, -1, 3);
					if (lua_isnumber(L, -1)) {
						v.z = lua_tonumber(L, -1);
					}
					lua_pop(L, 1);

					lua_rawgeti(L, -1, 3);
					if (lua_isnumber(L, -1)) {
						v.w = lua_tonumber(L, -1);
					}
					lua_pop(L, 1);

					lua_pop(L, 1);

					m_shader->SetVec3("u_material." + std::string(lua_tostring(L, -2)), v);
				} else if (size > 4) {
					CR_LOG_ERROR("%s", "Vectors of size 5+ are not supported");
				} else if (size == 1) {
					CR_LOG_ERROR("%s", "Vectors of size 1 are not supported, use number instead");
				}
			} else {
				CR_LOG_ERROR("Type \"%s\" isn't supported for materials", lua_typename(L, lua_type(L, -1)));
			}

			lua_pop(L, 1);
		}

		end:
			lua_close(L);
	}


	void Material::SetFloat(const std::string& name, float value) {
		m_shader->SetFloat(name, value);
	}

	void Material::SetInt(const std::string& name, int value) {
		m_shader->SetInt(name, value);
	}

	void Material::SetVec2(const std::string& name, glm::vec2 value) {
		m_shader->SetVec2(name, value);
	}

	void Material::SetVec3(const std::string& name, glm::vec3 value) {
		m_shader->SetVec3(name, value);
	}

	void Material::SetVec4(const std::string& name, glm::vec4 value) {
		m_shader->SetVec4(name, value);
	}

	void Material::SetMat4(const std::string& name, glm::mat4 value) {
		m_shader->SetMat4(name, value);
	}

	void Material::Bind(unsigned int unit) {
		if (m_albedo) {
			m_albedo->Bind(unit);
		}
	}

	Material::~Material() {
	}
}
