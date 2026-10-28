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

# Presentation projection deliberately does not import SASD UI or SQLite headers.
# It can be built and tested even when a desktop backend is unavailable.
add_library(harald_catalog_presentation STATIC src/catalog_table_projection.cpp src/catalog_browser.cpp)
add_library(HARALD::CatalogPresentation ALIAS harald_catalog_presentation)
target_include_directories(harald_catalog_presentation PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(harald_catalog_presentation PUBLIC HARALD::Catalog)
target_compile_features(harald_catalog_presentation PUBLIC cxx_std_20)

if(MSVC)
    target_compile_options(harald_catalog_presentation PRIVATE /W4 /permissive-)
else()
    target_compile_options(harald_catalog_presentation PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_executable(harald_cli src/main.cpp)
target_link_libraries(harald_cli PRIVATE HARALD::Catalog)

if(BUILD_TESTING)
    add_executable(harald_catalog_tests tests/catalog_tests.cpp)
    target_link_libraries(harald_catalog_tests PRIVATE HARALD::Catalog)
    add_test(NAME harald_catalog_tests COMMAND harald_catalog_tests)

    add_executable(harald_catalog_table_projection_tests tests/catalog_table_projection_tests.cpp)
    target_link_libraries(harald_catalog_table_projection_tests PRIVATE HARALD::CatalogPresentation)
    # MSVC otherwise uses the machine's legacy code page for source literals
    # without a BOM. Our German/Japanese fixtures must be decoded as UTF-8.
    if(MSVC)
        target_compile_options(harald_catalog_table_projection_tests PRIVATE /utf-8)
    endif()
    add_test(NAME harald_catalog_table_projection_tests COMMAND harald_catalog_table_projection_tests)

    add_executable(harald_catalog_browser_tests tests/catalog_browser_tests.cpp)
    target_link_libraries(harald_catalog_browser_tests PRIVATE HARALD::CatalogPresentation)
    if(MSVC)
        target_compile_options(harald_catalog_browser_tests PRIVATE /utf-8)
    endif()
    add_test(NAME harald_catalog_browser_tests COMMAND harald_catalog_browser_tests)
endif()

# Optional integration with the separately versioned SASD UI Toolkit. This
# builds a real TableModel/TableView consumer (currently a console preview),
# without forcing GUI/SDL/GTK dependencies onto the core or default build.
option(HARALD_WITH_SASD_UI "Build optional SASD UI Toolkit model/view preview" OFF)
if(HARALD_WITH_SASD_UI)
    find_package(SASDUIToolkit 0.2 CONFIG REQUIRED)
    add_executable(harald_ui_preview src/ui_preview.cpp)
    target_link_libraries(harald_ui_preview PRIVATE HARALD::CatalogPresentation SASD::UI)
endif()

# A real, optional rendered desktop host. On Windows the toolkit's installed
# 0.2 package exports the native Win32 adapter. On Linux the GTK4 adapter is
# still build-tree-only in UI Toolkit 0.2, so an EXPLICIT source checkout is
# required. No toolkit sources or SDL/GTK dependencies enter the catalog core.
option(HARALD_WITH_DESKTOP "Build experimental native HARALD catalog window" OFF)
set(HARALD_SASD_UI_SOURCE_DIR "" CACHE PATH
    "UI Toolkit source checkout for Linux GTK4 desktop build")
if(HARALD_WITH_DESKTOP)
    if(WIN32)
        if(NOT TARGET SASD::UI::Native::Win32)
            find_package(SASDUIToolkit 0.2 CONFIG REQUIRED)
        endif()
        set(_harald_desktop_backend SASD::UI::Native::Win32)
    elseif(UNIX AND NOT APPLE)
        if(NOT TARGET SASD::UI::Native::GTK)
            if(NOT EXISTS "${HARALD_SASD_UI_SOURCE_DIR}/CMakeLists.txt")
                message(FATAL_ERROR
                    "Linux desktop requires HARALD_SASD_UI_SOURCE_DIR pointing at the "
                    "SASD UI Toolkit 0.2 source checkout (GTK is not installed/exported yet)")
            endif()
            # Normal variables rather than FORCE cache writes keep this optional
            # consumer from permanently altering another project's CMake policy.
            set(SASD_UI_BUILD_GTK_ADAPTER ON)
            set(SASD_UI_BUILD_TESTS OFF)
            set(SASD_UI_BUILD_EXAMPLES OFF)
            add_subdirectory("${HARALD_SASD_UI_SOURCE_DIR}"
                             "${CMAKE_CURRENT_BINARY_DIR}/sasd-ui-build" EXCLUDE_FROM_ALL)
        endif()
        set(_harald_desktop_backend SASD::UI::Native::GTK)
    else()
        message(FATAL_ERROR "HARALD desktop host currently supports only Windows and Linux GTK4")
    endif()

    add_executable(harald_desktop src/desktop_main.cpp)
    target_link_libraries(harald_desktop PRIVATE HARALD::CatalogPresentation
                         ${_harald_desktop_backend})
    target_compile_features(harald_desktop PRIVATE cxx_std_20)
    if(MSVC)
        target_compile_options(harald_desktop PRIVATE /W4 /permissive- /utf-8)
    else()
        target_compile_options(harald_desktop PRIVATE -Wall -Wextra -Wpedantic)
    endif()
endif()
