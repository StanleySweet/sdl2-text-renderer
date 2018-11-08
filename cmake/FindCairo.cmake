##
## Author: Stanislas Daniel Claude Dolcini
## Contribs: /
##

if (WIN32)
    set(CAIRO_DIR "${CMAKE_CURRENT_LIST_DIR}/../lib/windows/Cairo/")
    set(CAIRO_INCLUDE_DIRS "${CAIRO_DIR}include/")
    if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
      set(CAIRO_LIB_DIR "${CAIRO_DIR}lib/x64/")
    else ()
      set(CAIRO_LIB_DIR "${CAIRO_DIR}lib/x86/")
    endif ()
    set(CAIRO_LIBRARIES "${CAIRO_LIB_DIR}/cairo.lib")
endif()