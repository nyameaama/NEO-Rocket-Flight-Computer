#Simulation of process from axis deviation to PID controller to thrust vectoring mount

def M1_translate(value):
    #values will be in the range of 0 - 90
    #but servo moves from 0 - 180 so numbers will have to
    #be scaled
    M2temp1 = 0
    M2_reading = 0            
    M2temp1 = value * 180
    M2_reading = M2temp1 / 90
    return M2_reading


def M2_translate(value):
    #values will be in the range of 0 - 90
	#but servo moves from 0 - 180 so numbers will have to
	#be scaled
    M2temp1 = 0
    M2_reading = 0
    M2temp1 = value * 180
    M2_reading = M2temp1 / 90
    return M2_reading


def PID(current,setpoint):
    kp = 0.5
    ki = 0.2
    kd = 0.1
    dt = 1
    error_integral = 0
    error_previous = 0
    processVar = current
    error = setpoint - processVar
    error_integral += error * dt
    derivative = (error - error_previous) / dt
    error_previous = error
    dv =  kd * derivative
    integral = ki * error_integral
    prop = kp * error
    result = prop + integral + derivative
    return result



def SimulationMain():
    testValues = [48,64,46]
    testSetpoints = [90,90,100]
    M1_translate(testValues[0])
    print(M1_translate(PID(testValues[0],testSetpoints[0])))
    print(PID(testValues[2],testSetpoints[2]))



SimulationMain()
