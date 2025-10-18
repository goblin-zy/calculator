# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\calmechine_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\calmechine_autogen.dir\\ParseCache.txt"
  "calmechine_autogen"
  )
endif()
