# Libraries

ADD_LIBRARY(cherryengine core.cpp CherryEngine/main.cpp)

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


# Linking
TARGET_LINK_LIBRARIES(glad dl)
TARGET_LINK_LIBRARIES(cherryengine glfw glad)
