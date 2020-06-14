count = 0

def AirspeedVal():
    return 9.8

#Function to find acceleration of rocket in () time
def AccelerationInSetTime(seconds):
    rocketMass = 1.0 #kg
    engineThrust = 25.3
    rocket_Weight = rocketMass * 9.8
    resultant_force = engineThrust - rocket_Weight
    Acceleration = resultant_force / rocketMass
    return Acceleration * seconds


#Function computes time (returns ms) propulsive acceleration will get vehicle to 1m/s
def calculatePropulsiveAccelerationTime():
    vel = AirspeedVal() 
    acc = AccelerationInSetTime(1)          #m/s
    pTime = vel / acc
    return pTime * 1000


#Function to compensate motor ignition delay to calculation
def compensateIgnitionDelay(altitude):
    IGNITION_DELAY = 0.258 #seconds
    revAlt = AirspeedVal() * IGNITION_DELAY
    revAlt = altitude + revAlt
    return revAlt


#Driver function
def propulsionAltitude():
    #To get the trigger altitude we use the time the motor takes to 
    #slow the vehicle down to 1 and add it to the terrain level
    #s * t
    #Altitude at landing area
    terrainGroundLevel = 2
    PAT = calculatePropulsiveAccelerationTime() / 1000
    #Current vel * Propulsive time to find distance
    tempDist = AirspeedVal() * PAT
    propulAlt = terrainGroundLevel + tempDist
    #Compensate for ignition delay
    propulAlt = compensateIgnitionDelay(propulAlt)
    return propulAlt

print(propulsionAltitude())