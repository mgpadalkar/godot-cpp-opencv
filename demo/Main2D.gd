extends Control


# Declare member variables here. Examples:
# var a = 2
# var b = "text"


# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass


func _on_Sprite_frame_updated(node, image):
	# pass # Replace with function body.
	var image_texture:ImageTexture = ImageTexture.new()
	image_texture.create_from_image(image)
	$webcamView.texture = image_texture
