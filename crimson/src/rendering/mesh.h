#pragma once

#include <vector>

#include "core.h"
#include "renderdata.h"

namespace Crimson {
	class CR_API Mesh {
	private:
		unsigned int m_va, m_vb, m_ib;

		std::vector<Vertex> m_vertices;
		std::vector<unsigned int> m_indices;
	public:
		Mesh(const std::vector<Vertex>& vertices, 
				const std::vector<unsigned int>& indices);
		
		virtual ~Mesh();

		void LoadFromData(const std::vector<Vertex>& vertices,
				const std::vector<unsigned int>& indices);
		
		void Draw();
	};
}
