# CMakeList.txt : CMake project for VulkanCubePipeline, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.10.2)

set(APP_GLUE_DIR ${ANDROID_NDK}/sources/android/native_app_glue)
include_directories(${APP_GLUE_DIR})
include_directories(ThirdParty)

include_directories(../ThirdParty)
add_library(glm STATIC ../ThirdParty/glm)
set_target_properties(glm PROPERTIES LINKER_LANGUAGE CXX)
add_library(app-glue STATIC ${APP_GLUE_DIR}/android_native_app_glue.c)

find_package(jsoncpp)

# Library target
add_library (MiniRenderVulkanPipeline SHARED "VulkanCubePipeline.cpp" "VulkanCubePipeline.h" "src/VulkanPipelineService.cpp" "include/VulkanPipelineService.h" "include/QueueFamilyIndices.h" "include/SwapChainSupportDetails.h" "include/FileLoadingService.h" "include/Vertex.h" "include/CameraBufferObject.h" "../ThirdParty/stb/stb_image.h")

target_link_libraries(MiniRenderVulkanPipeline app-glue android vulkan glm jsoncpp_lib)

# TODO: Add tests and install targets if needed.
