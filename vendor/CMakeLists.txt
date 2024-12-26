add_library(vendor INTERFACE)

add_subdirectory(SDL)
add_subdirectory(SDL_image)

target_link_libraries(vendor INTERFACE SDL3::SDL3)
target_link_libraries(vendor INTERFACE SDL3_image::SDL3_image-shared)