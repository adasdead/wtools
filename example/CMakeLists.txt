add_executable(Example)

target_sources(Example PRIVATE
    main.c
)

target_link_libraries(Example PRIVATE
    WTools
)