#!/bin/env ruby
banner = 'Usage: %s source.rb > out.yuv' % [__FILE__]

require 'optparse'
require 'AVC'
require 'Filter'
require 'Video'

options = {}
OptionParser.new do |opts|
  opts.banner = banner
  opts.on("-i", "--info", "Show track info") do
    options[:info] = true
  end
end.parse!
if ARGV.empty?
  $stderr.puts banner
  exit(-1)
end
require ARGV[0]
v = main()
if options[:info]
  $stderr.puts '[fs] Size: %dx%d' % [v.width, v.height]
  $stderr.puts '[fs] Frames: %d' % v.duration
  exit(0)
end
e = AVC::Output.new(v)
t = Time.now
i = 0
while e.encode_frame(v.frame)
  i += 1
end
$stderr.puts "[fs] encoded %d frames, %ffps, %dx%d\n" % [i, i/(Time.now - t), v.width, v.height]
