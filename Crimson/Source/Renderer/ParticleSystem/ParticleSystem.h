#pragma once

#include <memory>
#include <vector>

#include "Particle.h"

#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "Renderer/Renderer3D/Camera.h"

namespace Crimson {
	class ParticleSystem {
	private:
		unsigned int m_quadVA;
		unsigned int m_quadVB;

		std::shared_ptr<Shader> m_shader;

		std::vector<Particle> m_particles;
	public:
		int m_maxParticles{100};
		glm::vec3 m_position;
		int m_rateOverTime;
		float m_gravity{0.5f};
		float m_randomVelocityMin{0.0f};
		float m_randomVelocityMax{1.0f};
		float m_randomLifetimeMin{0.5f};
		float m_randomLifetimeMax{1.0f};
		float m_sizeOverLifetime{0.0f};
		float m_startSize{1.0f};

		ParticleSystem(const glm::vec3& position);

		void Update(float delta);
		void Draw(Camera& camera, const std::shared_ptr<Shader>& shader = NULL);
	};
}
