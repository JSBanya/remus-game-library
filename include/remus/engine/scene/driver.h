#pragma once

#include <vector>
#include <algorithm>
#include <remus/engine/cache.h>
#include <remus/engine/scene/scene.h>
#include <remus/gfx/shaders/shaderProgram.h>

namespace remus {
	namespace engine {
		namespace scene {

			class Driver {
			public:
				Driver(Cache* cache);

				virtual void addScene(Scene* s) noexcept;
				virtual void removeScene(Scene* s) noexcept;
				virtual void clearScenes() noexcept;
				virtual std::vector<Scene*> getActiveScenes() noexcept;

				virtual void tick(GLint num);
				virtual void render(GLfloat time, GLfloat delta);

				virtual gfx::shaders::ShaderProgram* getPostProcessor() noexcept; // No-multisampling post processing
				virtual gfx::shaders::ShaderProgram* getPostProcessorMS() noexcept; // Multisampling post processing

				virtual ~Driver();

			protected:
				Cache* cache;
				std::vector<Scene*> activeScenes;

			};

		}
	}
}