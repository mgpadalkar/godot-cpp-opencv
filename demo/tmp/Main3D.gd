extends Node3D

## Scene property
@export var scene : PackedScene: set = set_scene
var scene_node : Node

# Called when the node enters the scene tree for the first time.
func _ready():
	# pass # Replace with function body.
	var viewport = $SubViewportContainer/SubViewport
	var meshinstance = $MeshInstance3D
	init_screen_with_scene(meshinstance)
	init_viewport_with_scene(viewport)
#	viewport.set_clear_mode(SubViewport.CLEAR_MODE_ONCE)
	# meshinstance.material_override.albedo_texture = viewport.get_texture()
		


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass


## Set scene property
func set_scene(new_scene: PackedScene) -> void:
	scene = new_scene
	scene_node = scene.instantiate()
	add_child(scene_node) # add the scene as a child of the root node


func init_screen_with_scene(meshinstance: MeshInstance3D) -> void:
	if scene == null:
		return
	meshinstance.material_override.albedo_texture = scene_node.get_viewport().get_texture()


func init_viewport_with_scene(viewport: SubViewport):
	if scene == null:
		return
	viewport.set_clear_mode(SubViewport.CLEAR_MODE_ONCE)
#	# set the viewport size to the size of the scene
	var size = scene_node.get_window().get_visible_rect().size
	viewport.set_size(size)
