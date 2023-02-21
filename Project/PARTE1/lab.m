%% *Inicialização*
clear all
close all
clc;

%% Q1

%% 1º LAB
sim('input_mdl',2);
figure(101);
    plot(input.time, input.signals.values, 'linewidth', 1.25,'-b');
    title('');
    hold all;
    xlabel('Time (s)');
    ylabel('input signal (V)');
    legend('AutoUpdate','on')

