#include <remus/engine/render/forward.h>

namespace remus {
	namespace engine {
		namespace render {

			Forward::Forward(GLint width, GLint height, GLint multisample) : Pipeline(width, height, multisample) {
				this->openGLContext.setClearColor(0, 0, 0, 1.0);
				this->openGLContext.setClearModeColor(true);
				this->openGLContext.setDepthTest(true);
				this->openGLContext.setClearModeDepth(true);
				this->openGLContext.setFaceCulling(true);
				this->openGLContext.apply();

				Logger::logNotice("Using forward renderer.");
			}

			void Forward::draw(scene::Driver* driver) {
				this->fbo.bind();
				this->openGLContext.setViewport(this->width, this->height);
				this->openGLContext.doClear();

				for(auto scene : driver->getActiveScenes()) {
					auto camera = scene->getCamera();
					auto ambient = scene->getAmbient();
					auto pointLights = scene->getPointLights();
					auto directionalLights = scene->getDirectionalLights();
					auto spotLights = scene->getSpotLights();

					// Render opaque entities
					for(auto e : scene->getOpaqueEntities()) {
						this->renderEntity(e, camera, ambient, pointLights, directionalLights, spotLights);
					}

					// Render transparent entities
					for(auto e : scene->getTransparentEntities()) {
						this->renderEntity(e, camera, ambient, pointLights, directionalLights, spotLights);
					}
				}

				this->fbo.unbind();
			}

			void Forward::renderEntity(
				gfx::entity::Entity* e, 
				gfx::view::Camera* camera,
				glm::vec3 ambient,
				gfx::lighting::PointLights* pointLights, 
				gfx::lighting::DirectionalLights* directionalLights,
				gfx::lighting::SpotLights* spotLights
			) {
				if(e->numInstances() == 0)
					return;
				
				auto shader = e->getShader();

				shader->bind();

				// Bind entity instances
				e->bindInstanceData(0);

				// Bind camera uniforms
				shader->setUniform("viewMatrix", camera->getViewMatrix());
				shader->setUniform("projectionMatrix", camera->getProjection());
				shader->setUniform("cameraPosition", camera->getPos());

				// Apply entity uniforms
				e->applyUniforms();

				// Apply lights
				shader->setUniform("ambient", ambient);
				pointLights->bind(1);
				directionalLights->bind(2);
				spotLights->bind(3);

				// Draw model mesh-by-mesh
				auto model = e->getModel();
				auto materials = e->getMaterials();
				for(auto &mesh : model->getMeshes()) {
					auto meshName = mesh.first;
					auto meshObj = mesh.second;

					bool hasMaterial = (materials.count(meshName) != 0);
					if(hasMaterial) {
						materials[meshName]->bind(shader);
					}
					
					meshObj->drawTrianglesInstanced(e->numInstances());

					if(hasMaterial) {
						materials[meshName]->unbind();
					}
				}

				shader->unbind();
			}

		}
	}
}