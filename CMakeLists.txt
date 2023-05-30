#
# Copyright (c) 2018, 2019 Amine Ben Hassouna <amine.benhassouna@gmail.com>
#
# Permission is hereby granted, free of charge, to any
# person obtaining a copy of this software and associated
# documentation files (the "Software"), to deal in the
# Software without restriction, including without
# limitation the rights to use, copy, modify, merge,
# publish, distribute, sublicense, and/or sell copies of
# the Software, and to permit persons to whom the Software
# is furnished to do so, subject to the following
# conditions:
#
# The above copyright notice and this permission notice
# shall be included in all copies or substantial portions
# of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF
# ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
# TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
# PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT
# SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
# CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
# OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
# IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
# DEALINGS IN THE SOFTWARE.
#

# Define the project name
project(sdl2-ttf-sample)

# Set the cmake minimum version to 3.5.1
cmake_minimum_required(VERSION 3.5.1)

# Add SDL2 CMake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

# Add all c source files under the src directory
file(GLOB SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

# Add all headers files under the include directory
target_include_directories(${PROJECT_NAME} PRIVATE include)

# Add compiler errors/warnings flags
target_compile_options(${PROJECT_NAME} PRIVATE $<$<C_COMPILER_ID:MSVC>:/W4 /WX>)
target_compile_options(${PROJECT_NAME} PRIVATE $<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic -Werror>)


# Add SDL2 library
find_package(SDL2 REQUIRED)
target_link_libraries(${PROJECT_NAME} SDL2::Main)

# Add SDL2_image library
#find_package(SDL2_image REQUIRED)
#target_link_libraries(${PROJECT_NAME} SDL2::Image)

# Add SDL2_ttf library
find_package(SDL2_ttf REQUIRED)
target_link_libraries(${PROJECT_NAME} SDL2::TTF)

# Add SDL2_net library
#find_package(SDL2_net REQUIRED)
#target_link_libraries(${PROJECT_NAME} SDL2::Net)

# Add SDL2_mixer library
#find_package(SDL2_mixer REQUIRED)
#target_link_libraries(${PROJECT_NAME} SDL2::Mixer)

# Add SDL2_gfx library
#find_package(SDL2_gfx REQUIRED)
#target_link_libraries(${PROJECT_NAME} SDL2::GFX)

# Copy assets
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

file(GLOB test_SRCS tests/*.cpp
src/AxisBottomToTopL.cpp
src/AxisLeftToRightB.cpp
src/AxisLeftToRightT.cpp
src/AxisTopToBottomL.cpp
src/AxisFormat.cpp
src/City_Grid.cpp
src/CityFactory_Grid.cpp
src/CityState_Simple.cpp
src/Color.cpp
src/Converter.cpp
src/Coordinate.cpp
src/HappinessFunc_Falling.cpp
src/HappinessFunc_Flat.cpp
src/HappinessFunc_Rising.cpp
src/HappinessFunc_StepDown.cpp
src/HappinessFunc_StepUp.cpp
src/House.cpp
src/Letter.cpp
src/Manager.cpp
src/PlotFormat.cpp
src/PlotA.cpp
src/Question_Int.cpp
src/Question_Double.cpp
src/Question.cpp
src/Resident_UsingFunction.cpp
src/Renderer.cpp
src/Resident.cpp
src/Simulator_Basic_A.cpp
src/TextHelper.cpp
src/UI_CMDLine.cpp 
)

add_executable(RunTests ${test_SRCS})


