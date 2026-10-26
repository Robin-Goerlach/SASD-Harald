cmake_minimum_required(VERSION 3.20)
project(HARALD VERSION 0.0.1 LANGUAGES CXX)

include(CTest)
find_package(SQLite3 REQUIRED)

add_library(harald_catalog STATIC src/catalog.cpp src/sqlite_catalog.cpp)
add_library(HARALD::Catalog ALIAS harald_catalog)
target_include_directories(harald_catalog PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(harald_catalog PUBLIC SQLite::SQLite3)
target_compile_features(harald_catalog PUBLIC cxx_std_20)

if(MSVC)
    target_compile_options(harald_catalog PRIVATE /W4 /permissive-)
else()
    target_compile_options(harald_catalog PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_executable(harald_cli src/main.cpp)
target_link_libraries(harald_cli PRIVATE HARALD::Catalog)

if(BUILD_TESTING)
    add_executable(harald_catalog_tests tests/catalog_tests.cpp)
    target_link_libraries(harald_catalog_tests PRIVATE HARALD::Catalog)
    add_test(NAME harald_catalog_tests COMMAND harald_catalog_tests)
endif()

# Optional integration with the separately versioned SASD UI Toolkit. This
# builds a real TableModel/TableView consumer (currently a console preview),
# without forcing GUI/SDL/GTK dependencies onto the core or default build.
option(HARALD_WITH_SASD_UI "Build optional SASD UI Toolkit model/view preview" OFF)
if(HARALD_WITH_SASD_UI)
    find_package(SASDUIToolkit 0.2 CONFIG REQUIRED)
    add_executable(harald_ui_preview src/ui_preview.cpp)
    target_link_libraries(harald_ui_preview PRIVATE HARALD::Catalog SASD::UI)
endif()
