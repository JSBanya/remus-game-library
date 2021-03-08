#pragma once

#include <vector>
#include <algorithm>
#include <remus/engine/context.h>
#include <remus/engine/scene/scene.h>

namespace remus {
	namespace engine {
		namespace scene {

			class Driver {
			public:
				Driver(Context* context = nullptr);

				virtual void addScene(Scene* s) noexcept;
				virtual void removeScene(Scene* s) noexcept;
				virtual void clearScenes() noexcept;

				virtual void tick(GLint num);
				virtual void render(GLfloat time, GLfloat delta);
				virtual void draw();

				virtual ~Driver();

			protected:
				Context* context;
				std::vector<Scene*> activeScenes;

			};

		}
	}
}