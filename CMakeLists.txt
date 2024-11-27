cmake_minimum_required(VERSION 3.14)
project(Neocalc)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(ftxui QUIET)

if(NOT ftxui_FOUND) 
  message(STATUS "FTXUI not found, fetching it from the repository.")
    
  include(FetchContent)
  set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
    
  FetchContent_Declare(
      ftxui
      GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
      GIT_TAG v5.0.0
  )
  FetchContent_MakeAvailable(ftxui)
else()
    message(STATUS "FTXUI found, using the installed version.")
endif()

set(UI_SOURCE src/neocalc/ui/ui.cpp)
set(MAIN_SOURCE src/neocalc/main.cpp)

add_executable(Neocalc 
  ${UI_SOURCE}
  ${MAIN_SOURCE}
)

set(UI_INCLUDE ${CMAKE_SOURCE_DIR}/include/neocalc/ui)

target_include_directories(Neocalc PRIVATE 
  ${UI_INCLUDE}
)

target_link_libraries(Neocalc
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component
)
