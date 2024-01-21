# Find packages
find_package(raylib)

# Sources
file(GLOB CPP_SOURCES "*/**.cpp" "*/**.cc")
file(GLOB HPP_SOURCES "*/**.hpp" "*/**.h")

add_executable("Program" ${CPP_SOURCES} ${HPP_SOURCES})
target_link_libraries("Program" Core raylib)

install(TARGETS 
  "Program"
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  PUBLIC_HEADER DESTINATION include
)