#include "main.h"

int main() {
	srand(time(NULL));

	remus::logger::initLogger("./");
	remus::logger::logNotice("Starting remus test environment...");

	// Create framework
	auto window = new remus::engine::Window(Settings::width, Settings::height, Settings::title, Settings::fullscreen);
	auto runtime = new remus::engine::Runtime(window);
	
	// Setup window
	window->attach();
	window->setClearColor(0, 0, 0, 1.0);
	window->setGlDepthTest(true);
	window->setMSAA(4);
	window->setFaceCulling(true);
	window->setMouseInputBound();

	// Load resources
	loadResources(runtime->getContext());

	// Setup driver
	auto driver = new TestDriver(window, runtime->getContext());

	// Start
	runtime->run(driver);

	// Clean up
	delete driver;
	delete runtime;
	delete window;
	return 0;
}

void loadResources(remus::engine::Context* context) {
	remus::logger::logNotice("Loading resources");
	context->loadShaderVertex("test_shader_vert", "./resources/testShader.vert");
	context->loadShaderFragment("test_shader_frag", "./resources/testShader.frag");
	context->loadShaderProgram("test_shader", {"test_shader_vert", "test_shader_frag"});

	// Floor
	context->loadModel("floor", "./resources/floor.glb", false, true);
	context->loadTexture2D("floor_texture", "./resources/FloorTexture.png", false);
	context->loadTexture2D("floor_specular", "./resources/FloorSpecular.png", false);
	context->createMaterial("floor_material", "floor_texture", "floor_specular", 32.0);

	// Cube
	context->loadModel("cube", "./resources/cube.glb", false, true);
	context->loadTexture2D("cube_texture", "./resources/CubeTexture.png", true);
	context->loadTexture2D("cube_specular", "./resources/CubeSpecular.png", false);
	context->createMaterial("cube_material", "cube_texture", "cube_specular", 8.0);
}