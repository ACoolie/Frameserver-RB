class Filter
  attr_reader :source, :width, :height
  def initialize(source)
    @source = source
    @width = source.width
    @height = source.height
  end
end

class TrimFilter < Filter
  def initialize(source, start, e)
    super(source)
    @source.seek(start)
    @i = e-start
  end
  def frame()
    if @i == 0
      return nil
    end
    @i -= 1
    @source.frame
  end
end