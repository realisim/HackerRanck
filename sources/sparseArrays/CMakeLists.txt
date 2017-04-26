
INCLUDE_DIRECTORIES( ${HackerRanck_SOURCE_DIR}/sources/)
SET(PROJECT_NAME "sparseArrays")

#local files
FILE (GLOB SOURCES *.h *.cpp)
SOURCE_GROUP("application" FILES ${SOURCES})

ADD_EXECUTABLE( ${PROJECT_NAME} ${SOURCES} )

#install to bin and move assets
SET ( destinationPath ${HackerRanck_SOURCE_DIR}/bin/${PROJECT_NAME} )
INSTALL(TARGETS ${PROJECT_NAME} DESTINATION ${destinationPath} )
INSTALL(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/testCases/ DESTINATION ${destinationPath}/testCases )