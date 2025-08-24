cmake_minimum_required(VERSION 3.15)

# Configurazione
include(cmake/ProjectConfig.cmake)
project(${PROJECT_NAME} VERSION ${PROJECT_VERSION})



add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

# Sorgenti
include(cmake/extra.cmake)
# Proprietà progetto
target_compile_definitions(${PROJECT_NAME} PRIVATE
    PROJECT_NAME="${PROJECT_NAME}"
    USE_AUDIO=1
)

# Dipendenze
find_package(SFML 2.5 REQUIRED COMPONENTS audio graphics window system)
target_link_libraries(${PROJECT_NAME} PRIVATE 
    sfml-graphics 
    sfml-window 
    sfml-system
    sfml-audio
)

# Asset handling (new for visualizer)
file(COPY assets/ DESTINATION ${CMAKE_BINARY_DIR}/assets)