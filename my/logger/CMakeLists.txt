if(DEFINED BOOST_PATH)

  add_definitions(-DBOOST_LOG_DYN_LINK)
  include_directories(${BOOST_PATH})

  add_library(mylogger SHARED
      logger.cpp
  )
  target_link_libraries(
    mylogger
    pthread
    boost_log
    boost_thread
  )
  set_target_properties(mylogger PROPERTIES VERSION ${PROJECT_VERSION})

endif(DEFINED BOOST_PATH)