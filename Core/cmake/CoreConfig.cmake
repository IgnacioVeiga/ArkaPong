set(Core_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/../include")
set(Core_LIBRARIES Core)

# Export Core target
if(NOT TARGET Core)
    include("${CMAKE_CURRENT_LIST_DIR}/CoreTargets.cmake")
endif()