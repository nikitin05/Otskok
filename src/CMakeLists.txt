add_executable(example main.cpp Engine.cpp Engine.h Circle.cpp Circle.h Ball.cpp Ball.h Draw.cpp Input.cpp Update.cpp Function.h Function.cpp)
        #resources/arial.ttf resources/icon.ico resources/background.png resources/ball.png resources/segment.png)
target_link_libraries(example PRIVATE ImGui-SFML::ImGui-SFML)


# Copy DLLs needed for runtime on Windows
if(WIN32)
    if (BUILD_SHARED_LIBS)
        add_custom_command(TARGET example POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_FILE:ImGui-SFML::ImGui-SFML>
                $<TARGET_FILE:sfml-graphics>
                $<TARGET_FILE:sfml-window>
                $<TARGET_FILE:sfml-system>
                $<TARGET_FILE_DIR:example>)
    endif()
endif()