# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\opori_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\opori_autogen.dir\\ParseCache.txt"
  "opori_autogen"
  )
endif()
