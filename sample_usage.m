Wr.wavelength = 458;%654.25 ;
Wr.theta = 0; % this line is actually inoperational; value is just to remember the propagation direction
Wr.polarization = 0;

Wg.wavelength = 654; %532.07;
Wg.polarization = 1;
Wg.theta = pi;  % this line is actually inoperational; value is just to remember the propagation direction

theta_vector=pi*(75:0.1:105)/180;

mr  = Calculate_m(25,Wr.wavelength, '2EG');
mg  = Calculate_m(25,Wg.wavelength, '2EG');

Ir = GeneratePattern(10000, mr, theta_vector, Wr);
Ig = GeneratePattern(10000, mg, theta_vector+pi, Wg);

plot(theta_vector, Ir, 'b');
hold on;
plot(theta_vector, Ig, 'r');
xlabel('scattering angle [rad]');
ylabel('scattered light intensity [arb.u.]');
title('Angular distribution of scattered light intensity for two wavelengths/polarisations');