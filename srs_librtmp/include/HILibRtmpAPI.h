#ifndef _HI_RTMP_API_H
#define _HI_RTMP_API_H

#include <stdint.h>
#include <stdlib.h>

#ifdef WIN32
#ifdef HI_RTMP_API_EXPORTS
#define HI_RTMP_API extern "C"  __declspec(dllexport) 
#else 
#define HI_RTMP_API extern "C"  __declspec(dllimport) 
#endif
//#else
//#define HI_RTMP_API
#elif defined(__linux__) || defined(__APPLE__) //linux
#define HI_RTMP_API extern "C"
#endif



#define  HI_RTMP_REF (12345678)
#define  HI_RTMP_DES_REF (87654321)

#ifdef WIN32
#pragma warning(disable:4005 4099 4251 4508 4101 4700 4244 4267 4200 4312 4010 4091 4616 4311 4018 4482 4305 4129 4065 4805 4114 4060 4819 4996 )
#endif

#define RTMP_ERR_SUCCESS             1
#define RTMP_ERR_UNKNOWN             0

enum
{
NET_DISCONNECT	= 0x01,
NET_RECONNECT	= 0x02,
NET_CONNECT  	= 0x03,
NET_DESTROYNET = 0x04,
};


enum RTMP_AVPACKET_CODEC_ID
{
	RTMP_STREAM_AVCODEC_NONE = 0x00,
	RTMP_STREAM_VIDEO_MPEG2,
	RTMP_STREAM_VIDEO_MPEG4,
	RTMP_STREAM_VIDEO_H264,
	RTMP_STREAM_VIDEO_H265,
	RTMP_STREAM_VIDEO_VP8,
	RTMP_STREAM_VIDEO_VP9,

	RTMP_STREAM_VIDEO_YUV,
	RTMP_STREAM_VIDEO_RGB,
	RTMP_STREAM_IMAGE_PNG = 0x100,
	RTMP_STREAM_IMAGE_GIF,
	RTMP_STREAM_IMAGE_BMP,
	RTMP_STREAM_IMAGE_JPEG,

	RTMP_STREAM_AUDIO_PCM = 0x10000,
	RTMP_STREAM_AUDIO_SVAC,
	RTMP_STREAM_AUDIO_G711A,
	RTMP_STREAM_AUDIO_G711U,
	RTMP_STREAM_AUDIO_G722,
	RTMP_STREAM_AUDIO_G723,
	RTMP_STREAM_AUDIO_G726,
	RTMP_STREAM_AUDIO_G729,
	RTMP_STREAM_AUDIO_MP3,
	RTMP_STREAM_AUDIO_AAC,
	RTMP_STREAM_AUDIO_AC3,
	RTMP_STREAM_AUDIO_OPUS,
	RTMP_STREAM_AUDIO_MP2, // MPEG-2 Layer II
};

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#ifndef INOUT
#define INOUT
#endif


struct rtmp_handler_t
{
	void(*onconnect)(intptr_t param, int code);
	void (*onerror)(intptr_t param, int code);
	void (*ondestroy)(intptr_t param);
	void (*onmsg)(intptr_t param, int msgid, const void* packet, size_t bytes, uint64_t time);
	void (*onvideo)(intptr_t param, int streamid, const void* packet, size_t bytes, int w, int h, uint64_t time, int flags, int extra);
	void (*onaudeo)(intptr_t param, int streamid, const void* packet, size_t bytes, int channel, int bits_per_sample, int sample_rate, uint64_t time, int flags, int extra);
};


//typedef int (*rtmp_packet_cb)(intptr_t param, int streamid, const void *packet, size_t bytes, uint64_t time, int flags);
//typedef int (*rtmp_msg_cb)(intptr_t param, int msgid,const void *packet, size_t bytes, uint64_t time);
HI_RTMP_API long  rtmp_api_client_init(void); //
///@param[in] publish, 0-Publish(push stream to server), 1-LIVE/VOD(pull from server), 2-LIVE only, 3-VOD only
/// @param[in] flags 0-aio, 1-block io
///@return 
HI_RTMP_API intptr_t  rtmp_api_client_open_stream(char *url, int publish , int flags, struct rtmp_handler_t* handler, intptr_t context);
HI_RTMP_API long  rtmp_api_client_start_stream(intptr_t handle);
HI_RTMP_API long  rtmp_api_client_close_stream(intptr_t handle);

/*****************************************************************************************************

******************************************************************************************************/
HI_RTMP_API long  rtmp_api_setreconnect(IN intptr_t handle ,IN long dwInterval, IN long dwMaxTimes);

HI_RTMP_API int rtmp_api_client_pause(intptr_t handle, int pause); // VOD only
HI_RTMP_API int rtmp_api_client_seek(intptr_t handle, int64_t timestamp , float fRelativePos); // VOD only

///@return RTMP_STATE_START(4): push video/audio
HI_RTMP_API int rtmp_api_client_getstate(intptr_t handle);

HI_RTMP_API int rtmp_api_client_input(intptr_t handle , int streamid, const void *packet, size_t bytes, uint64_t time, int flags);
HI_RTMP_API void rtmp_api_client_destroy( );

#endif