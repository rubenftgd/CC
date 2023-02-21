who

%%
figure(101);
plot(input.time, input.signals.values);
figure(102);
plot(tensao_pot.time, tensao_pot.signals.values);%folgas mecânicas

%%
%Kp=34.0683º/V

%%

%% d in cm
% clockwise positive
% position 1,2,3,...
interval_dst=2.54/4; %interval distance cm
d = []; %d
L=41.0-2.4; %L  - -2.3-->-2.4
alpha=arctan(d/L); %alpha
alpha_e=;%measured
%%
alpha_e=[];
alpha  =[];
