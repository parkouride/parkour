set(widgets_SOURCE src/box_widget.cpp)
set(widgets_HEADER include/box_widget.h)
set(widgets_RESOURCES )

# Fix up files for QT
QT4_WRAP_CPP(widgets_HEADER_MOC ${widgets_HEADER})
QT4_ADD_RESOURCES(widgets_RESOURCES_RCC ${widgets_RESOURCES})

add_library(widgets OBJECT ${widgets_SOURCE}
                           ${widgets_HEADER_MOC}
                           ${widgets_RESOURCES_RCC})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR} include)

