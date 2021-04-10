#include "main.h"

int main() {
	srand(time(NULL));

	Logger::init("./");
	Logger::logNotice("Starting remus test environment...");

	// Create framework
	engine::Window window(Settings::width, Settings::height, Settings::title, Settings::fullscreen);
	window.setMouseInputBound();
	
	engine::Runtime runtime;
	
	// Load resources
	engine::Cache cache;
	loadResources(&cache);

	// Setup driver
	TestDriver driver(&window, &cache);

	// Enable GL debug messages
	Logger::enableGLDebug();

	// Start
	engine::render::Forward forwardRendering(Settings::width, Settings::height, Settings::multisampling);
	runtime.run(&window, &driver, &forwardRendering);

	// Clean up
	Logger::close();
	return 0;
}

void loadResources(engine::Cache* cache) {
	Logger::logNotice("Loading resources");

	// Test shader
	cache->loadShaderVertex("test_shader_vert", "./resources/testShader.vert");
	cache->loadShaderFragment("test_shader_frag", "./resources/testShader.frag");
	cache->loadShaderProgram("test_shader", {"test_shader_vert", "test_shader_frag"});

	// Postprocessing shader
	cache->loadShaderVertex("postprocessing_vert", "./resources/postprocessing.vert");
	cache->loadShaderFragment("postprocessing_frag", "./resources/postprocessing.frag");
	cache->loadShaderFragment("postprocessing_ms_frag", "./resources/postprocessing_ms.frag");
	cache->loadShaderProgram("postprocessing", {"postprocessing_vert", "postprocessing_frag"});
	cache->loadShaderProgram("postprocessing_ms", {"postprocessing_vert", "postprocessing_ms_frag"});

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