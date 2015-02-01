set(widgets_test_harness_SOURCES harness.cpp)
set(widgets_test_harness_HEADERS harness.h)
# QT4_WRAP_CPP(widgets_test_harness_HEADERS_MOC ${widgets_test_harness_HEADERS})

ADD_EXECUTABLE(widgets_test_harness ${widgets_test_harness_SOURCES}
    # ${widgets_test_harness_HEADERS_MOC}
    )
TARGET_LINK_LIBRARIES(widgets_test_harness widgets ${QT_LIBRARIES})
