#include <opencv2/opencv.hpp>
#include <string>
#include <thread>
extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
#include <libavdevice/avdevice.h>
}
#include <iostream>
using namespace std;
int main() {
    std::cout << "begin capture" << std::endl; // delete l8r
    cv::VideoCapture cap("C:\\www\\town0.avi"); // Open the video file
    AVFormatContext *formatContext = nullptr;
    const AVOutputFormat *outputFormat = av_guess_format("hls", NULL, NULL);
    string playlist_name = "C:\\hlsco\\playlist.m3u8";
    avformat_alloc_output_context2(&formatContext, outputFormat,
              NULL, playlist_name.c_str());
    AVDictionary *options = NULL;
    av_dict_set(&options, "hls_time", "5", 0); // Set segment duration to 10 seconds
    av_dict_set(&options, "hls_base_url", "http://localhost:8080/hls/", 0);
    av_dict_set(&options, "segment_format", "mpegts", 0);
    av_dict_set(&options, "segment_list_type", "m3u8", 0);
    av_dict_set(&options, "segment_list", playlist_name.c_str(), 0);
    av_dict_set_int(&options, "segment_list_size", 0, 0);
    av_dict
    _set(&options, "segment_time_delta", "1.0", 0);
    av_dict_set(&options, "segment_time", "5.0", 0);
    av_dict_set(&options, "segment_list_flags", "cache+live", 0);
    AVStream *stream = avformat_new_stream(formatContext, NULL);
    const AVCodec *codec = avcodec_find_encoder(AV_CODEC_ID_H264);
    AVCodecContext *codecContext = avcodec_alloc_context3(codec);
    codecContext->width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    codecContext->height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    codecContext->time_base = av_make_q(1, 25);
    codecContext->framerate = av_make_q(25, 1);
    codecContext->pix_fmt = AV_PIX_FMT_YUV420P;
    codecContext->codec_id = AV_CODEC_ID_H264;
    codecContext->codec_type = AVMEDIA_TYPE_VIDEO;
    avcodec_open2(codecContext, codec, NULL);
    avcodec_parameters_from_context(stream->codecpar, codecContext);
    avformat_write_header(formatContext, &options);
    cv::Mat frame;
    AVFrame *avFrame = av_frame_alloc();
    avFrame->format = AV_PIX_FMT_YUV420P;
    avFrame->width = codecContext->width;
    avFrame->height = codecContext->height;
    av_frame_get_buffer(avFrame, 0);
    struct SwsContext *swsContext = sws_getContext(
        codecContext->width, codecContext->height, AV_PIX_FMT_BGR24,
        codecContext->width, codecContext->height, AV_PIX_FMT_YUV420P,
        SWS_BILINEAR, NULL, NULL, NULL
    );
    int frameCounter = 0;
    int frameRate = 25; // Frame rate of the output video
    while (true) {
        if (!cap.read(frame)) {
            break;
        }
        uint8_t *data[1] = {(uint8_t *)frame.data};
        int linesize[1] = {3 * frame.cols};
        sws_scale(swsContext, data, linesize, 0,
                   frame.rows, avFrame->data, avFrame->linesize);
        avFrame->pts = frameCounter * (formatContext->streams[0]->time_base.den) / frameRate;
        AVPacket pkt;
        av_init_packet(&pkt);
        pkt.data = NULL;
        pkt.size = 0;
        if (avcodec_send_frame(codecContext, avFrame) == 0) {
            if (avcodec_receive_packet(codecContext, &pkt) == 0) {
                av_interleaved_write_frame(formatContext, &pkt);
                av_packet_unref(&pkt);
            }
        }
        frameCounter++;
    }
    av_write_trailer(formatContext);
    av_frame_free(&avFrame);
    avcodec_free_context(&codecContext);
    avio_closep(&formatContext->pb);
    avformat_free_context(formatContext);
    return 0;
}