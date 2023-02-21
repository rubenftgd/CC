%% Signal acquisition
Kp = 34.0683;
Ke = -4.2046;
sampling_time = 1/50; %0.02,50Hz ; for A/D, D/A
sampling_time_scope = 0.020; %sampling time for scopes
filename = 'test_xyz.mat'; %for saving matrices A,B,C,D
%% system simulation
%% input generation
duration = 170;
t = (0:sampling_time:duration)';
%% square
input_amplitude = 1; %about 1V
input_frequency = 0.5; %Hz
u = input_amplitude*square(2*pi*input_frequency*t);

%% sawtooth
input_amplitude = 1; %about 1V
input_frequency = 1; %Hz
u = input_amplitude*sawtooth(2*pi*input_frequency*t);

%% motor dead zone
input_amplitude = 1; %about 1V
input_frequency = 0.5; %Hz
u = 0.05*t;

%% PRBS
B = 0.11;
u = idinput(length(t)+500,'PRBS',[0 B]);
%%
%truncar primeiros 10s
% u = u(1:length(t));
u = u(501:length(u));
t = t(1:length(u));%?
stoptime = t(length(t));
%% simulation
% obtain simdata

%% Save the matrices?
% save(filename, 'A','B','C','D');