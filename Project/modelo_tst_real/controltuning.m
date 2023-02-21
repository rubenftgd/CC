% Controlo por computador - Reference design for testing on the real system
%
% Alexandre Bernardino, Joao Miranda Lemos - Setembro 2014

Ke = -3.5; % Extensometer
Kp = 36; % Potentiometer

% Regulator design
Q = C'*C;
R = 100;
[K,S,E] = dlqr(A,B,Q,R);

% Current estimator design
w2 = 100;
QE = eye(size(A))*w2;
RE = 1;
G = eye(size(A));
[M,P,Z,EE] = dlqe(A,G,C,QE,RE);

% Estimator implementation
PHIE = A-M*C*A;
GAMMAE = B-M*C*B;
CE = eye(size(PHIE));
DE = zeros(size(CE,1),size(GAMMAE,2));

% Externanl reference input
N = inv([A-eye(size(A)), B; C,0])*[zeros(size(A,1),1);1];
Nx = N(1:end-1,:);
Nu = N(end,:);
Nbar = Nu+K*Nx;
