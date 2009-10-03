class Video < Filter
  def initialize(f)
    @source = AVC::Input.new(f)
  end
  def frame()
    @source.frame
  end
  def seek(frame)
    @source.seek(frame)
  end
  def trim(start)
    TrimFilter.new(self, start)
  end
end