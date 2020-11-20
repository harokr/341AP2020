clear all
device = serialport("COM3", 9600)
flush(device)

n = 1000 %capure n data points at 5 ms delay
for i = 1:n
    Time(i) = .005 * i;
    SensorValues(i, 1:3) = read(device, 3, "uint8");
end
clear device
%plot here