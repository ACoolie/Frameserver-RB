#include "AVC.h"

void Init_libAVC() {
	av_register_all();
	avcodec_register_all();
	rb_avc = rb_define_module("AVC");
	Init_AVCInput();
	Init_AVCFrame();
	Init_AVCOutput();
}