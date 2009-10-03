#include "AVC.h"

void frame_free(AVFrame *frame) {
	av_free(frame);
}

void Init_AVCFrame() {
	rb_avcframe = rb_define_class_under(rb_avc, "Frame", rb_cObject);
}
