import time
#Simulation

def PathSimulationMain():
    speed = 0
    time_between_path_point = 0.2
    time1 = time.time()
    Altitude = 1
    while((time.time() - time1) < 3.5):
        vehicleAcc = AccelerationInSetTime(time.time() - time1)
        speed += vehicleAcc
        distanceFromSurface = speed * time.time()
        print(distanceFromSurface)


#Function to find acceleration of rocket in () time
def AccelerationInSetTime(seconds):
    rocketMass = 2 #kg
    engineThrust = 25.3
    engineThrustTime = 3.5 #secs

    rocket_Weight = rocketMass * 9.8
    resultant_force = engineThrust - rocket_Weight
    Acceleration = resultant_force / rocketMass
    return Acceleration * seconds

PathSimulationMain()