#  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
cmake_minimum_required(VERSION 2.8)

# doxygen working directory
set(DOXYGEN_WD ${CMAKE_CURRENT_SOURCE_DIR})

# get the version string
file(READ ${PROJECT_SOURCE_DIR}/VERSION OGLPLUS_VERSION_STR)

# doxyfile for building html docs
set(DOXYFILE ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile-html)
file(WRITE ${DOXYFILE} "@INCLUDE = ${DOXYGEN_WD}/Doxyfile.oalplus\n")
file(APPEND ${DOXYFILE} "IMAGE_PATH += ../../logo/ \n")
if(NOT OGLPLUS_NO_EXAMPLES)
	file(APPEND ${DOXYFILE} "IMAGE_PATH += ${PROJECT_BINARY_DIR}/example/oalplus \n")
endif()
file(APPEND ${DOXYFILE} "OUTPUT_DIRECTORY = ${CMAKE_CURRENT_BINARY_DIR}\n")
file(APPEND ${DOXYFILE} "GENERATE_TAGFILE = ${CMAKE_CURRENT_BINARY_DIR}/doxygen.tags\n")
file(APPEND ${DOXYFILE} "TAGFILES += ${CMAKE_CURRENT_BINARY_DIR}/../oglplus/doxygen.tags\n")
file(APPEND ${DOXYFILE} "TAGFILES += ${CMAKE_CURRENT_BINARY_DIR}/../eglplus/doxygen.tags\n")
file(APPEND ${DOXYFILE} "PROJECT_NUMBER = ${OGLPLUS_VERSION_STR}\n")
file(APPEND ${DOXYFILE} "QUIET = YES\n")

add_custom_command(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/html/index.html
	COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE}
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	COMMENT "Generating OALplus HTML documentation"
)

add_custom_target(
	oalplus-doc-index-html
	DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/html/index.html
)

set(COPIED_FILES tab_a.png tab_b.png tab_h.png tab_s.png tabs.css)
set(COPIED_FILES_TARGETS "")

foreach(COPIED_FILE ${COPIED_FILES})
	add_custom_target(
		"oglplus-doc-doxygen-oalplus-copy-${COPIED_FILE}"
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
			"${CMAKE_CURRENT_SOURCE_DIR}/${COPIED_FILE}"
			"${CMAKE_CURRENT_BINARY_DIR}/html/${COPIED_FILE}"
		COMMENT "Copying file ${COPIED_FILE}"
		DEPENDS oalplus-doc-index-html
	)
	set(COPIED_FILES_TARGETS
		"${COPIED_FILES_TARGETS}"
		"oglplus-doc-doxygen-oalplus-copy-${COPIED_FILE}"
	)
endforeach()

add_custom_target(
	rebuild-oalplus-doc
	COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE}
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

unset(DOXYFILE)

add_custom_target(
	oalplus-doc
	DEPENDS ${COPIED_FILES_TARGETS}
)

unset(DOC_DEPENDS)
