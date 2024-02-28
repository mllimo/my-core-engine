# Find packages
find_package(raylib)
find_package(box2d)


# Sources
file(GLOB CPP_SOURCES "*/**.cpp" "*/**.cc")
file(GLOB HPP_SOURCES "*/**.hpp" "*/**.h")

add_executable("ButtonCounter" ${CPP_SOURCES} ${HPP_SOURCES})
target_link_libraries("ButtonCounter" Core raylib box2d::box2d)

target_include_directories("ButtonCounter"
  PRIVATE
	..
)

install(TARGETS 
  "ButtonCounter"
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  PUBLIC_HEADER DESTINATION include
)