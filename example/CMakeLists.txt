add_executable(Example)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
pkg_search_module(GLIB REQUIRED glib-2.0)

target_sources(Example PRIVATE
    main.c
)

target_link_libraries(Example PRIVATE
    WTools
    ${GLIB_LIBRARIES}
)
link_directories(${GLIB_LIBRARY_DIRS})
target_link_libraries(Example INTERFACE ${GLIB_LDFLAGS})

target_include_directories(Example PRIVATE
    ${GLIB_INCLUDE_DIRS}
)
add_definitions(${GLIB_CFLAGS_OTHER})