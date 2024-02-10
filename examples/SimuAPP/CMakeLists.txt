# Find packages
find_package(raylib)
find_package(box2d)


# Sources
file(GLOB CPP_SOURCES "*/**.cpp" "*/**.cc")
file(GLOB HPP_SOURCES "*/**.hpp" "*/**.h")

add_executable("button_counter" ${CPP_SOURCES} ${HPP_SOURCES})
target_link_libraries("button_counter" Core raylib box2d::box2d)

target_include_directories("button_counter"
  PRIVATE
	..
)

install(TARGETS 
  "button_counter"
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  PUBLIC_HEADER DESTINATION include
)