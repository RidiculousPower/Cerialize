
get_directory_property( cmake_current_include_dir INCLUDE_DIRECTORIES )

LINK_DIRECTORIES( "/usr/local/lib" )

#  define shared library with sources
file( GLOB CERIALIZE_SOURCE "*.c" )
file( GLOB CERIALIZE_HEADERS "${cmake_current_include_dir}/cerialize/*.h" )

add_library( cerialize ${CERIALIZE_SOURCE} )

# use, i.e. don't skip the full RPATH for the build tree
set( CMAKE_SKIP_BUILD_RPATH  OFF )

# when building, don't use the install RPATH already
# (but later on when installing)
set( CMAKE_BUILD_WITH_INSTALL_RPATH ON )

set( CMAKE_INSTALL_NAME_DIR "@rpath" )

# the RPATH to be used when installing
set( CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib" )

# add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
set( CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE )

# Set the build version (VERSION) and the API version (SOVERSION)
set_target_properties( cerialize  PROPERTIES  LINKER_LANGUAGE C 
                                              OUTPUT_NAME "../libcerialize"
                                              PREFIX ""
                                              SUFFIX ".dylib"
                                              LINK_FLAGS "-Wl,-rpath,-L${CMAKE_INSTALL_RPATH}"
                                              INSTALL_RPATH ${CMAKE_INSTALL_RPATH}
                                              INSTALL_NAME_DIR ${CMAKE_INSTALL_NAME_DIR}
                                              C_FLAGS "-ggdb -fsigned-char -Wall -W -Wshadow -Wstrict-prototypes -Wpointer-arith -Wcast-qual -Winline -Werror" )

# Installation of the library
install( TARGETS cerialize DESTINATION lib PERMISSIONS OWNER_READ GROUP_READ WORLD_READ )
INSTALL( FILES ${CERIALIZE_HEADERS} DESTINATION "include/cerialize" )
INSTALL( FILES "${cmake_current_include_dir}/cerialize.h" DESTINATION "include" )
