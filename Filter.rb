class Filter
  attr_reader :source, :width, :height
  def initialize(source)
    @source = source
    @width = source.width
    @height = source.height
  end
  def frame()
    @source.frame
  end
  def seek(frame)
    @source.seek(frame)
  end
  def duration()
    @source.duration
  end
end

class TrimFilter < Filter
  def initialize(source, start, e)
    super(source)
    @source.seek(start)
    @i = @d = e - start
  end
  def frame()
    if @i == 0
      return nil
    end
    @i -= 1
    @source.frame
  end
  def duration()
    @d
  end
end
Filter.class_eval do
  def trim(*a)
    TrimFilter.new(self, *a)
  end
end

class CropFilter < Filter
  def initialize(source, left, top, width, height)
    @source = source
    @left = left
    @top = top
    if width <= 0
      @width = @source.width + width - @left
    else
      @width = width
    end
    if height <= 0
      @height = @source.height + height - @top
    else
      @height = height
    end  end
  def frame()
    f = @source.frame
    if not f
      return nil
    end
    f.crop(@left, @top)
  end
end
Filter.class_eval do
  def crop(*a)
    CropFilter.new(self, *a)
  end
end

