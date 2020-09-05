cmake_minimum_required (VERSION 3.0)

set(PRODUCTNAME DemoCoreDS_SimpleReceiver)
PROJECT(${PRODUCTNAME})

#Use solution folders.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#Configure Path to the coreDS installation folder
SET(COREDS_BASE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../" CACHE PATH "Path to the coreDS installation folder")
SET(coreDSLocation  "${COREDS_BASE_PATH}")
include_directories(${COREDS_BASE_PATH}/include)			
include( "${COREDS_BASE_PATH}/cmake/coreDS.cmake" )

add_executable(${PRODUCTNAME} SimpleDataReceiver.cpp)

#Set the current project as the main project
set_property (DIRECTORY PROPERTY VS_STARTUP_PROJECT ${PRODUCTNAME})
			
# Add the correct libraries to the current targets, calls TARGET_LINK_LIBRARIES internally
coreDS_AddLibraries(${PRODUCTNAME}, ${coreDSLocation})

#Add the required files to install for coreDS to run correctly.
coreDS_InstallFiles(${PRODUCTNAME}, ${coreDSLocation})
	
install(TARGETS ${PRODUCTNAME} DESTINATION .)

# We use this project configuration files
install(DIRECTORY  "${CMAKE_CURRENT_SOURCE_DIR}/config" DESTINATION . COMPONENT ${PRODUCTNAME})

# We use this Script configuration files
install(DIRECTORY  "${CMAKE_CURRENT_SOURCE_DIR}/Script" DESTINATION ./Config COMPONENT ${PRODUCTNAME})