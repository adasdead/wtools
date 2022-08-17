set(CMAKE_JAVA_COMPILE_FLAGS "-source" "1.8" "-target" "1.8")

find_package(Java REQUIRED)
include(UseJava)

add_jar(JWTools VERSION ${PROJECT_VERSION}
    me/adasdead/WTools/wColors.java
    me/adasdead/WTools/wCore.java
    me/adasdead/WTools/wMessageBox.java
    me/adasdead/WTools/wMouse.java
    me/adasdead/WTools/wNotifications.java
    me/adasdead/WTools/wSystem.java
    me/adasdead/WTools/wTerminal.java
)

get_target_property(_jarFile JWTools JAR_FILE)
get_target_property(_classDir JWTools CLASSDIR)