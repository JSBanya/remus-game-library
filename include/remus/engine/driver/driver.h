#pragma once

#include <vector>
#include <algorithm>
#include <remus/engine/context.h>
#include <remus/engine/scene/scene.h>

namespace remus {
	namespace engine {
		namespace driver {

			class Driver {
			public:
				Driver();
				Driver(Context* c);

				virtual void addScene(scene::Scene* s) noexcept;
				virtual void removeScene(scene::Scene* s) noexcept;
				virtual void clearScenes() noexcept;

				virtual void tick(GLint num);
				virtual void render(GLfloat time, GLfloat delta);

				void setContext(Context* c);

				virtual ~Driver();

			protected:
				Context* context;
				std::vector<scene::Scene*> activeScenes;

			};

		}
	}
}