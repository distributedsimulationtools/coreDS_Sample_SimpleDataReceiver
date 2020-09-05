angleConversions = require("angleConversions")
require("lla2ecef")

function convertAngleFromDIS()
local lat = math.rad(lastReceivedLat)
local lon = math.rad(lastReceivedLong)

local yaw = angleConversions.getOrientationFromEuler(lat, lon, DSimLocal.Psi , DSimLocal.Theta)
local pitch = angleConversions.getPitchFromEuler(lat, lon, DSimLocal.Psi , DSimLocal.Theta)
local roll = angleConversions.getRollFromEuler(lat, lon, DSimLocal.Psi, DSimLocal.Theta, DSimLocal.Phi)

DSimLocal.Psi = yaw
DSimLocal.Theta = pitch
DSimLocal.Phi = roll
end