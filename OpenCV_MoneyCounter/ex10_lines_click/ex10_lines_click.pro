QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp


INCLUDEPATH += F:/OpenCV-QT/mybuild/install/include
LIBS += -LF:\\OpenCV-QT\\mybuild\\bin \
libopencv_core2411d \
libopencv_calib3d2411d \
libopencv_contrib2411d \
libopencv_flann2411d \
libopencv_gpu2411d \
libopencv_highgui2411d \
libopencv_imgproc2411d \
libopencv_legacy2411d \
libopencv_ml2411d \
libopencv_nonfree2411d \
libopencv_objdetect2411d \
libopencv_ocl2411d \
libopencv_photo2411d \
libopencv_stitching2411d \
libopencv_superres2411d \
libopencv_video2411d \
libopencv_videostab2411d \
libopencv_features2d2411d \
