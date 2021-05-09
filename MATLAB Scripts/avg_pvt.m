clear all
clc
pvt = load('avg_pvt.txt');
avgpower = pvt(1:12,1);
avgtemp = pvt(1:12,2);
plot(avgpower,avgtemp)
axis([0.5,5,35,100])
xlabel('Average power (watts)');
ylabel('Average temperature (degrees celcius)');
title('Average Power vs Average Temperature');