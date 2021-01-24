--gifboy-wolfenstein
--based on lodev's and yonaba's raycasting tutorial

map={
width=10,
height=10,
{1,0,0,0,1,1,1,1,1,1},
{1,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,1},
{1,0,0,0,1,0,0,0,0,1},
{1,1,0,0,1,1,0,0,0,1},
{1,0,0,0,1,0,0,0,0,1},
{1,1,0,0,1,1,0,0,0,1},
{1,1,1,1,1,1,1,2,2,1}
}

posx=1
posy=3
dirx=1
diry=0
planex=0
planey=0.66
rotation=math.pi/2
direction=1
screenx=160
screeny=160
colorRoof=6
colorSky=5
colorStripes=10

--3D loop
delay(150)
for i=1,24 do
clear()
x=0
for x=0,screenx do
camx=2*x/screenx-1
rayposx=posx
rayposy=posy
raydirx=dirx+planex*camx
raydiry=diry+planey*camx
mapx=rayposx
mapy=rayposy
sidedistx=0
sidedisty=0
deltadistx=math.sqrt(1+(raydiry*raydiry)/(raydirx*raydirx))
deltadisty=math.sqrt(1+(raydirx*raydirx)/(raydiry*raydiry))
perp=0
stepx=0
stepy=0
hit=0
side=0
if raydirx<0 then
stepx=-1
sidedistx=(rayposx-mapx)*deltadistx
else stepx=1
sidedistx=(mapx+1-rayposx)*deltadistx
end
if raydiry<0 then
stepy=-1
sidedisty=(rayposy-mapy)*deltadisty
else stepy=1
sidedisty=(mapy+1-rayposy)*deltadisty
end
while hit==0 do
if sidedistx<sidedisty then
sidedistx=sidedistx+deltadistx
mapx=mapx+stepx
side=0
else
sidedisty=sidedisty+deltadisty
mapy=mapy+stepy
side=1
end
if map[math.floor(mapx)][math.floor(mapy)]>0 then hit=1 end
end
if side==0 then
perp=math.abs((mapx-rayposx+(1-stepx)/2)/raydirx)
else
perp=math.abs((mapy-rayposy+(1-stepy)/2)/raydiry)
end
lineheight=math.abs(screeny/perp)
draw=-lineheight/2+screeny/2
if draw<0 then draw=0 end
drawE=lineheight/2+screeny/2
if drawE>=screenx then drawE=screenx-1 end
a=65
b=58
c=63
if side==1 then
a=a-30
b=b-30
c=c-30
end
if map[math.floor(mapx)][math.floor(mapy)]==2 then a,b,c=255,199,101 end
palette(14,a,b,c)
bandUp=screeny/2+drawE
bandDown=screeny/2+draw
rectfill(x,draw,1,drawE,14);
rectfill(x,drawE,1,272,colorRoof);
rectfill(x,0,1,draw,colorSky);
rectfill(x,bandUp/2,1,1,colorStripes)
rectfill(x,bandDown/2,1,1,colorStripes)
rectfill(x,screeny/2,1,1,colorStripes)
end
render()
if frames()<5 then posx=posx+1 end
if frames()>=5 and frames()<11 then posy=posy+1 end
if frames()>=15 and frames()<20 then posx=posx+1 end
end

-- scene end
delay(2000)
clear()
scale(2,2)
textb('Level Won','center','center',7,1)
render()
stop()