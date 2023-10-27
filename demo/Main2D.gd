extends CanvasLayer

var size_set = false
var frame_size : Vector2

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.



# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass


func _on_gd_open_cv_example_frame_updated(node, image):
	# pass # Replace with function body.
	var image_texture:ImageTexture = ImageTexture.new()
	image_texture.set_image(image)
	$webcamView.set_texture(image_texture)
	if not size_set:
		frame_size = image_texture.get_size()
		size_set = true
		get_viewport().set_size(frame_size)
