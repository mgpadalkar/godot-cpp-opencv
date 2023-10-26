extends Node3D

## Scene property
@export var scene : PackedScene: set = set_scene

var scene_node : Node

func _ready():
	init_custom_scene()
	# Clear the viewport.
	$SubViewport.set_clear_mode(SubViewport.CLEAR_MODE_ONCE)

	# Retrieve the texture and set it to the viewport quad.
	$ViewportQuad.material_override.albedo_texture = $SubViewport.get_texture()


## Set scene property
func set_scene(new_scene: PackedScene) -> void:
	scene = new_scene

## initialize the custom scene
func init_custom_scene():
	if scene == null:
		return
		
	scene_node = scene.instantiate()
	var viewport = $SubViewport
	
	# add the scene as a child of this viewport
	viewport.add_child(scene_node)
	
	# set the viewport size to the size of the scene
	var size = scene_node.get_window().get_visible_rect().size
	viewport.set_size(size)
