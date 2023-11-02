extends CanvasLayer

var size_set = false
var frame_size : Vector2
var texture_left : ImageTexture = ImageTexture.new()
var texture_right : ImageTexture = ImageTexture.new()

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.



# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass


func _on_gd_open_cv_example_frame_updated(node, image_array):
	# pass # Replace with function body.
	
	# get left-right images
	var img_left : Image
	var img_right : Image
	# send same image to both eyes if only 1 is received
	if (image_array.size() == 1):
		image_array.push_back(image_array[0])  # same image
		# image_array.push_back(get_icon_image(image_array[0]))  # a default different image
	texture_left.set_image(image_array[0])
	texture_right.set_image(image_array[1])
		
	# get combined
	var combined = get_combined(image_array[0], image_array[1])
	var webcam_texture = ImageTexture.new()
	webcam_texture.set_image(combined)
	$webcamView.set_texture(webcam_texture)
	
	# set the size
	if not size_set:
		frame_size = texture_left.get_size()
		var view_size = webcam_texture.get_size()
		size_set = true
		get_viewport().set_size(view_size)


func get_combined(img1 : Image, img2 : Image):
	var x1 = img1.get_size().x
	var y1 = img1.get_size().y
	var x2 = img2.get_size().x
	var y2 = img2.get_size().y
	var combined = Image.create(x1+x2, y1, false, img1.get_format())
	combined.blit_rect(img1, Rect2(Vector2(0, 0), Vector2(x1, y1)), Vector2(0, 0))
	combined.blit_rect(img2, Rect2(Vector2(0, 0), Vector2(x2, y2)), Vector2(x1, 0))
	return combined


func get_icon_image(img : Image):
	var size = img.get_size()
	var icon_image = load("res://icon.svg").get_image()
	icon_image.resize(size.x, size.y)
	icon_image.convert(img.get_format())
	return icon_image
