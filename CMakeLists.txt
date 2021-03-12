# CMakeList.txt: PDFtools 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)
project ("PDFtools")

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set(CMAKE_CXX_STANDARD 17)  # 指定C++标准
include_directories("${PROJECT_SOURCE_DIR}/include/")  # 包含头文件目录，可指定多个
link_directories("${PROJECT_SOURCE_DIR}/lib")  # 需要放在add_executable前

# 将源代码添加到此项目的可执行文件。
add_executable(PDFtools "src/PDFtools.cpp" "include/PDFtools.h" "include/PDFdeal.h" "src/PDFdeal.cpp")


IF (WIN32)
	target_link_libraries( PDFtools "libresources.lib" "libmupdf.lib")  # 需要放在add_executable后
ELSEIF (UNIX)
	target_link_libraries( PDFtools "libmupdf.a" "libmupdf-third.a")  # 需要放在add_executable后
ELSE()
	MESSAGE(STATUS "其余系统类型未测试过，可修改cmakelists.txt后尝试")
ENDIF ()

