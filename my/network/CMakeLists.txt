add_library(mynetwork SHARED
    server.cpp
    client.cpp
)
set_target_properties(mynetwork PROPERTIES VERSION ${PROJECT_VERSION})