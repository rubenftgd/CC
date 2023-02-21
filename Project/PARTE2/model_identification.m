%%
% LOAD
Kp = 34.0683;
Ke = -4.2046;
%% SIGNAL DATA ACQUISITION
t = simdata.time; %assuming same sampling time for all variables


utrend = simdata.signals.values(:,1); % Entrada - Input signal
thetae = simdata.signals.values(:,2); % Potenciómetro - Potentiometer signal
alphae = simdata.signals.values(:,3); % Extensómetro - Starin gage signal

%%
t=t(1:5951);
utrend=utrend(1:5951);
thetae=thetae(1:5951);
alphae=alphae(1:5951);

%% Reconstrução ângulo total da barra – Computation of total bar angle
ytrend = thetae*Kp + alphae*Ke;


%% Plotting the signals
% change linewidth
% add titles, defined according tests
figure (201)
    subplot(3,1,1)
        plot(t, utrend,'linewidth', 0.1)
        xlabel('Time [s]');
        ylabel('u [V]');
        ylim ([-1.05 1.05]);
        xlim([0 t(length(t))]);
    subplot(3,1,2)
        plot(t, thetae,'linewidth', 0.1)
        xlabel('Time [s]');
        ylabel('\theta_e [V]');
        xlim([0 t(length(t))]);
    subplot(3,1,3)
        plot(t, alphae,'linewidth', 0.1)
        xlabel('Time [s]');
        ylabel('\alpha [V]');
        xlim([0 t(length(t))]);
        
figure(202)
    plot(t, ytrend,'linewidth', 0.1)
    ylabel('Total bar deflection [º]');
    xlabel('Time [s]');
    xlim([0 t(length(t))]);
% ytrend/ysim comparision?

%% Signal differentiation/filtration (LPF)

% For y
af = 0.8;
Afilt = [1 -af];
Bfilt = (1-af)*[1 -1];
% Filtragem seguida de eliminação de tendências
% Filtering and detrending
yf = filter(Bfilt,Afilt,ytrend);

figure(10)
plot(t, ytrend, 'linewidth',0.1)
hold on
plot(t,yf, '-g', 'linewidth', 0.1)
legend('ytrend','y detrended')

% % For alpha
% af2 = 0.4;
% 
% Afilt2 = [1 -af2];
% Bfilt2 = (1-af2)*[1 -1];
% alphae = filter(Bfilt2,Afilt2,alphae_trend);
% figure(11)
% plot(t, alphae_trend, 'linewidth',0.1)
% hold on
% plot(t,alphae, '-g', 'linewidth', 0.1)
% legend('alphae','alphae detrended')
% For u
% ONLY FOR HIGH OFFSET
u = dtrend(utrend);

% BURN??

%% Parameter identification
% length(u)-500 for square wave... fix code
z = [yf u]; %(1:length(u)-500) for old implementation of prbs
% na = 4; % AR part
% nb = 2; % X part
% nc = na; % MA part
% nk = 1; % Atraso puro – pure delay

na = 6; % AR part
nb = 2; % X part
nc = na; % MA part
nk = 1; % Atraso puro – pure delay

nn = [na nb nc nk];
th = armax(z,nn) % th is a structure in identification toolbox format
[den1,num1] = polydata(th);

%% System simulation with identified parameters
%yfsim = filter(num1,den1,u); % Equivalent to idsim(u,th);
% or
yfsim = idsim(u, th);
figure(211);
zplane(num1, den1);

% Checking simulation data
figure (212)
    plot(t, yf,'linewidth', 0.1);%nome??
    hold all;
    plot(t, yfsim, '-g','linewidth', 0.1);
    legend('Differentiated','Simulated');
    xlim([0 t(length(t))]);
    xlabel('Time [s]');
    ylabel('total differentiated angle [º]') %corrigir nome ?????
    title('Real vs Model') %????????
    
%% Measured error? - "simple" error, quadratic error?
error = mean(yf-yfsim)
% compare (yf, tf(num1, den1))
% COMPARE - identification toolbox
    
%% Adding the integrator
den = conv(den1, [1 -1]);
[num,den] = eqtflength(num1,conv(den1,[1 -1]));


% conversion to state model
[A,B,C,D] = tf2ss(num,den);

% CHECK
yestimate = dlsim(A,B,C,D,u);

% plot yestimate, recorded output
figure(221);
    plot(t, yestimate, t, ytrend)%, t, yestimate+ytrend(1));
% compare shape

%% simulation of the model, frequency response, ...


%% Save the matrices?
save(filename, 'A','B','C','D');