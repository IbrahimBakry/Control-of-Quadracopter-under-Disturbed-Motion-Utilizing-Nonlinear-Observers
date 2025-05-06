

% PLOT THE 3D TRAJECTORY OF OS4

glob;

% ********* DEG2RAD ********* 
%roll=roll*deg2rad;  % Transform deg2rad [rad]
%pitch=pitch*deg2rad;  % Transform deg2rad [rad]
%yaw=yaw*deg2rad;  % Transform deg2rad [rad]


hf = figure(1);
cameratoolbar('Show');
cameratoolbar('SetMode','orbit');
set(gcf,'MenuBar','figure','Renderer','OpenGL');
hold on;
axis vis3d;
view(3);
zoom(0.6);
set(gca,'Visible','On','Box','On','XGrid', 'Off','YGrid', 'Off','ZGrid', 'Off','projection','perspective');
% display coordinate frame at origin
hold off;
hold on;
drawH(eye(4),1,'ORIGIN',[0 0 0]);
for i=1:length(x),
    if (i>1),
        drawnow;
        delete(h.hx);
        delete(h.hy);
        delete(h.hz);
        delete(h.htext);
    end
    H_w_heli = Hom([x(i),y(i),z(i),yaw(i),pitch(i),roll(i)]');
    h = drawH(H_w_heli,0.3,'heli',[1 0 0]);
    
    %set camera
    campos([x(i),y(i)-(i*0.01+2),z(i)]);
    camup([0 0 1]');
    camtarget([x(i),y(i),z(i)]);
end
hold off;
out=0;
