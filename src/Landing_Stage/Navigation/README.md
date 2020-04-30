# Flight Navigation Module

## Guidance

* 



## Nav

* Nav creates path from one gps point to another


#### [IN DEVELOPMENT] Predicted Thrust Vectoring

* With the use of bluetooth, latency at any given point has to be compensated for. Predicted thrust vectoring computes the latency by piggybacking of other bluetooth traffic such as other system proceeses and returns the time it takes to transmit data between HC- 05 module and HC-06 module. This latency is then used by the PTV process to estimate the state and position of the rocket in the next (x) milliseconds. Where (x) is the latency computed beforehand. Gimbal position is then calculated for the predicted position and sent to the boost stage controller

