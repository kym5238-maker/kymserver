# Install script for directory: C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/blds/abseil/src/20250814.1-a96f5d5fc6.clean/absl/log

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/pkgs/abseil_x64-windows")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/blds/abseil/x64-windows-rel/lib/pkgconfig/absl_log_internal_check_impl.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/blds/abseil/x64-windows-rel/lib/pkgconfig/absl_log_internal_check_op.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/blds/abseil/x64-windows-rel/lib/pkgconfig/absl_log_internal_conditions.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/blds/abseil/x64-windows-rel/lib/pkgconfig/absl_log_internal_config.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/blds/abseil/x64-windows-rel/lib/pkgconfig/absl_log_internal_flags.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/blds/abseil/x64-windows-rel/lib/pkgconfig/absl_log_internal_format.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/blds/abseil/x64-windows-rel/lib/pkgconfig/absl_log_internal_globals.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/blds/abseil/x64-windows-rel/lib/pkgconfig/absl_log_internal_log_impl.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/blds/abseil/x64-windows-rel/lib/pkgconfig/absl_log_internal_proto.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/blds/abseil/x64-windows-rel/lib/pkgconfig/absl_log_internal_message.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/blds/abseil/x64-windows-rel/lib/pkgconfig/absl_log_internal_log_sink_set.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/blds/abseil/x64-windows-rel/lib/pkgconfig/absl_log_internal_nullguard.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/blds/abseil/x64-windows-rel/lib/pkgconfig/absl_log_internal_nullstream.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/blds/abseil/x64-windows-rel/lib/pkgconfig/absl_log_internal_strip.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/blds/abseil/x64-windows-rel/lib/pkgconfig/absl_log_internal_voidify.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/blds/abseil/x64-windows-rel/lib/pkgconfig/absl_log_internal_append_truncated.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/blds/abseil/x64-windows-rel/lib/pkgconfig/absl_absl_check.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/blds/abseil/x64-windows-rel/lib/pkgconfig/absl_absl_log.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/blds/abseil/x64-windows-rel/lib/pkgconfig/absl_check.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/blds/abseil/x64-windows-rel/lib/pkgconfig/absl_die_if_null.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/blds/abseil/x64-windows-rel/lib/pkgconfig/absl_log_flags.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/blds/abseil/x64-windows-rel/absl/log/absl_log_flags.lib")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/blds/abseil/x64-windows-rel/lib/pkgconfig/absl_log_globals.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/blds/abseil/x64-windows-rel/lib/pkgconfig/absl_log_initialize.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/blds/abseil/x64-windows-rel/lib/pkgconfig/absl_log.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/blds/abseil/x64-windows-rel/lib/pkgconfig/absl_log_entry.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/blds/abseil/x64-windows-rel/lib/pkgconfig/absl_log_sink.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/blds/abseil/x64-windows-rel/lib/pkgconfig/absl_log_sink_registry.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/blds/abseil/x64-windows-rel/lib/pkgconfig/absl_log_streamer.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/blds/abseil/x64-windows-rel/lib/pkgconfig/absl_log_internal_structured.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/blds/abseil/x64-windows-rel/lib/pkgconfig/absl_log_internal_structured_proto.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/blds/abseil/x64-windows-rel/absl/log/absl_log_internal_structured_proto.lib")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/blds/abseil/x64-windows-rel/lib/pkgconfig/absl_log_structured.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/blds/abseil/x64-windows-rel/lib/pkgconfig/absl_vlog_config_internal.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/blds/abseil/x64-windows-rel/lib/pkgconfig/absl_absl_vlog_is_on.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/blds/abseil/x64-windows-rel/lib/pkgconfig/absl_vlog_is_on.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/MS/Documents/GitHub/kymserver/KymServer/vcpkg_installed/vcpkg/blds/abseil/x64-windows-rel/lib/pkgconfig/absl_log_internal_fnmatch.pc")
endif()

