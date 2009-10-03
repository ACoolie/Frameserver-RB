#include "AVC.h"

static VALUE input_initialize(VALUE self, VALUE file) {
	AVFormatContext *formatContext;
	if(av_open_input_file(&formatContext, RSTRING_PTR(file), NULL, 0, NULL) != 0 || av_find_stream_info(formatContext) != 0) {
		fprintf(stderr, "Failed to open file \"%s\".", RSTRING_PTR(file));
		exit(-1);
	}
	DATA_PTR(self) = formatContext;
	int i = -1;
	while(i ++ < formatContext->nb_streams && formatContext->streams[i]->codec->codec_type != CODEC_TYPE_VIDEO) {}
	rb_iv_set(self, "@file", file);
	rb_iv_set(self, "@stream_id", INT2FIX(i));
	AVCodecContext *c = formatContext->streams[i]->codec;
	if(avcodec_open(c, avcodec_find_decoder(c->codec_id)) != 0) {
		fprintf(stderr, "Failed to open codec.");
		exit(-1);
	}
	return self;
}

static VALUE input_frame(VALUE self) {
	AVFormatContext *formatContext = NULL;
	Data_Get_Struct(self, AVFormatContext, formatContext);
	int stream_id = FIX2INT(rb_iv_get(self, "@stream_id"));
	AVPacket packet;
	av_init_packet(&packet);
	int finished = 0;
	AVCodecContext *c = formatContext->streams[stream_id]->codec;
	AVFrame *frame = avcodec_alloc_frame();
	av_read_frame(formatContext, &packet);
	while(!finished && av_read_frame(formatContext, &packet) >= 0) {
		if(packet.stream_index == stream_id)
			avcodec_decode_video2(formatContext->streams[stream_id]->codec, frame, &finished, &packet);
		av_free_packet(&packet);
	}
	return Data_Wrap_Struct(rb_avcframe, 0, frame_free, frame);
}

static VALUE input_seek(VALUE self, VALUE frame) {
	int c = FIX2INT(frame);
	while(c -- > 0) {
		input_frame(self);
	}
	return self;
}

static void input_free(AVFormatContext *formatContext) {
	av_free(formatContext);
}

static VALUE input_alloc(VALUE klass) {
	return Data_Wrap_Struct(klass, 0, input_free, NULL);
}

void Init_AVCInput() {
	rb_avcinput = rb_define_class_under(rb_avc, "Input", rb_cObject);
	rb_define_alloc_func(rb_avcinput, input_alloc);
	rb_define_method(rb_avcinput, "initialize", input_initialize, 1);
	rb_define_method(rb_avcinput, "frame", input_frame, 0);
	rb_define_method(rb_avcinput, "seek", input_seek, 1);
}