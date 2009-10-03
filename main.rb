#!/bin/env ruby
require 'AVC'
require 'Filter'
require 'Video'
require 'source'
i = $v
while i.source.class != AVC::Input
  i = i.source
end
e = AVC::Output.new(i.source)
t = Time.now
i = 35
i.times {
  puts e.encode_frame($v.frame)
}
$stderr.puts "\n[fs] %ffps\n" % (i/(Time.now - t))
