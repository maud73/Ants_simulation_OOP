cmake_minimum_required(VERSION 3.5)

project(Ant_Simulator_SSV_2021_Final)

#set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_FLAGS "-Wall")

set(TEST_DIR "${PROJECT_SOURCE_DIR}/Tests")
set(CACHE_DIR "${PROJECT_SOURCE_DIR}/../extlib/Catch/include")


include_directories(${PROJECT_SOURCE_DIR})
include_directories(${CACHE_DIR})
include_directories(${TEST_DIR})

file(GLOB UTILITY_SOURCES
     "${PROJECT_SOURCE_DIR}/Utility/*.cpp"
     "${PROJECT_SOURCE_DIR}/Utility/*.hpp"
     "${PROJECT_SOURCE_DIR}/JSON/*.cpp"
     "${PROJECT_SOURCE_DIR}/JSON/*.hpp"
     "${PROJECT_SOURCE_DIR}/Random/*.cpp"
     "${PROJECT_SOURCE_DIR}/Random/*.hpp"
     )
   

file(GLOB PROJECT_SOURCES
     "${PROJECT_SOURCE_DIR}/*.cpp"
     "${PROJECT_SOURCE_DIR}/*.hpp"    
      "${PROJECT_SOURCE_DIR}/Interface/*.hpp"
      "${PROJECT_SOURCE_DIR}/Stats/*.hpp"
      "${PROJECT_SOURCE_DIR}/Stats/*.cpp"
      "${PROJECT_SOURCE_DIR}/Environment/*.cpp"
      "${PROJECT_SOURCE_DIR}/Environment/*.hpp"
      ${UTILITY_SOURCES}
      )
    
file(GLOB SOURCES
     ${PROJECT_SOURCES}
)   


list(REMOVE_ITEM PROJECT_SOURCES "${PROJECT_SOURCE_DIR}/main.cpp")
   

file (GLOB CACHE_SOURCES
  "${CACHE_DIR}/catch.hpp"
   "${TEST_DIR}/UnitTests/CheckUtility.hpp"
   "${TEST_DIR}/UnitTests/CatchTests.cpp"
   #   ${SOURCES}
   ${UTILITY_SOURCES}
    )


file(GLOB SOURCES_GFX
         ${SOURCES}
)   
  
#add_executable (circularBodyTest  ${TEST_DIR}/UnitTests/CircularBodyTest.cpp ${CACHE_SOURCES})
############add_executable (ToricTest  ${TEST_DIR}/UnitTests/ToricTest.cpp ${CACHE_SOURCES})

add_custom_target(application-run
    COMMAND ./application
    DEPENDS application
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
# Find any version 2.X of SFML, first trying 2.5 or above (for which CMake configuration changed)
find_package(SFML 2.5 QUIET COMPONENTS graphics window system)
    if(SFML_FOUND)
      message(STATUS "Found SFML ${SFML_VERSION_MAJOR}.${SFML_VERSION_MINOR}.${SFML_VERSION_PATCH}")
      
      #main application:
      add_executable (application  ${TEST_DIR}/GraphicalTests/FinalApplication.cpp ${SOURCES_GFX})
      target_link_libraries(application sfml-graphics sfml-window sfml-system)
	
      #Units tests:
       add_executable (enemyTest  ${TEST_DIR}/UnitTests/EnemyTest.cpp ${SOURCES} ${CACHE_SOURCES})
      target_link_libraries(enemyTest sfml-graphics sfml-window sfml-system)
      add_executable (positionableTest  ${TEST_DIR}/UnitTests/PositionableTest.cpp ${SOURCES} ${CACHE_SOURCES})
      target_link_libraries(positionableTest sfml-graphics sfml-window sfml-system)
       add_executable (toricTest  ${TEST_DIR}/UnitTests/ToricTest.cpp ${SOURCES} ${CACHE_SOURCES})
      target_link_libraries(toricTest sfml-graphics sfml-window sfml-system)
      # add_executable (circularBodyTest  ${TEST_DIR}/UnitTests/CircularBodyTest.cpp ${CB_SOURCES} ${CACHE_SOURCES})
      # target_link_libraries(circularBodyTest sfml-graphics sfml-window sfml-system)
       add_executable (vec2dTest  ${TEST_DIR}/UnitTests/Vec2dTest.cpp ${SOURCES} ${CACHE_SOURCES})
       target_link_libraries(vec2dTest sfml-graphics sfml-window sfml-system)

      #Graphical tests:
       add_executable (anthillTest  ${TEST_DIR}/GraphicalTests/AnthillTest.cpp ${SOURCES_GFX})
       target_link_libraries(anthillTest sfml-graphics sfml-window sfml-system)

       add_executable (foodTest  ${TEST_DIR}/GraphicalTests/FoodTest.cpp ${SOURCES_GFX})
       target_link_libraries(foodTest sfml-graphics sfml-window sfml-system)
       
       add_executable (pheromoneTest  ${TEST_DIR}/GraphicalTests/PheromoneTest.cpp ${SOURCES_GFX})
       target_link_libraries(pheromoneTest sfml-graphics sfml-window sfml-system)
       
       add_executable (antTest  ${TEST_DIR}/GraphicalTests/AntTest.cpp ${SOURCES_GFX})
       target_link_libraries(antTest sfml-graphics sfml-window sfml-system)
       
       add_executable (termiteTest  ${TEST_DIR}/GraphicalTests/TermiteTest.cpp ${SOURCES_GFX})
       target_link_libraries(termiteTest sfml-graphics sfml-window sfml-system)
       
    else()
        set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
        find_package(SFML 2 COMPONENTS graphics window system)
        if(SFML_FOUND)

            message(STATUS "SFML_INCLUDE_DIR : ${SFML_INCLUDE_DIR}")
            message(STATUS "SFML_LIBRARIES   : ${SFML_LIBRARIES}")
            message(STATUS "SFML_DEPENDENCIES: ${SFML_DEPENDENCIES}")

            include_directories(${SFML_INCLUDE_DIR})
	    
	    #main application:
            add_executable(application ${TEST_DIR}/GraphicalTests/FinalApplication.cpp ${SOURCES_GFX})
            target_link_libraries(application ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

	    #Units tests:
	     add_executable (enemyTest ${TEST_DIR}/UnitTests/EnemyTest.cpp ${SOURCES} ${CACHE_SOURCES})
            target_link_libraries(enemyTest ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
	    add_executable (positionableTest ${TEST_DIR}/UnitTests/PositionableTest.cpp ${SOURCES} ${CACHE_SOURCES})
            target_link_libraries(positionableTest ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
	    add_executable (toricTest ${TEST_DIR}/UnitTests/ToricTest.cpp ${SOURCES} ${CACHE_SOURCES})
            target_link_libraries(toricTest ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
            # add_executable (circularBodyTest ${TEST_DIR}/UnitTests/CircularBodyTest.cpp ${CB_SOURCES} ${CACHE_SOURCES})
            # target_link_libraries(circularBodyTest ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
	     add_executable (vec2dTest ${TEST_DIR}/UnitTests/Vec2dTest.cpp ${SOURCES} ${CACHE_SOURCES})
             target_link_libraries(vec2dTest ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
	    
	    #Graphical tests:
	     add_executable(anthillTest ${TEST_DIR}/GraphicalTests/AnthillTest.cpp ${SOURCES_GFX})
             target_link_libraries(anthillTest ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

	     add_executable(foodTest ${TEST_DIR}/GraphicalTests/FoodTest.cpp ${SOURCES_GFX})
             target_link_libraries(foodTest ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
	     
	     add_executable(pheromoneTest ${TEST_DIR}/GraphicalTests/PheromoneTest.cpp ${SOURCES_GFX})
             target_link_libraries(pheromoneTest ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

	     add_executable(antTest ${TEST_DIR}/GraphicalTests/AntTest.cpp ${SOURCES_GFX})
             target_link_libraries(antTest ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

	     add_executable(termiteTest ${TEST_DIR}/GraphicalTests/TermiteTest.cpp ${SOURCES_GFX})
             target_link_libraries(termiteTest ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
        else()
            message(STATUS "SFML NOT FOUND ! ")
        endif() ## SFML 2
endif() ## SFML 2.5
