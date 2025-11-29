cmake_minimum_required(VERSION 3.30)
project(Evosnn2)

set(CMAKE_CXX_STANDARD 17)

# Set up Boost
# Check if primary path exists and is a directory
set(BOOST_POSSIBLE_PATH "/opt/homebrew/opt/boost/include")
set(FALLBACK_PATH "/usr/local/include/boost")


if(EXISTS "${BOOST_POSSIBLE_PATH}" AND IS_DIRECTORY "${BOOST_POSSIBLE_PATH}")
        set(Boost_INCLUDE_DIR "${BOOST_POSSIBLE_PATH}/include")
        set(Boost_INCLUDE_DIR "${BOOST_POSSIBLE_PATH}/lib")
else()
        set(Boost_INCLUDE_DIR "${FALLBACK_PATH}/include")
        set(Boost_INCLUDE_DIR "${FALLBACK_PATH}/lib")
endif()


# Find Boost
find_package(Boost REQUIRED COMPONENTS
    random)

include_directories(${Boost_INCLUDE_DIR})

# Add executable
add_executable(Evosnn2
        ComputationalUnit.cpp
        ComputationalUnit.h
        Evosnn.cpp
        Ga.cpp
        Ga.h
        Individual.cpp
        Individual.h
        Neuron.cpp
        Neuron.h
        Parameters.cpp
        Parameters.h
        resource.h
        targetver.h
        typedefs.cpp
        typedefs.h
        UtilityFunctions.cpp
        UtilityFunctions.h)

# Link Boost to the executable
# target_link_libraries(Evosnn2 ${Boost_LIBRARIES})
# Link against Boost targets
target_link_libraries(Evosnn2  PRIVATE
    Boost::random
)
# Include Boost headers
target_include_directories(Evosnn2 PRIVATE
    ${Boost_INCLUDE_DIRS}
)
