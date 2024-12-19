# Install script for directory: C:/Users/youss/Desktop/CollegeWork/Embedded Proj GUC/blink2/build/_deps/picotool-src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Users/youss/Desktop/CollegeWork/Embedded Proj GUC/blink2/build/_deps")
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
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "C:/VSARM/mingw/mingw32/bin/objdump.exe")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/picotool" TYPE EXECUTABLE MESSAGE_NEVER FILES "C:/Users/youss/Desktop/CollegeWork/Embedded Proj GUC/blink2/build/_deps/picotool-build/picotool.exe")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/picotool/picotool.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/picotool/picotool.exe")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "C:/VSARM/mingw/mingw32/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/picotool/picotool.exe")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/picotool/picotoolTargets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/picotool/picotoolTargets.cmake"
         "C:/Users/youss/Desktop/CollegeWork/Embedded Proj GUC/blink2/build/_deps/picotool-build/CMakeFiles/Export/picotool/picotoolTargets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/picotool/picotoolTargets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/picotool/picotoolTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/picotool" TYPE FILE MESSAGE_NEVER FILES "C:/Users/youss/Desktop/CollegeWork/Embedded Proj GUC/blink2/build/_deps/picotool-build/CMakeFiles/Export/picotool/picotoolTargets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/picotool" TYPE FILE MESSAGE_NEVER FILES "C:/Users/youss/Desktop/CollegeWork/Embedded Proj GUC/blink2/build/_deps/picotool-build/CMakeFiles/Export/picotool/picotoolTargets-release.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/picotool" TYPE FILE MESSAGE_NEVER FILES
    "C:/Users/youss/Desktop/CollegeWork/Embedded Proj GUC/blink2/build/_deps/picotool-build/picotoolConfig.cmake"
    "C:/Users/youss/Desktop/CollegeWork/Embedded Proj GUC/blink2/build/_deps/picotool-build/picotoolConfigVersion.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/youss/Desktop/CollegeWork/Embedded Proj GUC/blink2/build/_deps/picotool-build/errors/cmake_install.cmake")
  include("C:/Users/youss/Desktop/CollegeWork/Embedded Proj GUC/blink2/build/_deps/picotool-build/picoboot_connection/cmake_install.cmake")
  include("C:/Users/youss/Desktop/CollegeWork/Embedded Proj GUC/blink2/build/_deps/picotool-build/elf/cmake_install.cmake")
  include("C:/Users/youss/Desktop/CollegeWork/Embedded Proj GUC/blink2/build/_deps/picotool-build/elf2uf2/cmake_install.cmake")
  include("C:/Users/youss/Desktop/CollegeWork/Embedded Proj GUC/blink2/build/_deps/picotool-build/lib/cmake_install.cmake")
  include("C:/Users/youss/Desktop/CollegeWork/Embedded Proj GUC/blink2/build/_deps/picotool-build/bintool/cmake_install.cmake")
  include("C:/Users/youss/Desktop/CollegeWork/Embedded Proj GUC/blink2/build/_deps/picotool-build/pico_binary_info/cmake_install.cmake")
  include("C:/Users/youss/Desktop/CollegeWork/Embedded Proj GUC/blink2/build/_deps/picotool-build/boot_uf2_headers/cmake_install.cmake")
  include("C:/Users/youss/Desktop/CollegeWork/Embedded Proj GUC/blink2/build/_deps/picotool-build/boot_picoboot_headers/cmake_install.cmake")
  include("C:/Users/youss/Desktop/CollegeWork/Embedded Proj GUC/blink2/build/_deps/picotool-build/boot_picobin_headers/cmake_install.cmake")
  include("C:/Users/youss/Desktop/CollegeWork/Embedded Proj GUC/blink2/build/_deps/picotool-build/pico_usb_reset_interface_headers/cmake_install.cmake")
  include("C:/Users/youss/Desktop/CollegeWork/Embedded Proj GUC/blink2/build/_deps/picotool-build/pico_platform/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "C:/Users/youss/Desktop/CollegeWork/Embedded Proj GUC/blink2/build/_deps/picotool-build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
