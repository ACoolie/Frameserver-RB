class Filter
  attr_reader :source
  def initialize(source)
    @source = source
  end
end

class TrimFilter < Filter
  def initialize(source, start)
    super(source)
    @source.seek(start)
  end
  def frame()
    @source.frame
  end
end