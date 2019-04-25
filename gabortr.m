clear all;close all;


%%data Import section


L=10.3;            %domain size
n=2044;          %no of points
t2=linspace(0,L,n+1); t=t2(1:n);
S=(3*sin(2*t)+4*sin(4*t));%% signal

k=(2*pi/L)*[0:n/2-1 -n/2:-1]; ks=fftshift(k);

St=fft(S);
tres=0.1;
iwindow_width=1;
tslide=0:tres:10;


for j=1:length(tslide)

    
%gabor
g=exp(-1*iwindow_width*(t-tslide(j)).^2);
Sg=g.*S;
Sgt=fft(Sg);
spectra_windowed=abs(fftshift(Sgt)/max(abs(Sgt)));    
subplot(3,1,1), plot(t,S,'k',t,g,'r');
subplot(3,1,2), plot(t,Sg,'k');
subplot(3,1,3), plot(ks,spectra_windowed,'k');
axis([-5 5 0 1])
drawnow
pause(0.1)
end
