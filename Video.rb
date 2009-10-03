class Video < Filter
  attr_reader :width, :height
  def initialize(f)
    super(AVC::Input.new(f))
  end
end