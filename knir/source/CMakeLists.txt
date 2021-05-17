project(source)
add_executable(source source.cpp)
target_link_libraries(source ${OpenCV_LIBS})

set_property(TARGET source PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin.dbg")