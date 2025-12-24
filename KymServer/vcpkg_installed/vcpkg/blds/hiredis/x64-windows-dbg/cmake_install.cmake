# Install script for directory: C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/blds/hiredis/src/v1.3.0-73936257bb.clean

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/pkgs/hiredis_x64-windows/debug")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "OFF")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/blds/hiredis/x64-windows-dbg/hiredisd.lib")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/blds/hiredis/x64-windows-dbg/hiredisd.dll")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg]|[Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE FILE FILES "C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/blds/hiredis/x64-windows-dbg/hiredisd.pdb")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/build/native" TYPE FILE FILES "C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/blds/hiredis/src/v1.3.0-73936257bb.clean/hiredis.targets")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/hiredis" TYPE FILE FILES
    "C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/blds/hiredis/src/v1.3.0-73936257bb.clean/hiredis.h"
    "C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/blds/hiredis/src/v1.3.0-73936257bb.clean/read.h"
    "C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/blds/hiredis/src/v1.3.0-73936257bb.clean/sds.h"
    "C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/blds/hiredis/src/v1.3.0-73936257bb.clean/async.h"
    "C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/blds/hiredis/src/v1.3.0-73936257bb.clean/alloc.h"
    "C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/blds/hiredis/src/v1.3.0-73936257bb.clean/sockcompat.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/hiredis" TYPE DIRECTORY FILES "C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/blds/hiredis/src/v1.3.0-73936257bb.clean/adapters")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/blds/hiredis/x64-windows-dbg/hiredis.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/hiredis/hiredis-targets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/hiredis/hiredis-targets.cmake"
         "C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/blds/hiredis/x64-windows-dbg/CMakeFiles/Export/c30adf9aa42d7da0b03f0434e5e1ac2a/hiredis-targets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/hiredis/hiredis-targets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/hiredis/hiredis-targets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/hiredis" TYPE FILE FILES "C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/blds/hiredis/x64-windows-dbg/CMakeFiles/Export/c30adf9aa42d7da0b03f0434e5e1ac2a/hiredis-targets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/hiredis" TYPE FILE FILES "C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/blds/hiredis/x64-windows-dbg/CMakeFiles/Export/c30adf9aa42d7da0b03f0434e5e1ac2a/hiredis-targets-debug.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/hiredis" TYPE FILE FILES
    "C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/blds/hiredis/x64-windows-dbg/hiredis-config.cmake"
    "C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/blds/hiredis/x64-windows-dbg/hiredis-config-version.cmake"
    )
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/blds/hiredis/x64-windows-dbg/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
if(CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_COMPONENT MATCHES "^[a-zA-Z0-9_.+-]+$")
    set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
  else()
    string(MD5 CMAKE_INST_COMP_HASH "${CMAKE_INSTALL_COMPONENT}")
    set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INST_COMP_HASH}.txt")
    unset(CMAKE_INST_COMP_HASH)
  endif()
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/blds/hiredis/x64-windows-dbg/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
