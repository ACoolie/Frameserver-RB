class Video < Filter
  attr_reader :width, :height
  def initialize(f)
    @source = AVC::Input.new(f)
    @width = @source.width
    @height = @source.height
  end
  def frame()
    @source.frame
  end
  def seek(frame)
    @source.seek(frame)
  end
  def trim(start, e)
    TrimFilter.new(self, start, e)
  end
end