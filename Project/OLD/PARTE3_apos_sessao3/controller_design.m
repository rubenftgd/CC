%% INIT
Kp = 34.0683;
Ke = -4.2046;
sampling_time = 1/50; %0.02,50Hz ; for A/D, D/A
sampling_time_scope = 0.020; %sampling time for scopes
%%
load('identified_sys_model');

%% Regulator design LQR

Q = C'*C;

%Parameter to be tested
vec_r = 300:50:500;
LegendInfo = cell(length(vec_r),1);
LegendInfo{length(vec_r),1} = [];

for i=1:length(vec_r);
    R = vec_r(i); % AR part
    [K,S,E] = dlqr(A,B,Q,R);
    %SIMULATION
    sim('controller_test_lqr');
    figure (401)
        subplot(2,1,1);
        plot(simulation_data.time, simulation_data.signals.values(:,2),'linewidth', 0.1);
        hold on;
        LegendInfo{i} = sprintf('R = %.3f',vec_r(i));
end

figure(401);
    title('System response, for different R values');
    ylabel('Total Bar deflection [º]');
    subplot(2,1,1)
        legend(LegendInfo);
        ylim([-1 24]);
        xlim([0 20]);
    subplot(2,1,2)
        plot(simulation_data.time, simulation_data.signals.values(:,1),'linewidth', 0.1);
        xlim([0 20]);
        ylabel('System Input [V]');
        xlabel('k');
    
%%
%cheap vs expensive control
%poles' positions
% ss2tf('controller_test_lqr')

%% Current estimator design LQE

RE = 1;
G = eye(size(A));

% Estimator implementation
vec_qe = 100:100:1000;
LegendInfo2 = cell(length(vec_qe),1);
LegendInfo2{length(vec_qe),1} = [];

for i=1:length(vec_qe);
    QE = eye(size(A))*vec_qe(i);
    [Lc,P,Z,EE] = dlqe(A,G,C,QE,RE);
    %SIMULATION
    sim('controller_test_lqe');
    figure (411)
        subplot(2,1,1);
            plot(simulation_data2.time, simulation_data2.signals.values(:,1),...
                 'linewidth', 0.1);
            hold on;
            LegendInfo2{i} = sprintf('Q_E = %.3f',vec_qe(i));
end

figure(411);
    subplot(2,1,1)
        legend(LegendInfo2);
        title('Estimation Error, for different Q_E values');
        ylabel('Estimation Error [º]');
        %ylim([-1 24]);
        xlim([0 3]);
    subplot(2,1,2)
        plot(simulation_data.time, simulation_data.signals.values(:,1),...
             'linewidth', 0.1);
        xlim([0 3]);
        xlabel('k');
        ylabel('System Input [V]');
%%

%% Current estimator design LQE - SCALAR Q_E

RE = 1;
G = B;

vec_qe = 1:10:101;
LegendInfo4 = cell(length(vec_qe),1);
LegendInfo4{length(vec_qe),1} = [];

for i=1:length(vec_qe);
    QE = vec_qe(i);
    [Lc,P,Z,EE] = dlqe(A,G,C,QE,RE);
    %SIMULATION
    sim('controller_test_lqe');
    figure (441)
        subplot(2,1,1);
            plot(simulation_data2.time, simulation_data2.signals.values(:,1),...
                 'linewidth', 0.1);
            hold on;
            LegendInfo4{i} = sprintf('Q_E = %.3f',vec_qe(i));
end

figure(441);
    subplot(2,1,1);
        legend(LegendInfo4);
        title('Estimation Error, for different Q_E values');
        ylabel('Estimation Error [º]');
        xlim([0 3]);
    subplot(2,1,2);
        plot(simulation_data.time, simulation_data.signals.values(:,1),...
             'linewidth', 0.1);
        xlabel('k');
        xlim([0 3]);
        ylabel('System Input [V]');

%% Q_E fixed, RE as tuning knob

QE = 100;
G = B;

vec_re = 0.1:01:10;
LegendInfo3 = cell(length(vec_re)+1,1);
LegendInfo3{length(vec_re)+1,1} = [];

for i=1:length(vec_re);
    RE = vec_re(i);
    [Lc,P,Z,EE] = dlqe(A,G,C,QE,RE);
    %SIMULATION
    sim('controller_test_lqe');
    figure (421)
        plot(simulation_data2.time, simulation_data2.signals.values(:,1),'linewidth', 0.1);
        hold on;
        LegendInfo3{i} = sprintf('R_E = %.3f',vec_re(i));
end

figure(421);
    plot(simulation_data.time, simulation_data.signals.values(:,1),'-k','linewidth', 0.1);
    LegendInfo3{length(vec_re)+1} = sprintf('Ref');
    legend(LegendInfo3);
    
    title('Estimation Error, for different R_E values');
    xlabel('k');
    ylabel('Error');


%% Agregated system
%LQR
R=400;
[K,S,E] = dlqr(A,B,(C'*C),R);
% LQE
% Current estimator design
w2 = 100;
QE = eye(size(A))*w2;
RE = 0.8;
G = eye(size(A));
[M,P,Z,EE] = dlqe(A,G,C,QE,RE);



% Externanl reference input
N = inv([A-eye(size(A)), B; C,0])*[zeros(size(A,1),1);1];
Nx = N(1:end-1,:);
Nu = N(end,:);
Nbar = Nu+K*Nx;


%% Simulation
%% Time Response

%% Frequency Response

%% Loop-Gain