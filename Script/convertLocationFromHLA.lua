angleConversions = require("angleConversions")
require("ecef2lla")

function convertLocationFromHLA ()
DSimLocal.WorldLocation.Y,DSimLocal.WorldLocation.X,DSimLocal.WorldLocation.Z = ecef2lla(DSimLocal.WorldLocation.X,DSimLocal.WorldLocation.Y,DSimLocal.WorldLocation.Z)

local lat = math.rad(DSimLocal.WorldLocation.Y)  --converting to rad because function requires rad
local lon = math.rad(DSimLocal.WorldLocation.X)

local psi =  DSimLocal.Orientation.Psi-- heading
local theta = DSimLocal.Orientation.Theta--pitch
local phi = DSimLocal.Orientation.Phi --roll

DSimLocal.Orientation.Psi =  angleConversions.getOrientationFromEuler(lat, lon, psi, theta)
DSimLocal.Orientation.Theta = angleConversions.getPitchFromEuler(lat, lon, psi, theta)
DSimLocal.Orientation.Phi = angleConversions.getRollFromEuler(lat, lon, psi, theta, phi)

end