extends Node2D


# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass


func _on_gd_example_position_changed(node, new_pos):
	# pass # Replace with function body.
	print("The position of " + node.get_class() + " is now " + str(new_pos))
