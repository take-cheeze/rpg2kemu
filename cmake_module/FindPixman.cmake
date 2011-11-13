# PIXMAN_INCLUDE_DIR - include path to pixman.h
# PIXMAN_LIBRARY - library of pixman

find_path(PIXMAN_INCLUDE_DIR_INTERNAL pixman-1/pixman.h)
find_library(PIXMAN_LIBRARY pixman-1)
if((EXISTS ${PIXMAN_INCLUDE_DIR_INTERNAL}) AND (EXISTS ${PIXMAN_LIBRARY}))
  set(Pixman_FOUND TRUE)
  set(PIXMAN_INCLUDE_DIR "${PIXMAN_INCLUDE_DIR_INTERNAL}/pixman-1")
  message(STATUS "pixman found")
else()
  set(Pixman_FOUND FALSE)
  message(STATUS "pixman not found")
endif()
