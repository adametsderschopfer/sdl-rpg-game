add_executable(${PROJECT_NAME}
        Manager/TextureManager.cpp
        Manager/TextureManager.h

        Game.cpp
        Game.h
)
target_sources(${PROJECT_NAME} PRIVATE main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE vendor)