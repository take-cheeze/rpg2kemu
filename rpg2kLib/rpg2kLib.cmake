# sets value
# - ${rpg2kLib_LIBRARIES} - use it like "TARGET_LINK_LIBRARIES(${TARGET} ${rpg2kLib_LIBRARIES})"

FUNCTION(FIND_RPG2KLIB RPG2KLIB_PATH)
	# set warning flags
	IF((${CMAKE_CXX_COMPILER_ID} MATCHES "GNU") OR (${CMAKE_CXX_COMPILER_ID} MATCHES "Clang"))
		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
	ENDIF()

	# DEBUG define
	IF(CMAKE_BUILD_TYPE STREQUAL "Debug")
		ADD_DEFINITIONS(-DRPG2K_DEBUG=1)
	ELSE()
		ADD_DEFINITIONS(-DRPG2K_DEBUG=0)
	ENDIF()

	ADD_SUBDIRECTORY(${RPG2KLIB_PATH})
	INCLUDE_DIRECTORIES(${RPG2KLIB_PATH})
	LINK_DIRECTORIES(${RPG2KLIB_PATH})

	# Boost
	FIND_PACKAGE(Boost REQUIRED)
	INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

	SET(rpg2kLib_LIBRARIES 	${Boost_LIBRARIES} rpg2kLib)
ENDFUNCTION()