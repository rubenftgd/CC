%%
% LOAD
Kp = 34.0683;
Ke = -4.2046;
%% SIGNAL DATA ACQUISITION
t = simdata.time; %assuming same sampling time for all variables

utrend = simdata.signals.values(:,1); % Entrada - Input signal
thetae = simdata.signals.values(:,2); % Potenciómetro - Potentiometer signal
alphae = simdata.signals.values(:,3); % Extensómetro - Starin gage signal


% Reconstrução ângulo total da barra – Computation of total bar angle
ytrend = thetae*Kp + alphae*Ke;

%% Plotting the signals
% change linewidth
% add titles, defined according tests
figure (101)
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
        
figure(102)
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

figure(110)
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
z = [yf u];

%% Effect of ARMAX coefficients - na, nc
nb = 2; % X part
nk = 1; % Atraso puro – pure delay

%Parameter to be tested
vec_na = [4 6 8 12];

fit = zeros(1, length(vec_na));
mse = zeros(1, length(vec_na));
loss = zeros(1, length(vec_na));
fpe = zeros(1, length(vec_na));
LegendInfo = cell(length(vec_na),1);
LegendInfo{length(vec_na),1} = [];

figure (202)
    plot(t, yf,'-.','linewidth', 1);%nome??
    LegendInfo{1} = 'Differentiated';
    hold all;



for i=1:length(vec_na);
    na = vec_na(i); % AR part
    nc = na; % MA part
    nn = [na nb nc nk];
    th = armax(z,nn); % th is a structure in identification toolbox format
%     [den1,num1] = polydata(th);
    fit(i) = th.Report.Fit.FitPercent;
    mse(i) = th.Report.Fit.MSE;
    loss(i) = th.Report.Fit.LossFcn;
    fpe(i) = th.Report.Fit.FPE;
    %SIMULATION
    yfsim = idsim(u, th);
%     figure(201);
%     zplane(num1, den1);
%     hold on;
    % Checking simulation data
    figure (202)
        plot(t, yfsim,'linewidth', 0.1);
        LegendInfo{i+1} = sprintf('n_a = %f',vec_na(i));
end
legend(LegendInfo);

figure(202);
    xlabel('Time [s]');
    ylabel('total differentiated angle [º]'); %corrigir nome ?????
    title('Real vs Model'); %????????
    xlim([10 11.1]);%t(length(t))]);
    ylim([-9 9]);
   
figure(203);
    plot(vec_na, fit,'--',vec_na, (diff([eps; fit(:)])./diff([eps; vec_na(:)]))',...
         vec_na,zeros(1,length(vec_na)),'--g',vec_na,95*ones(1,length(vec_na)),'--r',...
         vec_na,92.5*ones(1,length(vec_na)),'--r');
    title('Fit %, for different n_a values + derivative');
    xlabel('n_a');
    ylabel('%');
    axis([0 vec_na(length(vec_na)) -2 100]);
figure(204);
    plot(vec_na, mse,'--',vec_na,(diff([eps; mse(:)])./diff([eps; vec_na(:)]))',...
         vec_na,zeros(1,length(vec_na)),'--g');
    title('MSE, for different n_a values + derivative');
    xlabel('n_a');
    ylabel('MSE');
     axis([0 vec_na(length(vec_na)) -1 1]);
figure(205);
    plot(vec_na, fpe,'--',vec_na,(diff([eps; mse(:)])./diff([eps; vec_na(:)]))',...
         vec_na,zeros(1,length(vec_na)),'--g');
    title('FPE, for different n_a values + derivative');
    xlabel('n_a');
    ylabel('FPE');
     axis([0 vec_na(length(vec_na)) -1 1]);
figure(206);
    plot(vec_na, loss,'--',vec_na,(diff([eps; loss(:)])./diff([eps; vec_na(:)]))',...
         vec_na,zeros(1,length(vec_na)),'--g');
    title('LossFcn, for different n_a values + derivative');
    xlabel('n_a');
    ylabel('Loss');
    axis([0 vec_na(length(vec_na)) -1 1]);

%% Effect of ARMAX coefficients - nb
na = 6;
nc = na;
nk = 1; % Atraso puro – pure delay

%Parameter to be tested
vec_nb = 1:1:4;

fit = zeros(1, length(vec_nb));
mse = zeros(1, length(vec_nb));
loss = zeros(1, length(vec_nb));
fpe = zeros(1, length(vec_nb));
LegendInfo_2 = cell(length(vec_nb),1);
LegendInfo_2{length(vec_nb),1} = [];

figure (211)
    plot(t, yf,'-.','linewidth', 1);%nome??
    LegendInfo_2{1} = 'Differentiated';
    hold all;



for i=1:length(vec_nb);
    nb = vec_nb(i); % AR part
    nn = [na nb nc nk];
    th = armax(z,nn); % th is a structure in identification toolbox format
%     [den1,num1] = polydata(th);
    fit(i) = th.Report.Fit.FitPercent;
    mse(i) = th.Report.Fit.MSE;
    loss(i) = th.Report.Fit.LossFcn;
    fpe(i) = th.Report.Fit.FPE;
    %SIMULATION
    yfsim = idsim(u, th);
%     figure(201);
%     zplane(num1, den1);
%     hold on;
    % Checking simulation data
    figure (211)
        plot(t, yfsim,'linewidth', 0.1);
        LegendInfo_2{i+1} = sprintf('n_b = %f',vec_nb(i));
end
legend(LegendInfo_2);

figure(211);
    xlabel('Time [s]');
    ylabel('total differentiated angle [º]'); %corrigir nome ?????
    title('Real vs Model'); %????????
    xlim([10 11.1]);%t(length(t))]);
    ylim([-9 9]);
   
figure(213);
    plot(vec_nb, fit,'--',vec_nb, (diff([eps; fit(:)])./diff([eps; vec_nb(:)]))',...
         vec_nb,zeros(1,length(vec_nb)),'--g');
    title('Fit %, for different n_b values + derivative');
    xlabel('n_b');
    ylabel('%');
    axis([0 vec_nb(length(vec_nb)) -2 100]);
figure(214);
    plot(vec_nb, mse,'--',vec_nb,(diff([eps; mse(:)])./diff([eps; vec_nb(:)]))',...
         vec_nb,zeros(1,length(vec_nb)),'--g');
    title('MSE, for different n_b values + derivative');
    xlabel('n_b');
    ylabel('MSE');
     axis([0 vec_nb(length(vec_nb)) -1 1]);
figure(215);
    plot(vec_nb, fpe,'--',vec_nb,(diff([eps; mse(:)])./diff([eps; vec_nb(:)]))',...
         vec_nb,zeros(1,length(vec_nb)),'--g');
    title('FPE, for different n_b values + derivative');
    xlabel('n_b');
    ylabel('FPE');
     axis([0 vec_nb(length(vec_nb)) -1 1]);
figure(216);
    plot(vec_nb, loss,'--',vec_nb,(diff([eps; loss(:)])./diff([eps; vec_nb(:)]))',...
         vec_nb,zeros(1,length(vec_nb)),'--g');
    title('LossFcn, for different n_b values + derivative');
    xlabel('n_b');
    ylabel('Loss');
    axis([0 vec_nb(length(vec_nb)) -1 1]);
    
    
%% Effect of ARMAX coefficients - nk
na = 6;
nc = na;
nb = 2;

%Parameter to be tested
vec_nk = 0:1:4;

fit = zeros(1, length(vec_nk));
mse = zeros(1, length(vec_nk));
loss = zeros(1, length(vec_nk));
fpe = zeros(1, length(vec_nk));
LegendInfo_3 = cell(length(vec_nk),1);
LegendInfo_3{length(vec_nk),1} = [];

figure (221)
    plot(t, yf,'-.','linewidth', 1);%nome??
    LegendInfo_3{1} = 'Differentiated';
    hold all;



for i=1:length(vec_nk);
    nk = vec_nk(i); % AR part
    nn = [na nb nc nk];
    th = armax(z,nn); % th is a structure in identification toolbox format
%     [den1,num1] = polydata(th);
    fit(i) = th.Report.Fit.FitPercent;
    mse(i) = th.Report.Fit.MSE;
    loss(i) = th.Report.Fit.LossFcn;
    fpe(i) = th.Report.Fit.FPE;
    %SIMULATION
    yfsim = idsim(u, th);
%     figure(201);
%     zplane(num1, den1);
%     hold on;
    % Checking simulation data
    figure (221)
        plot(t, yfsim,'linewidth', 0.1);
        LegendInfo_3{i+1} = sprintf('n_k = %f',vec_nk(i));
end
legend(LegendInfo_3);

figure(221);
    xlabel('Time [s]');
    ylabel('total differentiated angle [º]'); %corrigir nome ?????
    title('Real vs Model'); %????????
    xlim([10 11.1]);%t(length(t))]);
    ylim([-9 9]);
   
figure(223);
    plot(vec_nk, fit,'--',vec_nk, (diff([eps; fit(:)])./diff([eps; vec_nk(:)]))',...
         vec_nk,zeros(1,length(vec_nk)),'--g');
    title('Fit %, for different n_k values + derivative');
    xlabel('n_k');
    ylabel('%');
    axis([0 vec_nk(length(vec_nk)) -2 100]);
figure(224);
    plot(vec_nk, mse,'--',vec_nk,(diff([eps; mse(:)])./diff([eps; vec_nk(:)]))',...
         vec_nk,zeros(1,length(vec_nk)),'--g');
    title('MSE, for different n_k values + derivative');
    xlabel('n_k');
    ylabel('MSE');
     axis([0 vec_nk(length(vec_nk)) -1 1]);
figure(225);
    plot(vec_nk, fpe,'--',vec_nk,(diff([eps; mse(:)])./diff([eps; vec_nk(:)]))',...
         vec_nk,zeros(1,length(vec_nk)),'--g');
    title('FPE, for different n_k values + derivative');
    xlabel('n_k');
    ylabel('FPE');
     axis([0 vec_nk(length(vec_nk)) -1 1]);
figure(226);
    plot(vec_nk, loss,'--',vec_nk,(diff([eps; loss(:)])./diff([eps; vec_nk(:)]))',...
         vec_nk,zeros(1,length(vec_nk)),'--g');
    title('LossFcn, for different n_k values + derivative');
    xlabel('n_k');
    ylabel('Loss');
    axis([0 vec_nk(length(vec_nk)) -1 1]);    

%% conclusions
% nk = 1 maximises fit and minimises error
% nb = 2 is a good compromise
% na = nc = 6 or 8 seem good values; higher values yield better fit to
% data, but require more computational effort and increase complexity of
% system model and controller
% for na>8 the fit improvement obtained is small (derivative...), so it is
% a compromise between fit/MSE/... and computational effort/controller
% complexity
    
%% After determining the ideal coefficients

z = [yf u]; %(1:length(u)-500) for old implementation of prbs
na = 6; % AR part
nb = 2; % X part
nc = na; % MA part
nk = 1; % Atraso puro – pure delay

nn = [na nb nc nk];
th = armax(z,nn) % th is a structure in identification toolbox format
[den1,num1] = polydata(th);

yfsim = idsim(u, th);
figure(231);
    plot(t,yf,t, yfsim);
    legend('Differentiated','Simulated');
    xlabel('Time [s]');
    ylabel('total differentiated angle [º]'); %corrigir nome ?????
    title('Real vs Model'); %????????
    xlim([10 11.1]);%t(length(t))]);
    ylim([-1.7 1.7]);


    
%% Measured error? - "simple" error, quadratic error?
% COMPARE - identification toolbox
load('prbs_4rd_test_3rd_signal_wksp');
%%
u2 = simdata.signals.values(:,1); % Entrada - Input signal
figure(301);
    plot(simdata.time, u2);
y2 = simdata.signals.values(:,2)*Kp + simdata.signals.values(:,3)*Ke;
figure(302)
    plot(simdata.time, y2);

yf2 = filter(Bfilt,Afilt,y2);
u2detrended = dtrend(u2);

M = iddata(yf2,u2detrended);

[~,fit2]=compare(M,th)

%%
% model generated from prbs signal yields good fit (>95%) to its data and
% good fit (>90%) to square wave data
    
%% Adding the integrator
den = conv(den1, [1 -1]);
[num,den] = eqtflength(num1,conv(den1,[1 -1]));


% conversion to state model
[A,B,C,D] = tf2ss(num,den);

% CHECK
yestimate = dlsim(A,B,C,D,u);

% plot yestimate, recorded output
figure(221);
    plot(t, yestimate, t, ytrend);
% compare shape

%% MOTOR DEAD ZONE
figure (400)
    plotyy(simdata.time,simdata.signals.values(:,1),...
           simdata.time,simdata.signals.values(:,2)*Kp);
    title('Motor Dead Zone');