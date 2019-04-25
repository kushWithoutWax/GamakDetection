clear all;close all;


%%data Import section


L=7;                                       %domain size
n=2044;                                     %no of points
t2=linspace(0,L,n+1); t=t2(1:n);            %%time vector
S=(0.3*sin(2*t)+0.4*sin(4*t)+tanh(t-1).^2 + 0.22* sin(3 * (t-4).^3)+0.5*exp(-(t-1).^2)+0.1*sin(4*t));                  %% signal

k=(2*pi/L)*[0:n/2-1 -n/2:-1]; ks=fftshift(k);

St=fft(S);
tres=0.1;
iwindow_width=2;
tslide=0:tres:L;
locations=find(ks>=4 & ks<100 );
array_hfc=[];
for j=1:length(tslide)

    
%gabor
g=exp(-1*iwindow_width*(t-tslide(j)).^2);
Sg=g.*S;
Sgt=fft(Sg);
spectra_windowed=abs(fftshift(Sgt)/max(abs(Sgt)));
array_spectra=spectra_windowed(locations);
total_hfc=trapz(array_spectra);         %%total high frequency components.
array_hfc=[array_hfc,total_hfc];


subplot(3,1,1), plot(t,S,'k',t,g,'r');
subplot(3,1,2), plot(t,Sg,'k');
subplot(3,1,3), plot(ks,spectra_windowed,'k');
axis([-10 10 0 1])
drawnow
pause(0.1)
end


figure;
subplot(2,1,1), plot(t,S,'k');
subplot(2,1,2) , scatter(tslide,array_hfc,'k');

