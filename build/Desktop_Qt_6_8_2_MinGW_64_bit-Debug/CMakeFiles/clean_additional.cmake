# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "3D_audio_autogen"
  "CMakeFiles\\3D_audio_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\3D_audio_autogen.dir\\ParseCache.txt"
  )
endif()
