clear all
clc
maxtemp = load('maxtemp.txt');
temp = maxtemp(1:15000,1);
time_ms = maxtemp(1:15000,3);
time = (time_ms-5000)/1000;
plot(time,temp)
time_axis = linspace(0,540,60);
axis([0,550,0,100]);
title('Temperature vs Time');
xlabel('Time (seconds)');
ylabel('Temperature (degrees celcius)');