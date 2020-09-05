angleConversions = require("angleConversions")
require("lla2ecef")

lastLat = 0;
lastLong = 0;
lastAlt = 0;

function convertLocationToDIS()
lastLat = DSimLocal.Y;
lastLong = DSimLocal.X;
lastAlt = DSimLocal.Z;

--convert lat/long to geocentric
DSimLocal.X, DSimLocal.Y,DSimLocal.Z = lla2ecef(lastLat, lastLong,lastAlt)

end