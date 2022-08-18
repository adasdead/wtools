set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(WTools SHARED)

if (COMPILE_JAVA_SOURCES)

    find_package(JNI REQUIRED)

    target_link_libraries(WTools PUBLIC
        JNI::JNI
    )

    target_sources(WTools PRIVATE
        jni/me_adasdead_WTools_wMessageBox.c
        jni/me_adasdead_WTools_wMouse.c
        jni/me_adasdead_WTools_wNotifications.c
        jni/me_adasdead_WTools_wSystem.c
        jni/me_adasdead_WTools_wTerminal.c
    )

    target_include_directories(WTools PRIVATE
        jni/
    )

endif()

if (UNIX)

    find_package(X11 REQUIRED)

    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

    target_sources(WTools PRIVATE
        linux/wnotifications.c
        linux/wterminal.c
        linux/wsystem.c
        linux/wmsgbox.c
        linux/wmouse.c
    )

    target_include_directories(WTools PRIVATE
        ${GTK3_INCLUDE_DIRS}
    )

    target_link_libraries(WTools PRIVATE
        ${GTK3_LIBRARIES}
        X11::X11
    )

endif()

if (WIN32)

    target_sources(WTools PRIVATE
        windows/wnotifications.c
        windows/wterminal.c
        windows/wsystem.c
        windows/wmsgbox.c
        windows/wmouse.c
    )

endif()

target_include_directories(WTools PUBLIC
    ${PROJECT_INCLUDE_DIR}
)