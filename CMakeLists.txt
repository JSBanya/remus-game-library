cmake_minimum_required(VERSION 3.9)

project(remus VERSION 0.0.1 DESCRIPTION "Remus game library" LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(OpenGL_GL_PREFERENCE GLVND)

include(GNUInstallDirs)

find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)
find_package(Freetype REQUIRED)
find_package(glfw3 REQUIRED)
find_package(assimp REQUIRED)

add_library(remus STATIC
	src/engine/runtime.cpp
	src/engine/window.cpp
	src/engine/context.cpp
	src/engine/context_defaults.cpp

	src/engine/scene/driver.cpp
	src/engine/scene/stackDriver.cpp
	src/engine/scene/scene.cpp

	src/utils/mouse.cpp
	src/utils/keyboard.cpp

	src/gfx/entity/entity.cpp

    src/gfx/view/camera.cpp
	src/gfx/view/orthographicCamera.cpp
	src/gfx/view/perspectiveCamera.cpp

    src/gfx/buffers/ebo.cpp
	src/gfx/buffers/fbo.cpp
	src/gfx/buffers/rbo.cpp
	src/gfx/buffers/vao.cpp
	src/gfx/buffers/vbo.cpp
	src/gfx/buffers/ssbo.cpp

	src/gfx/lighting/lights.cpp

	src/gfx/models/model.cpp
	src/gfx/models/mesh.cpp
	src/gfx/models/modelMatrix.cpp
	src/gfx/models/rectangle.cpp

	src/gfx/shaders/shader.cpp
	src/gfx/shaders/shaderProgram.cpp

	src/gfx/texture/texture2d.cpp
	src/gfx/texture/material.cpp
	src/gfx/texture/writableTexture2d.cpp
	src/gfx/texture/font.cpp

	src/logging/logger.cpp

	src/glad.c
)

target_include_directories(remus PUBLIC 
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
	${FREETYPE_INCLUDE_DIRS}
)

target_include_directories(remus PRIVATE src)

target_link_libraries(remus stdc++fs GL glfw "${CMAKE_DL_LIBS}" freetype "${ASSIMP_LIBRARIES}")

install(TARGETS remus
	EXPORT remusConfig
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

export(TARGETS remus
    FILE "${CMAKE_CURRENT_BINARY_DIR}/remusConfig.cmake"
)

install(EXPORT remusConfig
    DESTINATION "${CMAKE_INSTALL_DATADIR}/remus/cmake"
)

# Create test environment
add_executable(remus_test 
	test/main.cpp
	test/testScene.cpp
	test/testDriver.cpp
)

target_include_directories(remus_test PRIVATE test)

target_link_libraries(remus_test remus)

file(COPY test/resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})