#!/bin/env ruby
if ARGV.empty?
  $stderr.puts 'Usage: %s source.rb > outfile.yuv' % [__FILE__]
  exit
end
require 'AVC'
require 'Filter'
require 'Video'
require ARGV[0] #!!!
i = $v
while i.source.class != AVC::Input
  i = i.source
end
e = AVC::Output.new(i.source)
t = Time.now
i = 0
while e.encode_frame($v.frame)
  i += 1
end
$stderr.puts "[fs] encoded %d frames. %ffps\n" % [i, i/(Time.now - t)]
