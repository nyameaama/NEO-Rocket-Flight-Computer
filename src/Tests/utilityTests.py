def beta(x):
    R1 = 90 - (-90) 
    R2 = 180 - 0
    temp1 = (x - (-90))
    translated_reading = temp1 * (R2 / R1) + 0
    return translated_reading

print(beta(90))