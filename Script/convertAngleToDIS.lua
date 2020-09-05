angleConversions = require("angleConversions")
require("lla2ecef")

function convertAngleToDIS()
	local lat = math.rad(lastLat)
	local lon = math.rad(lastLong)

	local yaw = DSimLocal.Psi-- heading
	local pitch = DSimLocal.Theta--pitch
	local roll = DSimLocal.Phi--roll

	DSimLocal.Theta = (angleConversions.getThetaFromTaitBryanAngles(lat, lon, yaw, pitch));
	DSimLocal.Phi = (angleConversions.getPhiFromTaitBryanAngles(lat, lon, yaw, pitch, roll))
	DSimLocal.Psi =  (angleConversions.getPsiFromTaitBryanAngles(lat, lon, yaw, pitch)) 
end