close all;
clear all;

x_min = -10;
x_max = 10;
N = 1001;
SNR = 15;

a = 1.75; b = -0.8; c = -2.5;

x = linspace(x_min, x_max, N);
y = a * exp(-((x - b)/c).^2);
yy = awgn(y, SNR);
plot(x, y, 'b'); hold on; plot(x, yy, 'r');
csvwrite('gaussian_x.h', x)
csvwrite('gaussian_y.h', yy)
