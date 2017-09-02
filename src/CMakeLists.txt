SET(src
    core.cpp
    CherryEngine/main.cpp
    CherryEngine/state.cpp
    CherryEngine/log.cpp
    state/state_machine.cpp
    log/logbuf.cpp
)


# Libraries
ADD_LIBRARY(cherryengine ${src})
ADD_LIBRARY(glad glad.c)


# Include
TARGET_INCLUDE_DIRECTORIES(cherryengine

                           PUBLIC
                           ${CherryEngine_SOURCE_DIR}/include

                           PRIVATE
                           ${CherryEngine_SOURCE_DIR}/src)

TARGET_INCLUDE_DIRECTORIES(glad

                           PRIVATE
                           ${CherryEngine_SOURCE_DIR}/include)

# Packages
FIND_PACKAGE(Threads)

# Linking
TARGET_LINK_LIBRARIES(glad dl)
TARGET_LINK_LIBRARIES(cherryengine glfw glad ${CMAKE_THREADS_LIBS_INIT} -lpthread)
