import time
#Simulation of change in altitude during ascent 

def PathSimulationMain():
    total_time = time.time()
    speed = 0
    time_between_path_point = 0.2
    Altitude = 0
    previousTime = time.time()
    while((time.time() - total_time) < 3.5):
        vehicleAcc = AccelerationInSetTime(time.time() - previousTime)
        #distance = vehicleAcc * (time.time() - previousTime) 
        previousTime = time.time()
        speed += vehicleAcc
        #Altitude += distance
        print(speed)
        


#Function to find acceleration of rocket in () time
def AccelerationInSetTime(seconds):
    rocketMass = 0.5 #kg
    engineThrust = 25.3
    engineThrustTime = 3.5 #secs

    rocket_Weight = rocketMass * 9.8
    resultant_force = engineThrust - rocket_Weight
    Acceleration = resultant_force / rocketMass
    return Acceleration * seconds

PathSimulationMain()
#print(AccelerationInSetTime(1))