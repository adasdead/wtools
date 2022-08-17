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