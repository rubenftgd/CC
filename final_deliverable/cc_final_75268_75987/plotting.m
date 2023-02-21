%% Test results plotting

%% LOAD
%% Plotting the signals

figure (601)
%     suptitle(sprintf('Simulation data for R = %.0f, R_E = %.0f and integrator with K=0.15 (reset and saturation limits adjusted)', R, RE));
    suptitle('Simulation Data');
    subplot(2,1,1)
        plot(simdata.time/0.02, simdata.signals.values(:,1),'linewidth', 0.1);
        hold on;
        plot(simdata.time/0.02, simdata.signals.values(:,2),'linewidth', 0.1);
        legend('Reference','Total Bar Deflection');
        hold on;
        ylabel('Angle [º]');
        ylim([-60 60])
    subplot(2,1,2);
        plot(simdata.time/0.02, simdata.signals.values(:,3),'linewidth', 0.1);
        xlabel('k');
        ylabel('u_k[V]');
        ylim([-3 3])
%%
% Transfer functions
% LQR
C_lqr = ss(A-B*K,B*Nbar,C,0,0.02);
figure(611);
    bode(C_lqr);
    suptitle('LQR Frequency Response');

[NC_lqr,DC_lqr] = tfdata(C_lqr,'v');
figure(612);
    suptitle('LQR Symmetric Root Locus');
    subplot(1,2,1)
        zplane(NC_lqr,DC_lqr)
        ax = axis;
    subplot(1,2,2)
        zplane([],E)
        axis(ax)
% LQG
C2_lqg = ss([A -B*K; M*C*A A-M*C*A-(B-M*C*B)*K-M*C*B*K], ...
[B; M*C*B+(B-M*C*B)]*Nbar,[C zeros(size(C))],0,0.02);
figure(613);
    bode(C_lqr,C2_lqg);
    suptitle('LQG Frequency Response');
    legend('C (LQR)','C (LQG, m2)');

[NC2_lqg,DC2_lqg] = tfdata(C2_lqg,'v');
figure(614);
    suptitle('LQG Symmetric Root Locus');
    subplot(1,2,1);
        zplane(NC2_lqg,DC2_lqg);
        ax = axis;
    subplot(1,2,2);
        zplane([],[E; EE]);% EE-LQE, E-LQR
        axis(ax);



