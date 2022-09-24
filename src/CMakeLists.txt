set(HEADERS
    camera.h
    firework.h
    fs.h
    island.h
    model.h
    ocean.h
    shader.h
    stb_image.h
    texture.h
    window.h
    xobject.h
)

set(SOURCES
    camera.cpp
    firework.cpp
    fs.cpp
    island.cpp
    main.cpp
    model.cpp
    ocean.cpp
    shader.cpp
    stb_image.cpp
    texture.cpp
    window.cpp
)

include_directories(
    ../lib/glew-2.1.0/include
    ../lib/glfw-3.3.8/include
    ../lib/glm-0.9.9.8
)

add_executable(fireworks ${HEADERS} ${SOURCES})
target_link_libraries(
    fireworks
    glew
    glfw
    glm::glm
    ${OpenGL_LIBRARIES}
)

add_custom_command(TARGET fireworks POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/res" "$<TARGET_FILE_DIR:fireworks>/res"
)
