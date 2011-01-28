# modified from BerkeleyDB .cmake
#
# -*- cmake -*-
#  from:
#  http://code.google.com/p/emeraldviewer/source/browse/indra/cmake/FindBerkeleyDB.cmake?spec=svn2d5b87bf61c915011530469add736301acccfd32&r=2d5b87bf61c915011530469add736301acccfd32
#
# modified:
#  * changed paths to suit BerkeleyDB.5.0 installation
# * reversed order for searching /usr/local and /usr

# - Find BerkeleyDB
# Find the BerkeleyDB includes and library
# This module defines
#  DB_INCLUDE_DIR, where to find db.h, etc.
#  DB_LIBRARIES, the libraries needed to use BerkeleyDB.
#  DB_FOUND, If false, do not try to use BerkeleyDB.
# also defined, but not for general use are
#  DB_LIBRARY, where to find the BerkeleyDB library.

#  Look for header in paths:
FIND_PATH( CERIALIZE_INCLUDE_DIR  cerialize.h
		                              /usr/local/include
		                              /usr/include
)


#  Look for lib in paths:
SET( CERIALIZE_NAMES ${CERIALIZE_NAMES} cerialize )
FIND_LIBRARY(CERIALIZE_LIBRARY
  NAMES ${CERIALIZE_NAMES}
  PATHS /usr/local/lib /usr/lib
)

#  set whether we found both headers and lib
IF (CERIALIZE_LIBRARY AND CERIALIZE_INCLUDE_DIR)
    SET(CERIALIZE_LIBRARIES ${CERIALIZE_LIBRARY})
    SET(CERIALIZE_FOUND "YES")
ELSE (CERIALIZE_LIBRARY AND CERIALIZE_INCLUDE_DIR)
  SET(CERIALIZE_FOUND "NO")
ENDIF (CERIALIZE_LIBRARY AND CERIALIZE_INCLUDE_DIR)


IF (CERIALIZE_FOUND)
   IF (NOT CERIALIZE_FIND_QUIETLY)
      MESSAGE(STATUS "Found Cerialize: ${CERIALIZE_LIBRARIES}")
   ENDIF (NOT CERIALIZE_FIND_QUIETLY)
ELSE (CERIALIZE_FOUND)
   IF (CERIALIZE_FIND_REQUIRED)
      MESSAGE(FATAL_ERROR "Could not find Cerialize library")
   ENDIF (CERIALIZE_FIND_REQUIRED)
ENDIF (CERIALIZE_FOUND)

# Deprecated declarations.
SET (NATIVE_CERIALIZE_INCLUDE_PATH ${CERIALIZE_INCLUDE_DIR} )
GET_FILENAME_COMPONENT (NATIVE_CERIALIZE_LIB_PATH ${CERIALIZE_LIBRARY} PATH)

MARK_AS_ADVANCED(
  CERIALIZE_LIBRARY
  CERIALIZE_INCLUDE_DIR
)