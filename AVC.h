#include <ruby.h>
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>

VALUE rb_avc, rb_avcinput, rb_avcframe, rb_avcoutput;
void Init_libAVC();
void Init_AVCInput();
void Init_AVCFrame();
void Init_AVCOuptut();

void frame_free(AVFrame *frame);