# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.10.2)

set(APP_GLUE_DIR ${ANDROID_NDK}/sources/android/native_app_glue)
include_directories(${APP_GLUE_DIR})
include_directories(ThirdParty)
#add_library(glm STATIC ThirdParty/glm)
#set_target_properties(glm PROPERTIES LINKER_LANGUAGE CXX)
#add_library(app-glue STATIC ${APP_GLUE_DIR}/android_native_app_glue.c)
add_subdirectory(VulkanCubePipeline)

set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")

add_library( # Sets the name of the library.
             MiniRenderNative

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             MiniRenderMain.cpp ThirdParty/stb/stb_image.h VulkanMain.cpp VulkanMain.hpp MiniRenderCamera.cpp MiniRenderCamera.h)

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

target_link_libraries( # Specifies the target library.
                       MiniRenderNative

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} app-glue android MiniRenderVulkanPipeline)