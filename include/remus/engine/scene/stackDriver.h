#pragma once

#include <stack>
#include <vector>
#include <remus/engine/context.h>
#include <remus/engine/driver/driver.h>
#include <remus/engine/scene/scene.h>

namespace remus {
	namespace engine {
		namespace driver {

			class StackDriver : public Driver {
			public:
			
				void newState() noexcept;
				void popState() noexcept;

				virtual ~StackDriver();

			protected:
				std::stack<std::vector<scene::Scene*>> states;

			};

		}
	}
}