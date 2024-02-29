# Find packages
find_package(raylib)
find_package(box2d)


# Sources
file(GLOB CPP_SOURCES "*/**.cpp" "*/**.cc")
file(GLOB HPP_SOURCES "*/**.hpp" "*/**.h")

add_executable("PingPong" ${CPP_SOURCES} ${HPP_SOURCES})
target_link_libraries("PingPong" Core raylib box2d::box2d)

target_include_directories("PingPong"
  PRIVATE
	..
)

install(TARGETS 
  "PingPong"
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  PUBLIC_HEADER DESTINATION include
)