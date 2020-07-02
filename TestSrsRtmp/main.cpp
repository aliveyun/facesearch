#include <stdio.h>
#include <string.h>

#pragma comment (lib,"ws2_32.lib")

#include <iostream>
#include "srs_librtmp.h"
//#include "srs_kernel_codec.h"
#include "../HIFfReadAPI/include/HIFfReadAPI.h"

void* gRtmp = nullptr;
bool start = false;
// https://github.com/ossrs/srs/issues/212#issuecomment-64145910
int read_audio_frame(char* data, int size, char** pp, char** frame, int* frame_size)
{
	char* p = *pp;

	// @remark, for this demo, to publish aac raw file to SRS,
	// we search the adts frame from the buffer which cached the aac data.
	// please get aac adts raw data from device, it always a encoded frame.
	if (!srs_aac_is_adts(p, size - (p - data))) {
		srs_human_trace("aac adts raw data invalid.");
		return -1;
	}

	// @see srs_audio_write_raw_frame
	// each frame prefixed aac adts header, '1111 1111 1111'B, that is 0xFFF.,
	// for instance, frame = FF F1 5C 80 13 A0 FC 00 D0 33 83 E8 5B
	*frame = p;
	// skip some data.
	// @remark, user donot need to do this.
	p += srs_aac_adts_frame_size(p, size - (p - data));

	*pp = p;
	*frame_size = p - *frame;
	if (*frame_size <= 0) {
		srs_human_trace("aac adts raw data invalid.");
		return -1;
	}

	return 0;
}

int srs_librtmp_audio_push(srs_rtmp_t rtmp, char* audio_raw, off_t file_size, double fps)
{
	int dts = 0;
	int pts = 0;
	// @remark, to decode the file.
	char* p = audio_raw;
	int count = 0;
	//while(1){
	for (; p < audio_raw + file_size;) {
		// @remark, read a frame from file buffer.
		char* data = NULL;
		int size = 0;
		int nb_start_code = 0;
		if (read_audio_frame(audio_raw, file_size, &p, &data, &size) < 0) {
			srs_human_trace("read a frame from file buffer failed.");
			return -1;
		}
		dts = pts = fps;

		// 0 = Linear PCM, platform endian
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

		// send out the h264 packet over RTMP
		int  ret = srs_audio_write_raw_frame(rtmp, sound_format, sound_rate, sound_size, sound_type, data, size, dts);
		if (ret != 0) {
			srs_human_trace("send audio raw data failed. ret=%d", ret);
			return -1;
		}




	}
	srs_human_trace("h264 raw data completed");
	p = audio_raw;
	//}

	return 0;


}
int read_h264_frame(char* data, int size, char** pp, int* pnb_start_code, int fps,
	char** frame, int* frame_size, int* dts, int* pts)
{
	char* p = *pp;

	// @remark, for this demo, to publish h264 raw file to SRS,
	// we search the h264 frame from the buffer which cached the h264 data.
	// please get h264 raw data from device, it always a encoded frame.
	if (!srs_h264_startswith_annexb(p, size - (p - data), pnb_start_code)) {
		srs_human_trace("h264 raw data invalid.");
		return -1;
	}

	// @see srs_write_h264_raw_frames
	// each frame prefixed h.264 annexb header, by N[00] 00 00 01, where N>=0,
	// for instance, frame = header(00 00 00 01) + payload(67 42 80 29 95 A0 14 01 6E 40)
	*frame = p;
	p += *pnb_start_code;

	for (;p < data + size; p++) {
		if (srs_h264_startswith_annexb(p, size - (p - data), NULL)) {
			break;
		}
	}

	*pp = p;
	*frame_size = p - *frame;
	if (*frame_size <= 0) {
		srs_human_trace("h264 raw data invalid.");
		return -1;
	}

	// @remark, please get the dts and pts from device,
	// we assume there is no B frame, and the fps can guess the fps and dts,
	// while the dts and pts must read from encode lib or device.
	if (fps!=0)
	*dts += 1000 / fps;
	*pts = *dts;

	return 0;
}
int srs_librtmp_push(srs_rtmp_t rtmp, char* h264_raw, off_t file_size, double fps)
{
	int dts = 0;
	int pts = 0;
	// @remark, to decode the file.
	char* p = h264_raw;
	int count = 0;
	//while(1){
	for (; p < h264_raw + file_size;) {
		// @remark, read a frame from file buffer.
		char* data = NULL;
		int size = 0;
		int nb_start_code = 0;
		if (read_h264_frame(h264_raw, (int)file_size, &p, &nb_start_code, fps, &data, &size, &dts, &pts) < 0) {
			srs_human_trace("read a frame from file buffer failed.");
			return -1;
		}
		dts = pts = fps;
		// send out the h264 packet over RTMP
		int ret = srs_h264_write_raw_frames(rtmp, data, size, dts, pts);
		if (ret != 0) {
			if (srs_h264_is_dvbsp_error(ret)) {
				srs_human_trace("ignore drop video error, code=%d", ret);
			}
			else if (srs_h264_is_duplicated_sps_error(ret)) {
				srs_human_trace("ignore duplicated sps, code=%d", ret);
			}
			else if (srs_h264_is_duplicated_pps_error(ret)) {
				srs_human_trace("ignore duplicated pps, code=%d", ret);
			}
			else {
				srs_human_trace("send h264 raw data failed. ret=%d", ret);
				return -1;
			}
		}

		// 5bits, 7.3.1 NAL unit syntax,
		// H.264-AVC-ISO_IEC_14496-10.pdf, page 44.
		//  7: SPS, 8: PPS, 5: I Frame, 1: P Frame, 9: AUD, 6: SEI
		u_int8_t nut = (char)data[nb_start_code] & 0x1f;
		srs_human_trace("sent packet: type=%s, time=%d, size=%d, fps=%.2f, b[%d]=%#x(%s)",
			srs_human_flv_tag_type2string(SRS_RTMP_TYPE_VIDEO), dts, size, fps, nb_start_code, (char)data[nb_start_code],
			(nut == 7 ? "SPS" : (nut == 8 ? "PPS" : (nut == 5 ? "I" : (nut == 1 ? "P" : (nut == 9 ? "AUD" : (nut == 6 ? "SEI" : "Unknown")))))));

		// @remark, when use encode device, it not need to sleep.
		/*if (count++ == 9) {
			usleep(1000 * 1000 * count / fps);
			count = 0;
		}*/
	}
	srs_human_trace("h264 raw data completed");
	p = h264_raw;
	//}

	return 0;
}
static void v_packet_cb(intptr_t param, int streamid, const void* packet, size_t bytes, int w, int h, uint64_t time, int flags, int extra)
{
	//time = time * 1000;
	//if (extra)
	//	srs_rtmp_write_packet(gRtmp, SRS_RTMP_TYPE_SCRIPT, time, (char*)packet, bytes);
	//	//srs_h264_write_raw_frames(gRtmp, (char*)"000000016742802995A014016E400000000168CE3880", strlen("000000016742802995A014016E400000000168CE3880"), time, time);
	//int ret = 0;


	int b=srs_librtmp_push(gRtmp, (char*)packet, bytes, time);
	if (b!=0)
	{
		printf("kkkk\n");
	}
	//ret = srs_h264_write_raw_frames(gRtmp, (char*)packet, bytes, time, time);
	//srs_rtmp_write_packet(gRtmp, SRS_RTMP_TYPE_VIDEO, time, (char*)packet, bytes);
	//printf("1111\n");

}

int srs_librtmp_connect(srs_rtmp_t rtmp)
{
	if (srs_rtmp_handshake(rtmp) != 0) {
		srs_human_trace("simple handshake failed.");
		return -1;
	}
	srs_human_trace("simple handshake success");

	if (srs_rtmp_connect_app(rtmp) != 0) {
		srs_human_trace("connect vhost/app failed.");
		return -1;
	}
	srs_human_trace("connect vhost/app success");

	if (srs_rtmp_publish_stream(rtmp) != 0) {
		srs_human_trace("publish stream failed.");
		return -1;
	}
	srs_human_trace("publish stream success");

	return 0;
}

int main(int argc, char *argv[])
{

	/*gRtmp = srs_rtmp_create("rtmp://10.55.16.111:1935/head/04006e8ba423b544c9d4");
	srs_rtmp_handshake(gRtmp);

	srs_rtmp_connect_app(gRtmp);
	srs_rtmp_publish_stream(gRtmp);*/

	gRtmp = srs_rtmp_create("rtmp://10.55.16.111:1935/head/04006e8ba423b544c9d4");
	srs_librtmp_connect(gRtmp);
	struct ffmpeg_handler_t h;
	memset(&h, 0, sizeof(struct ffmpeg_handler_t));
	h.onvideo = v_packet_cb;
	//h.onerror = e_onerror;
	intptr_t handle = ffmpg_api_open_stream((char*)"rtsp://192.168.138.120/mpeg4", HI_PIXEL_FMT_SRC, 0, 0, &h, (intptr_t)111);
	ffmpg_api_start_stream(handle);

	start = true;
	for (;;)
	{
		
	
	
		//LOG_PRINT(LOG_INFO, "gatewayserver is run %d day %02d:%02d:%02d", day, hour, minute, second);
	
		//OSThread::Sleep(sleep_sec * 1000);
		Sleep(5 * 1000);
	}
	std::system("pause \n");


}
