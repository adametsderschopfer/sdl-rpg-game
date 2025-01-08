add_executable(${PROJECT_NAME}
        Manager/TextureManager.cpp
        Manager/TextureManager.h

        Game/Game.cpp
        Game/Game.h
        Core/GameObject/GameObject.h
        Core/GameObject/GameObject.cpp
        Game/Map.cpp
        Game/Map.h
        Core/ECS/ECS.h
        Core/ECS/Components.h
        Core/ECS/SpriteComponent.h
        Core/ECS/TransformComponent.h
        Core/ECS/PlayerController.h
        Core/ECS/ColliderComponent.h
        Core/Collision.h
        Core/Collision.cpp
        Core/ECS/TileComponent.h
        Core/ECS/ECS.cpp
        Core/ECS/Animation.h
        Manager/AssetsManager.cpp
        Manager/AssetsManager.h
        Core/ECS/ProjectileComponent.h
)
target_sources(${PROJECT_NAME} PRIVATE main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE vendor)