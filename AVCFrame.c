#include "AVC.h"

void frame_free(AVFrame *frame) {
	av_free(frame);
}

static VALUE frame_crop(VALUE self, VALUE left, VALUE top) {
	AVFrame *frame = NULL;
	VALUE fc = rb_iv_get(self, "@__format_context");
	Data_Get_Struct(self, AVFrame, frame);
	AVFrame *f = avcodec_alloc_frame();
	int cl = FIX2INT(left);
	int ct = FIX2INT(top);
	av_picture_crop((AVPicture *)f, (AVPicture *)frame, PIX_FMT_YUV420P, ct, cl);
	av_free(frame);
	DATA_PTR(self) = f;
	return self;
}

void Init_AVCFrame() {
	rb_avcframe = rb_define_class_under(rb_avc, "Frame", rb_cObject);
	rb_define_method(rb_avcframe, "crop", frame_crop, 2);
}
