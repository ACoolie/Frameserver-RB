#include "AVC.h"

static VALUE output_initialize(VALUE self, VALUE input) {
	AVFormatContext *f = NULL;
	AVCodecContext *c, *codecContext = NULL;
	Data_Get_Struct(self, AVCodecContext, codecContext);
	Data_Get_Struct(input, AVFormatContext, f);
	c = f->streams[FIX2INT(rb_iv_get(input, "@stream_id"))]->codec;
	avcodec_get_context_defaults2(codecContext, CODEC_TYPE_VIDEO);
	AVCodec *codec = avcodec_find_encoder(CODEC_ID_RAWVIDEO);
	codecContext->pix_fmt = PIX_FMT_YUV420P;
	codecContext->time_base = (AVRational){1,25};
	codecContext->width = c->width;
	codecContext->height = c->height;
	if(avcodec_open(codecContext, codec) != 0) {
		fprintf(stderr, "Failed to open codec.");
		exit(-1);
	}
	DATA_PTR(self) = codecContext;
	return self;
}

static VALUE output_encode_frame(VALUE self, VALUE frame) {
	AVCodecContext *codecContext = NULL;
	AVFrame *v = NULL;
	Data_Get_Struct(self, AVCodecContext, codecContext);
	Data_Get_Struct(frame, AVFrame, v);
	if(!v || !v->data[0]) {
		return Qfalse;
	}
	int bufsize = avpicture_get_size(codecContext->pix_fmt, codecContext->width, codecContext->height);
	uint8_t *buffer = malloc(bufsize);
	int size = avcodec_encode_video(codecContext, buffer, bufsize, v);
	fwrite(buffer, 1, size, stdout);
	free(buffer);
	return Qtrue;
}

static void output_free(AVCodecContext *codecContext) {
	av_free(codecContext);
}

static VALUE output_alloc(VALUE klass) {
	return Data_Wrap_Struct(klass, 0, output_free, avcodec_alloc_context());
}

void Init_AVCOutput() {
	rb_avcoutput = rb_define_class_under(rb_avc, "Output", rb_cObject);
	rb_define_alloc_func(rb_avcoutput, output_alloc);
	rb_define_method(rb_avcoutput, "initialize", output_initialize, 1);
	rb_define_method(rb_avcoutput, "encode_frame", output_encode_frame, 1);
}
