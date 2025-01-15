cmake_minimum_required(VERSION 3.16)

project(BinanceTradeCpp VERSION 1.0.0 LANGUAGES CXX)

set(QT_VERSION_MAJOR 6)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

# set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=-*,clang-analyzer-*")

set(CMAKE_AUTOUIC_SEARCH_PATHS "${CMAKE_SOURCE_DIR}/src/view/ui")


set(CMAKE_INSTALL_PREFIX "$ENV{HOME}/${PROJECT_NAME}/${PROJECT_VERSION}")

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Build types" FORCE)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_BINARY_DIR}/Debug/${PROJECT_VERSION}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/Release/${PROJECT_VERSION}/bin)

set(CMAKE_PREFIX_PATH "/home/adam/Qt/6.7.3/gcc_64/lib/cmake/")



# find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql LinguistTools)
find_package(Qt${QT_VERSION_MAJOR}
    REQUIRED COMPONENTS
        Core
        Widgets
        Sql
        Gui
        LinguistTools
)

find_package( OpenSSL REQUIRED )


set(TS_FILES ${PROJECT_NAME}_en_US.ts)

set(PROJECT_HEADERS_DIR
    ${CMAKE_SOURCE_DIR}/include)

set(PROJECT_SOURCES

    ${TS_FILES}
    main.cpp
    src/database/DBManager.cpp
    src/coordinator/AppCoord.cpp

    src/config/Config.cpp
    src/tools/CryptoManager.cpp
    src/tools/HashManager.cpp
    src/tools/Log.cpp
    src/tools/utils.cpp

    src/view/MainVw.cpp
    src/model/MainModel.cpp
    src/viewmodel/MainVM.cpp
    src/coordinator/MainCoord.cpp

    # src/view/UserLoginVw.cpp
    # src/model/UserLoginMdl.cpp
    # src/viewmodel/UserLoginVM.cpp
    # src/coordinator/UserLoginCoord.cpp

    src/view/DBLoginVw.cpp
    src/view/DBLoginVw2.cpp
    src/model/DBLoginMdl.cpp
    src/viewmodel/DBLoginVM.cpp
    src/coordinator/DBLoginCoord.cpp

    src/view/CreateModelVw.cpp
    src/model/CreateModelMdl.cpp
    src/viewmodel/CreateModelVM.cpp
    src/coordinator/CreateModelCoord.cpp

    src/view/PullDataWidget.cpp
    src/model/PullDataMdl.cpp
    src/viewmodel/PullDataVM.cpp
    src/coordinator/PullDataCoord.cpp

)

set(PROJECT_HEADERS

    include/database/DBManager.hpp
    include/coordinator/AppCoord.hpp
    include/tools/Exceptions.hpp

    include/config/Config.hpp
    include/tools/CryptoManager.hpp
    include/tools/HashManager.hpp
    include/tools/Log.hpp
    include/tools/utils.hpp

    include/view/MainVw.hpp
    include/model/MainModel.hpp
    include/viewmodel/MainVM.hpp
    include/coordinator/MainCoord.hpp


    # include/view/UserLoginVw.hpp
    # include/view/IUserLoginView.hpp
    # include/model/UserLoginMdl.hpp
    # include/viewmodel/UserLoginVM.hpp
    # include/viewmodel/IUserLoginVM.hpp
    # include/coordinator/UserLoginCoord.hpp

    include/view/DBLoginVw.hpp
    include/view/DBLoginVw2.hpp
    include/view/IDBLoginVw.hpp
    include/viewmodel/DBLoginVM.hpp
    include/viewmodel/IDBLoginVM.hpp
    include/coordinator/DBLoginCoord.hpp
    
    include/view/CreateModelVw.hpp
    include/model/CreateModelMdl.hpp
    include/viewmodel/CreateModelVM.hpp
    include/coordinator/CreateModelCoord.hpp


    include/view/PullDataWidget.hpp
    include/model/PullDataMdl.hpp
    include/viewmodel/PullDataVM.hpp
    include/coordinator/PullDataCoord.hpp
)

set(PROJECT_UI_FILES
    src/view/ui/MainWindow.ui
    # src/view/ui/UserLoginWindow.ui
    src/view/ui/DatabaseLoginWindow.ui
    src/view/ui/DBLoginDialog.ui
    src/view/ui/CreateModelDialog.ui
    src/view/ui/PullDataWidget.ui
)


# # UIC çıktıları (header dosyaları) için bir liste tanımla
# set(UI_HEADERS)

# # Her .ui dosyasını uic ile header'a dönüştür
# foreach(UI_FILE ${PROJECT_UI_FILES})
#     get_filename_component(UI_FILENAME ${UI_FILE} NAME_WE)
#     set(UI_HEADER "${CMAKE_CURRENT_BINARY_DIR}/ui_${UI_FILENAME}.h")

#     add_custom_command(
#         OUTPUT ${UI_HEADER}
#         COMMAND ${Qt6_UIC_EXECUTABLE} -o ${UI_HEADER} ${UI_FILE}
#         DEPENDS ${UI_FILE}
#         COMMENT "Generating ${UI_HEADER} from ${UI_FILE}"
#         VERBATIM
#     )

#     # Her header dosyasını UI_HEADERS listesine ekle
#     list(APPEND UI_HEADERS ${UI_HEADER})
# endforeach()


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME}
        MANUAL_FINALIZATION
        ${PROJECT_UI_FILES}
        ${PROJECT_HEADERS}
        ${PROJECT_SOURCES}
       
        icons.qrc
        


    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(${PROJECT_NAME} SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(${PROJECT_NAME}
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

# add_subdirectory(external/nlohmann)

set( INCLUDE_DIRECTORIES

    /external     /include      /share       /src

    /external/nlohmann
    /share/${PROJECT_NAME}
    /share/${PROJECT_NAME}/${PROJECT_VERSION}


    include/view        include/viewmodel    include/model
    include/coordinator include/config       include/tools
    include/database

    src/view            src/viewmodel        src/model
    src/coordinator     src/config           src/tools
    src/database

    include/view/ui
    src/view/ui

    build/BinanceTradeCpp_autogen/include_Debug
)

target_include_directories(${PROJECT_NAME}
                                PRIVATE ${INCLUDE_DIRECTORIES}
)


target_link_libraries(  ${PROJECT_NAME} PRIVATE
                        Qt${QT_VERSION_MAJOR}::Widgets
                        Qt${QT_VERSION_MAJOR}::Sql
                        Qt${QT_VERSION_MAJOR}::Gui
                        OpenSSL::SSL
                        OpenSSL::Crypto
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${Qt${QT_VERSION_MAJOR}_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.${PROJECT_NAME})
endif()
set_target_properties(${PROJECT_NAME} PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)


# BEGIN: nlohmann_json kütüphanesinin projeye eklenmesi

add_library(nlohmann_json INTERFACE) 

target_include_directories(
    nlohmann_json
    INTERFACE
    ${CMAKE_SOURCE_DIR}/external
)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json)

target_precompile_headers( ${PROJECT_NAME}
                            PRIVATE external/nlohmann/json.hpp
)

add_dependencies(${PROJECT_NAME} nlohmann_json)


# END: nlohmann_json kütüphanesinin projeye eklenmesi

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable( ${PROJECT_NAME} )
endif()


# install(CODE "
#     execute_process(COMMAND test -d \"$ENV{HOME}/${PROJECT_NAME}\" RESULT_VARIABLE dir_exists)
#     if(dir_exists EQUAL 0)
#         message(FATAL_ERROR \"Directory '$ENV{HOME}/${PROJECT_NAME}' already exists. Please remove it or choose a different directory.\")
#     endif()
# ")



SET( DIR_LIST_FOR_CONFIGURE "Debug" "Release")

foreach(ITEM IN LISTS DIR_LIST_FOR_CONFIGURE)

    configure_file( ${CMAKE_SOURCE_DIR}/share/${PROJECT_VERSION}/share/version.json.in
                    ${CMAKE_BINARY_DIR}/${ITEM}/${PROJECT_VERSION}/share/version.json
                    @ONLY
    )

    configure_file( ${CMAKE_SOURCE_DIR}/share/${PROJECT_VERSION}/share/config.json.in
                    ${CMAKE_BINARY_DIR}/${ITEM}/${PROJECT_VERSION}/share/config.json
                    @ONLY
    )

    configure_file( ${CMAKE_SOURCE_DIR}/share/${PROJECT_VERSION}/share/users.json.in
                    ${CMAKE_BINARY_DIR}/${ITEM}/${PROJECT_VERSION}/share/users.json
                    @ONLY
    )

    configure_file( ${CMAKE_SOURCE_DIR}/share/${PROJECT_VERSION}/share/keys/database.dat.in
                    ${CMAKE_BINARY_DIR}/${ITEM}/${PROJECT_VERSION}/share/keys/database.dat
                    @ONLY
    )

    configure_file( ${CMAKE_SOURCE_DIR}/share/${PROJECT_VERSION}/share/keys/user.dat.in
                    ${CMAKE_BINARY_DIR}/${ITEM}/${PROJECT_VERSION}/share/keys/user.dat
                    @ONLY
    )

    configure_file( ${CMAKE_SOURCE_DIR}/share/${PROJECT_VERSION}/share/logs.log.in
                    ${CMAKE_BINARY_DIR}/${ITEM}/${PROJECT_VERSION}/share/logs.log
                    @ONLY
    )


    configure_file(${CMAKE_SOURCE_DIR}/share/scripts/check_postgresql_installation.sh
                    ${CMAKE_BINARY_DIR}/${ITEM}/share/scripts/check_postgresql_installation.sh
                    COPYONLY
    )



endforeach()

install( DIRECTORY
            ${CMAKE_BINARY_DIR}/Debug/${PROJECT_VERSION}/share/logs
         DESTINATION
            ${CMAKE_INSTALL_PREFIX}/share/logs
)
# file(MAKE_DRIRECTORY ${CMAKE_INSTALL_PREFIX}/share )
# file(MAKE_DRIRECTORY ${CMAKE_INSTALL_PREFIX}/share/logs )

install( FILES
            ${CMAKE_BINARY_DIR}/Release/${PROJECT_VERSION}/share/version.json
            ${CMAKE_BINARY_DIR}/Release/${PROJECT_VERSION}/share/config.json
         DESTINATION
            ${CMAKE_INSTALL_PREFIX}/share
)

install( PROGRAMS
            ${CMAKE_BINARY_DIR}/Release/share/scripts/check_postgresql_installation.sh
         DESTINATION
            ${CMAKE_INSTALL_PREFIX}/../share/scripts
)






install(CODE "execute_process(COMMAND sudo chown -R $ENV{USER}:$ENV{USER} ${CMAKE_INSTALL_PREFIX}/..)")


message(STATUS "C Compiler: ${CMAKE_C_COMPILER}")
message(STATUS "C++ Compiler: ${CMAKE_CXX_COMPILER}")

message(STATUS "PROJECT_NAME        : ${PROJECT_NAME}")

message(STATUS "PROJECT_SOURCES     : ${PROJECT_SOURCES}")
message(STATUS "PROJECT_HEADERS     : ${PROJECT_HEADERS}")
message(STATUS "PROJECT_UI_FILES    : ${PROJECT_UI_FILES}")
message(STATUS "INCLUDE_DIRECTORIES : ${INCLUDE_DIRECTORIES}")

message(STATUS "CMAKE_BUILD_TYPE    : ${CMAKE_BUILD_TYPE}")
message(STATUS "CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG   : ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}")
message(STATUS "CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE : ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}")
message(STATUS "CMAKE_INSTALL_PREFIX                   : ${CMAKE_INSTALL_PREFIX}")
message(STATUS "CMAKE_PREFIX_PATH                      : ${CMAKE_PREFIX_PATH}")
message(STATUS "CMAKE_SOURCE_DIR                       : ${CMAKE_SOURCE_DIR}")
message(STATUS "CMAKE_BINARY_DIR                       : ${CMAKE_BINARY_DIR}")
message(STATUS "CMAKE_RUNTIME_OUTPUT_DIRECTORY         : ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
