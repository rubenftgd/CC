%% INIT
Kp = 34.0683;
Ke = -4.2046;
sampling_time = 1/50; %0.02,50Hz ; for A/D, D/A
sampling_time_scope = 0.020; %sampling time for scopes
%%
load('identified_sys_model');


%% Regulator design LQR
% load('modelo_50hz.mat');

Q = C'*C;

%Parameter to be tested
vec_r = 0.1:0.1:1;
fit = zeros(1, length(vec_r));
LegendInfo = cell(length(vec_r)+1,1);
LegendInfo{length(vec_r)+1,1} = [];

for i=1:length(vec_r);
    R = vec_r(i); % AR part
    [K,S,E] = dlqr(A,B,Q,R);
%     fit(i) = th.Report.Fit.FitPercent;
    %SIMULATION
    sim('controller_test_lqr');
    figure (401)
        plot(simulation_data.time, simulation_data.signals.values(:,2),'linewidth', 0.1);
        hold on;
        LegendInfo{i} = sprintf('R = %.3f',vec_r(i));
%         fit(i)=mean(xcorr(simulation_data.signals.values(:,2),simulation_data.signals.values(:,1),'coeff'));
end

figure(401);
    plot(simulation_data.time, simulation_data.signals.values(:,1),'-k','linewidth', 0.1);
    LegendInfo{length(vec_r)+1} = sprintf('Ref');
    legend(LegendInfo);
    
    title('System response, for different R values');
    xlabel('k');
    ylabel('Total Bar deflection (?)???');
    axis([0 5 -0.1 1.55]);
%     
% figure(402);
%     plot(vec_r, fit);
%     xlabel('R');
    

%cheap vs expensive control
% R=0.410 ??????

%poles' positions
% ss2tf('controller_test_lqr')

%% Current estimator design LQE

% qe = 100;
RE = 1;
G = eye(size(A));


% Estimator implementation

vec_qe = 0.001:0.01:0.1;
% fit = zeros(1, length(vec_r));
LegendInfo2 = cell(length(vec_qe)+1,1);
LegendInfo2{length(vec_qe)+1,1} = [];

for i=1:length(vec_qe);
    QE = eye(size(A))*vec_qe(i);
    [Lc,P,Z,EE] = dlqe(A,G,C,QE,RE);
    PHIE = A-Lc*C*A;
    GAMMAE = B-Lc*C*B;
    CE = eye(size(PHIE));
    DE = zeros(size(CE,1),size(GAMMAE,2));
    %    fit(i) = th.Report.Fit.FitPercent;
    %SIMULATION
    sim('controller_test_lqe');
    figure (411)
        plot(simulation_data2.time, simulation_data2.signals.values(:,1),'linewidth', 0.1);
        hold on;
        LegendInfo2{i} = sprintf('Q_E = %.3f',vec_qe(i));
%         fit(i)=mean(xcorr(simulation_data.signals.values(:,2),simulation_data.signals.values(:,1),'coeff'));
end

figure(411);
    plot(simulation_data.time, simulation_data.signals.values(:,1),'-k','linewidth', 0.1);
    LegendInfo2{length(vec_qe)+1} = sprintf('Ref');
    legend(LegendInfo2);
    
    title('Estimation Error???, for different Q_E values');
    xlabel('k');
    ylabel('Total Bar deflection (?)???');
%     axis([0 5 -0.1 1.55]);

%%
% Externanl reference input
N = inv([A-eye(size(A)), B; C,0])*[zeros(size(A,1),1);1];
Nx = N(1:end-1,:);
Nu = N(end,:);
Nbar = Nu+K*Nx;

%% Simulation
%% Time Response

%% Frequency Response

%% Loop-Gain