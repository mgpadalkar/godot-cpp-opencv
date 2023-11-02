extends Node3D

@export var scene : PackedScene : set = set_scene
var scene_node : Node
var all_set = false

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	# pass
	if not all_set and scene_node and scene_node.size_set:
		var my_shader = $Screen.mesh.surface_get_material(0)
		var texture_left  = scene_node.texture_left
		var texture_right = scene_node.texture_right
		my_shader.set_shader_parameter("texture_left", texture_left)
		my_shader.set_shader_parameter("texture_right", texture_right)
		all_set = true


func set_scene(new_scene: PackedScene) -> void:
	scene = new_scene
	scene_node = scene.instantiate()
	$SubViewport.add_child(scene_node)
	$SubViewport.render_target_update_mode = SubViewport.UPDATE_ONCE
