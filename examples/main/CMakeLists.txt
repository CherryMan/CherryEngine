ADD_EXECUTABLE(main main.cpp
                    base_state.cpp)

TARGET_INCLUDE_DIRECTORIES(main PUBLIC
                           ${CherryEngine_SOURCE_DIR}/include)

TARGET_LINK_LIBRARIES(main cherryengine)
