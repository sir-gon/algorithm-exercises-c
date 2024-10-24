file (GLOB_RECURSE SOURCES "src/*.c")
add_library(exercises STATIC ${SOURCES})

target_include_directories(exercises
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

set_property(TARGET exercises PROPERTY C_STANDARD 11)

target_compile_options(exercises
        PUBLIC
        -save-temps
)

install(TARGETS exercises
        EXPORT exercisesConfig
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
)

install(DIRECTORY include/ DESTINATION include)
install(EXPORT exercisesConfig DESTINATION share/exercises/cmake)
export(TARGETS exercises FILE exercisesConfig.cmake)
