angleConversions = require("angleConversions")
require("lla2ecef")

function convertLocationToHLA ()

local lat = math.rad(DSimLocal.WorldLocation.X)
local lon = math.rad(DSimLocal.WorldLocation.Y)

DSimLocal.WorldLocation.X,DSimLocal.WorldLocation.Y,DSimLocal.WorldLocation.Z = lla2ecef(DSimLocal.WorldLocation.X,DSimLocal.WorldLocation.Y,DSimLocal.WorldLocation.Z)

local yaw = DSimLocal.Orientation.Psi-- heading
local pitch = DSimLocal.Orientation.Theta--pitch
local roll = DSimLocal.Orientation.Phi--roll

DSimLocal.Orientation.Theta = (angleConversions.getThetaFromTaitBryanAngles(lat, lon, yaw, pitch));
DSimLocal.Orientation.Phi = (angleConversions.getPhiFromTaitBryanAngles(lat, lon, yaw, pitch, roll))
DSimLocal.Orientation.Psi =  (angleConversions.getPsiFromTaitBryanAngles(lat, lon, yaw, pitch)) 
end