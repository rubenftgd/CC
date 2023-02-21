%% INIT
Kp = 34.0683;
Ke = -4.2046;
sampling_time = 1/50; %0.02,50Hz ; for A/D, D/A
sampling_time_scope = 0.020; %sampling time for scopes
%%
load('identified_sys_model');

%% Agregated system

%LQR
R=500;
[K,S,E] = dlqr(A,B,(C'*C),R);
% LQE
% Current estimator design
qe = 100;
QE = eye(size(A))*qe;
RE = 1; %1
G = eye(size(A));
[M,P,Z,EE] = dlqe(A,G,C,QE,RE);

% Externanl reference input
N = inv([A-eye(size(A)), B; C,0])*[zeros(size(A,1),1);1];
Nx = N(1:end-1,:);
Nu = N(end,:);
Nbar = Nu+K*Nx;

%% LQR
C_lqr = ss(A-B*K,B*Nbar,C,0,0.02);
bode(C_lqr);

[NC_lqr,DC_lqr] = tfdata(C_lqr,'v');
subplot(1,2,1)
zplane(NC_lqr,DC_lqr)
ax = axis;
subplot(1,2,2)
zplane([],E)
axis(ax)

%% LQE
subplot(1,2,1)
zplane([],eig(A-M*C*A))
subplot(1,2,2)
zplane([],EE)

%% LQG
C2_lqg = ss([A -B*K; M*C*A A-M*C*A-(B-M*C*B)*K-M*C*B*K], ...
[B; M*C*B+(B-M*C*B)]*Nbar,[C zeros(size(C))],0,0.02);
bode(C_lqr,C2_lqg)
legend('C (LQR)','C (LQG, m2)')
%%
[NC2_lqg,DC2_lqg] = tfdata(C2_lqg,'v');
subplot(1,2,1)
zplane(NC2_lqg,DC2_lqg)
ax = axis;
subplot(1,2,2)
zplane([],[E; EE])
axis(ax)


%% Time Response

%% Frequency Response

%% Loop-Gain