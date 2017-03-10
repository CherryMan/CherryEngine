ADD_LIBRARY(cherryengine core.cpp)
ADD_LIBRARY(glad glad.c)

TARGET_INCLUDE_DIRECTORIES(cherryengine PUBLIC
                           ${CherryEngine_SOURCE_DIR}/include)
TARGET_INCLUDE_DIRECTORIES(cherryengine PRIVATE
                           ${CherryEngine_SOURCE_DIR}/src)

TARGET_INCLUDE_DIRECTORIES(glad PRIVATE
                           ${CherryEngine_SOURCE_DIR}/include)

TARGET_LINK_LIBRARIES(glad ld)
TARGET_LINK_LIBRARIES(cherryengine glfw glad)
