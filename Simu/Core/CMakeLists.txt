set(LIB_NAME "Core")
option(LibA_BUILD_SHARED "Build the library as shared" OFF)

# Find packages
find_package(raylib)

# Sources
file(GLOB CPP_SOURCES "*/**.cpp" "*/**.cc")
file(GLOB HPP_SOURCES "*/**.hpp" "*/**.h")

if (LibA_BUILD_SHARED)
	add_library(${LIB_NAME} SHARED ${CPP_SOURCES} ${HPP_SOURCES})
else()
	add_library(${LIB_NAME} STATIC ${CPP_SOURCES} ${HPP_SOURCES})
endif()

target_link_libraries(${LIB_NAME} PUBLIC 
	raylib
)

generate_export_header(${LIB_NAME} EXPORT_FILE_NAME ${CMAKE_BINARY_DIR}/exports/${LIB_NAME}API.h)

target_include_directories(${LIB_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/exports>
)

install(TARGETS 
  ${LIB_NAME}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  PUBLIC_HEADER DESTINATION include
)