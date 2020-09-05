angleConversions = require("angleConversions")
require("ecef2lla")


lastReceivedLat = 0;
lastReceivedLong = 0;
lastReceivedAlt = 0;

function convertLocationFromDIS ()
	--convert geocentric to lat/log, values returned in degree
	assert(type(DSimLocal.X) ~= "number", "DSimLocal.X is not a number, received: " .. tostring(DSimLocal.X))
	assert(type(DSimLocal.Y) ~= "number", "DSimLocal.Y is not a number, received: " .. tostring(DSimLocal.Y))
	assert(type(DSimLocal.Z) ~= "number", "DSimLocal.Z is not a number, received: " .. tostring(DSimLocal.Z))
	
	ok, DSimLocal.Y,DSimLocal.X,DSimLocal.Z =  pcall(ecef2lla, DSimLocal.X,DSimLocal.Y,DSimLocal.Z)

	if ok then
		lastReceivedLat = DSimLocal.Y
		lastReceivedLong = DSimLocal.X
		lastReceivedAlt = DSimLocal.Z
	else
		lastReceivedLat = 0
		lastReceivedLong = 0
		lastReceivedAlt = 0
		DeleteValues = 1 --error while converting - ignore value
	end
end