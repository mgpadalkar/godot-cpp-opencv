extends Node3D

var xr_interface : XRInterface
var view_adjusted = false

# Called when the node enters the scene tree for the first time.
func _ready():
	# pass # Replace with function body.
	xr_interface = XRServer.find_interface("OpenXR")
	if xr_interface and xr_interface.is_initialized():
		print("OpenXR initialized successfully")
		# Turn off v-sync!
		DisplayServer.window_set_vsync_mode(DisplayServer.VSYNC_DISABLED)
		# Change our main viewport to output to the HMD
		get_viewport().use_xr = true
		get_viewport().transparent_bg = true
		print("Passthrough support: " + str(xr_interface.is_passthrough_supported()))
		return true
	else:
		print("OpenXR not initialized, please check if your headset is connected")
		return false


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	# pass
	if not view_adjusted:
		if $Main2D.size_set:
			adjust_the_view()
			view_adjusted = true


func adjust_the_view():
	var frame_size = $Main2D.frame_size
	var rendered_size = xr_interface.get_render_target_size()
	var scale = rendered_size / frame_size
	# scale the frame with respect to the rendering size
	$Main2D.scale = scale
	# scale the viewport to the rendering target size
	get_viewport().set_size(rendered_size)
