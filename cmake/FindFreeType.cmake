##
## Author: Stanislas Daniel Claude Dolcini
## Contribs: /
##

if (WIN32)
    set(FREETYPE_DIR "${CMAKE_CURRENT_LIST_DIR}/../lib/windows/FreeType/")
    set(FREETYPE_INCLUDE_DIRS "${FREETYPE_DIR}include/")
    if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
      set(FREETYPE_LIB_DIR "${FREETYPE_DIR}win64/")
    else ()
      set(FREETYPE_LIB_DIR "${FREETYPE_DIR}win32/")
    endif ()
    set(FREETYPE_LIBRARIES "${FREETYPE_LIB_DIR}/freetype.lib")
endif()