

#include "HILibRtmpAPI.h"
#include "srs_librtmp.h"

#include <iostream>


int srs_librtmp_connect(srs_rtmp_t rtmp)
{
	if (srs_rtmp_handshake(rtmp) != 0) {
		srs_human_trace("simple handshake failed.");
		return RTMP_ERR_UNKNOWN;
	}
	srs_human_trace("simple handshake success");

	if (srs_rtmp_connect_app(rtmp) != 0) {
		srs_human_trace("connect vhost/app failed.");
		return RTMP_ERR_UNKNOWN;
	}
	srs_human_trace("connect vhost/app success");

	if (srs_rtmp_publish_stream(rtmp) != 0) {
		srs_human_trace("publish stream failed.");
		return RTMP_ERR_UNKNOWN;
	}
	srs_human_trace("publish stream success");

	return RTMP_ERR_SUCCESS;
}

HI_RTMP_API intptr_t  rtmp_api_client_open_stream(char* url, int publish, int flags, struct rtmp_handler_t* handler, intptr_t context)
{

	srs_rtmp_t rtmp = srs_rtmp_create("rtmp://10.55.16.111:1935/head/04006e8ba423b544c9d4");
	if (rtmp)
	{
		
		if (RTMP_ERR_SUCCESS== srs_librtmp_connect(rtmp))
		{
			return (intptr_t)rtmp;
		}
		srs_rtmp_destroy(rtmp);
	}
	return 0;
}

HI_RTMP_API int rtmp_api_client_input(intptr_t handle, int streamid, const void* packet, size_t bytes, uint64_t time, int flags)
{
	if (RTMP_STREAM_VIDEO_H264== streamid)
	{
		return  srs_h264_write_raw_frames((srs_rtmp_t)handle, (char*)packet, bytes, time, time);
	} 
	else
	{	// 0 = Linear PCM, platform endian
		// 1 = ADPCM
		// 2 = MP3
		// 7 = G.711 A-law logarithmic PCM
		// 8 = G.711 mu-law logarithmic PCM
		// 10 = AAC
		// 11 = Speex
		char sound_format = 10;
		// 2 = 22 kHz
		char sound_rate = 2;
		// 1 = 16-bit samples
		char sound_size = 1;
		// 1 = Stereo sound
		char sound_type = 1;

		 return srs_audio_write_raw_frame((srs_rtmp_t)handle, sound_format, sound_rate, sound_size, sound_type, (char*)packet, bytes, time);

		//return  srs_h264_write_raw_frames((srs_rtmp_t)handle, (char*)packet, bytes, time, time);
	}
	return 0;
}