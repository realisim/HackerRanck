
INCLUDE_DIRECTORIES( ${HackerRanck_SOURCE_DIR}/sources/)
SET(PROJECT_NAME "BiggerIsGreater")

#local files
FILE (GLOB SOURCES *.h *.cpp)
FILE (GLOB TESTCASES "testCases/*.txt")
MESSAGE(${TESTCASES})
SOURCE_GROUP("application" FILES ${SOURCES})
SOURCE_GROUP("testCases" FILES ${TESTCASES})

ADD_EXECUTABLE( ${PROJECT_NAME} ${SOURCES} )

#install to bin and move assets
SET ( destinationPath ${HackerRanck_SOURCE_DIR}/bin/${PROJECT_NAME} )
INSTALL(TARGETS ${PROJECT_NAME} DESTINATION ${destinationPath} )
INSTALL(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/testCases/ DESTINATION ${destinationPath}/testCases )