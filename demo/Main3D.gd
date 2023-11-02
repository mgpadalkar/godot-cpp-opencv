extends Node3D

var xr_interface : XRInterface

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
		return true
	else:
		print("OpenXR not initialized, please check if your headset is connected")
		return false


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass
