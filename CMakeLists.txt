cmake_minimum_required(VERSION 3.10)

project(MyLibConfigProject)

# Настройка компилятора
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

# Добавляем директории заголовков GTK3
include_directories(${GTK3_INCLUDE_DIRS})

# Добавляем флаги компиляции GTK3
add_definitions(${GTK3_CFLAGS_OTHER})

# Поддержка Debug и Release версий
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_C_FLAGS_DEBUG "-g")
set(CMAKE_C_FLAGS_RELEASE "-O3")

# Если режим сборки Debug, экспортируем compile_commands.json
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()

# Подключение библиотеки libconfig
pkg_check_modules(LIBCONFIG REQUIRED IMPORTED_TARGET libconfig)
# Подключение библиотеки librsvg
pkg_check_modules(LIBRSVG REQUIRED IMPORTED_TARGET librsvg-2.0)

# Создание исполняемого файла
add_executable(main
  main.c
  main_window/main_window_init.h
  main_window/grid_widget.h
  led_widget/led_widget.h led_widget/led_widget.c
  structures/led.h structures/led.c
  structures/config.h structures/config.c

  interfaces/interface.c interfaces/interface.h
)

# Линковка библиотеки libconfig к нашему проекту
target_link_libraries(main PRIVATE PkgConfig::LIBCONFIG)
# Линковка библиотеки librsvg к нашему проекту
target_link_libraries(main PRIVATE PkgConfig::LIBRSVG)
# Связываем с библиотеками GTK3
target_link_libraries(main PRIVATE ${GTK3_LIBRARIES})

# Указываем директории для поиска библиотек во время выполнения
target_link_directories(main PUBLIC ${GTK3_LIBRARY_DIRS})

# # Копирование файла config.cfg в папку сборки
configure_file(${CMAKE_SOURCE_DIR}/config.cfg ${CMAKE_BINARY_DIR}/config.cfg COPYONLY)
