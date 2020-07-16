# CMakeList.txt : CMake project for VulkanCubePipeline, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.10.2)

set(APP_GLUE_DIR ${ANDROID_NDK}/sources/android/native_app_glue)
include_directories(${APP_GLUE_DIR})

include_directories(../ThirdParty)
add_library(glm STATIC ../ThirdParty/glm)
set_target_properties(glm PROPERTIES LINKER_LANGUAGE CXX)
add_library(app-glue STATIC ${APP_GLUE_DIR}/android_native_app_glue.c)
#add_library(jsoncpp STATIC ../ThirdParty/jsoncpp)
#set_target_properties(jsoncpp PROPERTIES LINKER_LANGUAGE CXX)


find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log )

# Library target
add_library (MiniRenderVulkanPipeline SHARED "VulkanCubePipeline.cpp" "VulkanCubePipeline.h" "src/VulkanPipelineService.cpp" "include/VulkanPipelineService.h" "include/QueueFamilyIndices.h" "include/SwapChainSupportDetails.h" "include/FileLoadingService.h" "include/Vertex.h" "include/CameraBufferObject.h" "../ThirdParty/stb/stb_image.h" "ThirdParty/jsoncpp/jsoncpp.cpp" "ThirdParty/jsoncpp/json/json.h" "ThirdParty/jsoncpp/json/json-forwards.h")
target_link_libraries(MiniRenderVulkanPipeline app-glue android vulkan glm ${log-lib})