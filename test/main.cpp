#include "main.h"

int main() {
	srand(time(NULL));

	remus::logger::initLogger("./");
	remus::logger::logNotice("Starting remus test environment...");

	// Create framework
	auto window = new remus::engine::Window(Settings::width, Settings::height, Settings::width, Settings::height, Settings::title, Settings::fullscreen);
	auto runtime = new remus::engine::Runtime(window);
	
	// Setup window
	window->setMouseInputBound();

	auto context = window->context();
	context->setClearColor(0, 0, 0, 1.0);
	context->setClearModeColor(true);
	context->setDepthTest(true);
	context->setClearModeDepth(true);
	context->setFaceCulling(true);

	// Load resources
	loadResources(runtime->getCache());

	// Setup driver
	auto driver = new TestDriver(window, runtime->getCache());

	// Start
	runtime->run(driver);

	// Clean up
	delete driver;
	delete runtime;
	delete window;
	return 0;
}

void loadResources(remus::engine::Cache* cache) {
	remus::logger::logNotice("Loading resources");
	cache->loadShaderVertex("test_shader_vert", "./resources/testShader.vert");
	cache->loadShaderFragment("test_shader_frag", "./resources/testShader.frag");
	cache->loadShaderProgram("test_shader", {"test_shader_vert", "test_shader_frag"});

	// Floor
	cache->loadModel("floor", "./resources/floor.glb", false, true);
	cache->loadTexture2D("floor_texture", "./resources/FloorTexture.png", false);
	cache->loadTexture2D("floor_specular", "./resources/FloorSpecular.png", false);
	cache->createMaterial("floor_material", "floor_texture", "floor_specular", 32.0);

	// Cube
	cache->loadModel("cube", "./resources/cube.glb", false, true);
	cache->loadTexture2D("cube_texture", "./resources/CubeTexture.png", true);
	cache->loadTexture2D("cube_specular", "./resources/CubeSpecular.png", false);
	cache->createMaterial("cube_material", "cube_texture", "cube_specular", 8.0);
}