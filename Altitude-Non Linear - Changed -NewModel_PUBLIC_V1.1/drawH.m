

function out = drawH(H, s, t, c)

v1 = [H(1,4);H(2,4);H(3,4)];
v2 = v1 + s*[H(1,1);H(2,1);H(3,1)]; 
v3 = v1 + s*[H(1,2);H(2,2);H(3,2)]; 
v4 = v1 + s*[H(1,3);H(2,3);H(3,3)]; 

out.hx = line([v1(1),v2(1)] , [v1(2),v2(2)] , [v1(3),v2(3)]);
out.hy = line([v1(1),v3(1)] , [v1(2),v3(2)] , [v1(3),v3(3)]);
out.hz = line([v1(1),v4(1)] , [v1(2),v4(2)] , [v1(3),v4(3)]);

vadd = [H(1,1);H(2,1);H(3,1)] + [H(1,2);H(2,2);H(3,2)] + [H(1,3);H(2,3);H(3,3)];
textloc = v1 - 0.2*vadd;
out.htext = text(textloc(1),textloc(2),textloc(3),t);

%set line properties
set(out.hx,'Color',[0 0 0],'LineWidth',2);
set(out.hy,'Color',c,'LineWidth',2);
set(out.hz,'Color',c,'LineWidth',2);

%set text properties
set(out.htext,'Color',c);       