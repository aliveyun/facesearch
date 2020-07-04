#cmake_minimum_required(VERSION 2.8.0)
cmake_minimum_required(VERSION 3.6)
set(PROJECT_NAME HIPlayCtrlAPI)
project(${PROJECT_NAME})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11 -frtti -Wall -Wno-literal-suffix -D__linux__=1 -O3 -W  -Os -fpic -fPIC")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O2 -fPIC")
#CPPFLAGS += -fPIC
add_definitions(-DOS_LINUX)
add_definitions(-D__linux__)
add_definitions(-D_HAVE_FFMPEG_)
#add_definitions(-D_SEMAPHORE_H)
include_directories(
      include
	  meida
     ../HILibSDK/include
	 ../HILibAio/include
	 ../HILibRtmpAPI/include
	 ../HILibSDK/include
	 ../include/ffmpeg
	 ../HIAvcodeSDK/include
	 ../HIFfReadAPI/include
  
	#../HILibFlv/include	
	#../HILibMov/include
	 #../include/ffmpeg
	# ../HILibSDK/include
	 #../HILibSDK/include
)
#head file path，头文件目录
# INCLUDE_DIRECTORIES(
 #include
#)
#set(LD_LIBRARY_PATH $LD_LIBRARY_PATH:${PROJECT_SOURCE_DIR}/libs)
#file(GLOB SRC_LIST "*.c" "*.cpp")

set(SRC_LIST
     src/HIPlayCtrlAPI.cpp
    src/avplayer.cpp
    src/AVPlayerCore.cpp
	 src/AVPlayerCore.cpp
	 src/PlayStream.cpp
	 meida/ffmpeg_Filesource.cpp
	 meida/ffmpeg_Livesource.cpp
	 meida/rtmp_source.cpp
	 
	#../HILibFlv/source/mpeg4-aac.c
   #  ../HILibAio/src/aio-accept.c
	#../HILibAio/src/aio-client.c
	#../HILibAio/src/aio-recv.c
	#../HILibAio/src/aio-rwutil.c
	#../HILibAio/src/aio-send.c
	#../HILibAio/src/aio-tcp-transport.c
	#../HILibAio/src/aio-timeout.c
	#../HILibAio/src/aio-worker.c


)


#link_libraries(/usr/lib/FFmpeg/libavcodec.so)
#link_libraries(/usr/lib/FFmpeg/libswresample.so)
#link_libraries(/usr/lib/FFmpeg/libavdevice.so)
#link_libraries(/usr/lib/FFmpeg/libavformat.so)
#link_libraries(/usr/lib/FFmpeg/libavutil.so)
#link_libraries(/usr/lib/FFmpeg/libavfilter.so)
#link_libraries(/usr/lib/FFmpeg/libpostproc.so)
#link_libraries(/usr/lib/FFmpeg/libswscale.so)

#add link library，添加可执行文件所需要的库，比如我们用到了libm.so（命名规则：lib+name+.so），就添加该库的名称
#TARGET_LINK_LIBRARIES(${PROJECT_NAME} m)
ADD_LIBRARY(HIPlayCtrlAPI SHARED ${SRC_LIST} )
#ADD_LIBRARY(HIRtmpAPI_static STATIC ${SRC_LIST} )

#SET_TARGET_PROPERTIES(HIRtmpAPI_static PROPERTIES OUTPUT_NAME "HIRtmpAPI")
#SET_TARGET_PROPERTIES(HIRtmpAPI PROPERTIES CLEAN_DIRECT_OUTPUT 1)
#SET_TARGET_PROPERTIES(HIRtmpAPI_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)



link_directories(${PROJECT_SOURCE_DIR}../lib/)
target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/../HILibSDK/build/libHILibSDK.a) 
target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/../HILibAio/build/libHILibAio.a) 
target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/../HILibFlv/build/libHILibFlv.a) 
target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/../HILibAio/build/libHILibAio.a) 

target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/../HIAvcodeSDK/build/libHIAvcodeSDK.so) 
target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/../HIFfReadAPI/build/libHIFfReadAPI.so) 
target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/../HILibRtmpAPI/build/libHILibRtmpAPI.so) 


target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/../lib/linux/ffmpeg/libswscale.so) 
target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/../lib/linux/ffmpeg/libswresample.so) 
target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/../lib/linux/ffmpeg/libavcodec.so) 
target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/../lib/linux/ffmpeg/libavfilter.so) 
target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/../lib/linux/ffmpeg/libavdevice.so) 
target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/../lib/linux/ffmpeg/libavformat.so) 
target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/../lib/linux/ffmpeg/libavutil.so) 
target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/../lib/linux/ffmpeg/libpostproc.so) 
target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/../faad2-2.8.8/build/lib/libfaad.a)



#link_directories(${PROJECT_SOURCE_DIR})
#target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/ /usr/lib/FFmpeg/libpostproc.so) 
#target_link_libraries(${PROJECT_NAME} /usr/lib/FFmpeg/libswscale.so) 
#target_link_libraries(${PROJECT_NAME} /usr/lib/FFmpeg/libswresample.so) 
#target_link_libraries(${PROJECT_NAME} /usr/lib/FFmpeg/libavcodec.so) 
#target_link_libraries(${PROJECT_NAME} /usr/lib/FFmpeg/libavfilter.so) 
#target_link_libraries(${PROJECT_NAME} /usr/lib/FFmpeg/libavdevice.so) 
#target_link_libraries(${PROJECT_NAME} /usr/lib/FFmpeg/libavformat.so) 
#target_link_libraries(${PROJECT_NAME} /usr/lib/FFmpeg/libavutil.so) 
#target_link_libraries(${PROJECT_NAME} /usr/lib/FFmpeg/libpostproc.so) 



#link_directories(${PROJECT_SOURCE_DIR}../lib/)
#target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/../HILibSDK/build/libHILibSDK.a) 
#target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/../HILibMpeg/build/libHILibMpeg.a) 
#target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/../HILibFlv/build/libHILibFlv.a) 
#target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/../HILibAio/build/libHILibAio.a) 
#target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/../HILibRtmp/build/libHILibRtmp.a) 


#link_directories(${PROJECT_SOURCE_DIR}/../lib/)
#target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/../HILibSDK/build/libHILibSDK.a) 
#target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/../HILibAio/build/libHILibAio.a) 
#target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/../HILibFlv/build/libHILibFlv.a) 
#target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/../HILibAio/build/libHILibAio.a) 

#target_link_libraries(${PROJECT_NAME} ${CMAKE_LIBRARY_PATH}/FFmpeg/libavcodec.so) 
#target_link_libraries(${PROJECT_NAME} ${CMAKE_LIBRARY_PATH}/FFmpeg/libswresample.so) 
#target_link_libraries(${PROJECT_NAME} ${CMAKE_LIBRARY_PATH}/FFmpeg/libavdevice.so) 
#target_link_libraries(${PROJECT_NAME} ${CMAKE_LIBRARY_PATH}/FFmpeg/libavformat.so) 
#target_link_libraries(${PROJECT_NAME} ${CMAKE_LIBRARY_PATH}/FFmpeg/libavutil.so) 
#target_link_libraries(${PROJECT_NAME} ${CMAKE_LIBRARY_PATH}/FFmpeg/libavfilter.so) 
#target_link_libraries(${PROJECT_NAME} ${CMAKE_LIBRARY_PATH}/FFmpeg/libpostproc.so) 
#target_link_libraries(${PROJECT_NAME} ${CMAKE_LIBRARY_PATH}/FFmpeg/libswscale.so) 



#link_libraries(/usr/lib/FFmpeg/libavcodec.so)
#link_libraries(/usr/lib/FFmpeg/libswresample.so)
#link_libraries(/usr/lib/FFmpeg/libavdevice.so)
#link_libraries(/usr/lib/FFmpeg/libavformat.so)
#link_libraries(/usr/lib/FFmpeg/libavutil.so)
#link_libraries(/usr/lib/FFmpeg/libavfilter.so)
#link_libraries(/usr/lib/FFmpeg/libpostproc.so)
#link_libraries(/usr/lib/FFmpeg/libswscale.so)

#link_directories(/usr/lib/FFmpeg)
#find_package(libavcodec.so)
#find_library(SERIALDEVICE_LIB libavcodec.so)
#target_link_libraries(${PROJECTNAME} libavcodec.so)

#target_link_libraries(${PROJECTNAME} libavcodec.so) 
#target_link_libraries(${PROJECTNAME} libswresample.so) 
#target_link_libraries(${PROJECTNAME} libavdevice.so) 
#target_link_libraries(${PROJECTNAME} libavformat.so) 
#target_link_libraries(${PROJECTNAME} libavutil.so) 
#target_link_libraries(${PROJECTNAME} libpostproc.so) 
#target_link_libraries(${PROJECTNAME} libavfilter.so) 
#target_link_libraries(${PROJECTNAME} libswscale.so) 
#target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/../lib/linux/ffmpeg/libavcodec.so) 
#target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/../lib/linux/ffmpeg/libswresample.so) 
#target_link_libraries(${PROJECT_NAME} /mnt/d/svn/HI/TestFfReadAPI/../lib/linux/ffmpeg/libswresample.so) 
#target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/../lib/linux/ffmpeg/libavdevice.so) 
#target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/../lib/linux/ffmpeg/libavformat.so) 
#target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/../lib/linux/ffmpeg/libavutil.so) 
#target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/../lib/linux/ffmpeg/libpostproc.so) 
#target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/../lib/linux/ffmpeg/libavfilter.so) 
#target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/../lib/linux/ffmpeg/libswscale.so) 

#link_libraries(/home/liaojianke/facedetect/THFace/Face-SDK-Linux64/Face-SDK-Linux64/bin/libTHFaceImage.so)

#link_directories( ${PROJECT_SOURCE_DIR}../lib/linux/ffmpeg/
#${PROJECT_SOURCE_DIR}..//lib/linux/ffmpeg
#${PROJECT_SOURCE_DIR}..//HILibFlv/build
#${PROJECT_SOURCE_DIR}..//HILibAio/build
#)
#target_link_libraries(${PROJECT_NAME}  libHILibSDK.a libHILibFlv.a libHILibAio.a libpostproc.so libavfilter.so libswscale.so libavcodec.so libswresample.so libavdevice.so libavformat.so libavutil.so pthread dl rt)

#target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/../faad2-2.8.8/build/lib/libfaad.a)
 
#target_link_libraries(HIPlayMediaSDK ${PROJECT_SOURCE_DIR}/../HILibFlv/build/libHILibFlv.a) 
#target_link_libraries(HIPlayMediaSDK ${PROJECT_SOURCE_DIR}/../HILibAio/build/libHILibAio.a) 
#target_link_libraries(HIPlayMediaSDK ${PROJECT_SOURCE_DIR}/../HILibRtmp/build/libHILibRtmp.a) 
#LINK_DIRECTORIES(/usr/local/cuda-8.0/lib64)
#LINK_DIRECTORIES(/usr/local/cuda-8.0/lib64)



#add_library(${PROJECT_NAME}
#	 SHARED
	# ir_plugin_interface.cpp
#	 dotini_parser.cpp
#)
#TARGET_LINK_LIBRARIES(${PROJECT_NAME} -lpthread -lz -lstdc++ -ldeepface -lmxnet -lsgai -lsgmx)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} -lpthread -lstdc++ )

