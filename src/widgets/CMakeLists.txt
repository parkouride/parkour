set(widgets_SOURCE src/box_widget.cpp
                   src/canvas.cpp
    )
set(widgets_HEADER include/box_widget.h
                   include/canvas.h
    )
set(widgets_HEADER_QT )
set(widgets_RESOURCES )

# Fix up files for QT
QT4_WRAP_CPP(widgets_HEADER_MOC ${widgets_HEADER_QT})
QT4_ADD_RESOURCES(widgets_RESOURCES_RCC ${widgets_RESOURCES})

add_library(widgets STATIC ${widgets_SOURCE}
                           ${widgets_HEADER}
                           ${widgets_HEADER_QT}
                           ${widgets_HEADER_MOC}
                           ${widgets_RESOURCES_RCC})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR} include)

add_subdirectory(test_harness)
