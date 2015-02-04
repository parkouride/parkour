set(widgets_test_harness_SOURCES harness.cpp)
set(widgets_test_harness_HEADERS harness.h)
# QT4_WRAP_CPP(widgets_test_harness_HEADERS_MOC ${widgets_test_harness_HEADERS})

if (APPLE)
    set(widgets_test_harness_SOURCES ${widgets_test_harness_SOURCES} AppIcon.icns)
    set_source_files_properties(AppIcon.icns PROPERTIES
        MACOSX_PACKAGE_LOCATION Resources)
endif ()

ADD_EXECUTABLE(widgets_test_harness MACOSX_BUNDLE ${widgets_test_harness_SOURCES}
    ${widgets_test_harness_HEADERS}
    # ${widgets_test_harness_HEADERS_MOC}
    )
TARGET_LINK_LIBRARIES(widgets_test_harness widgets ${QT_LIBRARIES})
set(MACOSX_BUNDLE_BUNDLE_NAME "WidgetsTestHarness")
set(MACOSX_BUNDLE_BUNDLE_VERSION "${ledide_VERSION_MAJOR}.${ledide_VERSION_MINOR}")
set(MACOSX_BUNDLE_LONG_VERSION_STRING "${ledide_VERSION_MAJOR}.${ledide_VERSION_MINOR}")
set(MACOSX_BUNDLE_SHORT_VERSION_STRING "${ledide_VERSION_MAJOR}.${ledide_VERSION_MINOR}")
set(MACOSX_BUNDLE_COPYRIGHT "MIT Licensed")
set(MACOSX_BUNDLE_GUI_IDENTIFIER "io.stainless.ledide")
set(MACOSX_BUNDLE_ICON_FILE AppIcon.icns)

INSTALL_QT4_EXECUTABLE(${EXECUTABLE_PATH} "")
