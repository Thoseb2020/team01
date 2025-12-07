cmake_minimum_required(VERSION 3.20)
project(ASC_ode)

set(CMAKE_CXX_STANDARD 20)

include_directories(src nanoblas/src)

add_subdirectory(src)
add_subdirectory(nanoblas)

add_compile_options(-fpermissive)

# ---- Your executables ----
add_executable(test_ode demos/test_ode.cpp)
target_link_libraries(test_ode PUBLIC nanoblas)

add_executable(test_rc demos/test_rc.cpp)
target_link_libraries(test_rc PUBLIC nanoblas)

add_executable(test_autodiff demos/test_autodiff.cpp)
target_link_libraries(test_autodiff PUBLIC nanoblas)

add_executable(test_pendulum_autodiff demos/test_pendulum_autodiff.cpp)
target_link_libraries(test_pendulum_autodiff PUBLIC nanoblas)

# ---- Newmark examples (from upstream) ----
add_executable(mass_spring demos/mass_spring.cpp)
target_link_libraries(mass_spring PUBLIC nanoblas)

add_executable(mass_spring_fem demos/mass_spring_fem.cpp)
target_link_libraries(mass_spring_fem PUBLIC nanoblas)

add_executable(test_newmark demos/test_newmark.cpp)
target_link_libraries(test_newmark PUBLIC nanoblas)
