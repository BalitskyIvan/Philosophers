cmake_minimum_required(VERSION 3.17)
project(Philosophers C)

set(CMAKE_C_STANDARD 11)

include_directories(philo_one)

add_executable(Philosophers
    philo_one/detach.c
    philo_one/ft_itoa.c
    philo_one/initializer.c
    philo_one/main.c
    philo_one/philo.h
    philo_one/utils.c)
