#pragma once

#include <reactphysics3d/reactphysics3d.h>

namespace rp3d = ::reactphysics3d;

namespace Crimson {
	class PhysicsScene;

	class EventListener : public rp3d::EventListener {
	private:
		PhysicsScene* m_physicsScene;
	public:
		EventListener(PhysicsScene* physicsScene);

		void onContact(const rp3d::CollisionCallback::CallbackData& callbackData) override;
	};
}
