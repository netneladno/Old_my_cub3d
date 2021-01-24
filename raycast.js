
/*
    Written by chris deboy
    
    based on the tutorial at lodev.org/cgtutor/raycasting/.html
    
    Copyright (c) 2012 Chris DeBoy

    Permission is hereby granted, free of charge, to any person obtaining a copy of
    this software and associated documentation files (the "Software"), to deal in the
    Software without restriction, including without limitation the rights to use, 
    copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the 
    Software, and to permit persons to whom the Software is furnished to do so, 
    subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all 
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
    FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR 
    COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
    AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH
    THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
    
*/

var worldMap = [
    [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],
    [1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
    [1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
    [1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
    [1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1],
    [1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1],
    [1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1],
    [1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1],
    [1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1],
    [1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
    [1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
    [1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
    [1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
    [1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
    [1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
    [1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
    [1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
    [1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
    [1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
    [1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
    [1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
    [1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
    [1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
    [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]
];

var posX = 22; var posY = 12;
var dirX = -1; var dirY = 0;
var oldDirX; var oldPlaneX;
var planeX = 0; var planeY = 0.66;

var time = 0; var oldTime = 0; var date = new Date();

var cnvsScreen = document.getElementById('screen');
var context = cnvsScreen.getContext('2d');

function castRays()
    {
        context.clearRect(0, 0, cnvsScreen.width, cnvsScreen.height);
        for(x = 0; x < cnvsScreen.width; x++)
            {
                
                var cameraX = 2 * x / cnvsScreen.width - 1;
                var rayPosX = posX;
                var rayPosY = posY;
                var rayDirX = dirX + planeX * cameraX;
                var rayDirY = dirY + planeY * cameraX;
                
                var mapX = Math.floor(rayPosX);
                var mapY = Math.floor(rayPosY);
                
                var sideDistX;
                var sideDistY;
                
                var deltaDistX = Math.sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
                var deltaDistY = Math.sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
                
                var stepX; var stepY;
                
                var hit = 0;
                var side;
                
                if(rayDirX < 0)
                    {
                        stepX = -1;
                        sideDistX = (rayPosX - mapX) * deltaDistX;
                    }
                else
                    {
                        stepX = 1;
                        sideDistX = (mapX + 1.0 - rayPosX) * deltaDistX;
                    }
                if(rayDirY < 0)
                    {
                        stepY = -1;
                        sideDistY = (rayPosY - mapY) * deltaDistY;
                    }
                else
                    {
                        stepY = 1;
                        sideDistY = (mapY + 1.0 - rayPosY) * deltaDistY;
                    }
                    
                while(hit === 0)
                    {
                        if(sideDistX < sideDistY)
                            {
                                sideDistX += deltaDistX;
                                mapX += stepX;
                                side = 0;
                            }
                        else
                            {
                                sideDistY += deltaDistY;
                                mapY += stepY;
                                side = 1;
                            }
                        
                        if(worldMap[mapX][mapY] > 0){hit = 1;}
                    }
                
                if(side === 0)
                    {
                        perpWallDist = Math.abs((mapX - rayPosX + (1 - stepX) / 2) /rayDirX);
                    }
                else
                    {
                        perpWallDist = Math.abs((mapY - rayPosY + (1 - stepY) / 2) / rayDirY);
                    }
                
                var lHeight = Math.abs(Math.floor(cnvsScreen.height /  perpWallDist));
                
                var drawStart = -lHeight / 2 + cnvsScreen.height / 2;
                if(drawStart < 0){ drawStart = 0;}
                var drawEnd = lHeight / 2 + cnvsScreen.height / 2;
                if(drawEnd >= cnvsScreen.height){ drawEnd = cnvsScreen.height - 1;}
                
                var color;
                switch(worldMap[mapX][mapY])
                    {
                        case 1: color = "#ff0000"; break;
                        case 2: color = "#00ff00"; break;
                        case 3: color = "#0000ff"; break;
                        case 4: color = "#ffffff"; break;
                        default: color = "ff00FF"; break;
                    }
                
                //if (side == 1){color = color / 2;}
                
                context.fillStyle = color;
                context.beginPath();
                context.moveTo(x,drawStart);
                context.lineTo(x,drawEnd);
                context.stroke();
            }
        requestAnimFrame(function(){castRays();});
        
        oldTime = time;
        time = date.getTime();
        var frameTime = (time - oldTime) / 1000.0;
        
        var moveSpeed = frameTime * 5.0;
        var rotSpeed = frameTime * 3.0;
        
        if(keyList.up )
            {
                if(worldMap[Math.floor(posX + dirX * moveSpeed)][Math.floor(posY)] === false){posX += dirX * moveSpeed;}
                if(worldMap[Math.floor(posX)][Math.floor(posY + dirY * moveSpeed)] === false){posY += dirY * moveSpeed;}
            }
         if (keyList.down )
            {
                if(worldMap[Math.floor(posX - dirX * moveSpeed)][Math.floor(posY)] === false){posX -= dirX * moveSpeed;}
                if(worldMap[Math.floor(posX)][Math.floor(posY - dirY * moveSpeed)] === false){posY -= dirY * moveSpeed;}
            }
        if (keyList.right )
            {
                oldDirX = dirX;
                dirX = dirX * Math.cos(-rotSpeed) - dirY * Math.sin(-rotSpeed);
                dirY = oldDirX * Math.sin(-rotSpeed) + dirY * Math.cos(-rotSpeed);
                oldPlaneX = planeX;
                planeX = planeX * Math.cos(-rotSpeed) - planeY * Math.sin(-rotSpeed);
                planeY = oldPlaneX * Math.sin(-rotSpeed) + planeY * Math.cos(-rotSpeed);
            }
        if (keyList.left )
            {
                oldDirX = dirX;
                dirX = dirX * Math.cos(rotSpeed) - dirY * Math.sin(rotSpeed);
                dirY = oldDirX * Math.sin(rotSpeed) + dirY * Math.cos(rotSpeed);
                oldPlaneX = planeX;
                planeX = planeX * Math.cos(rotSpeed) - planeY * Math.sin(rotSpeed);
                planeY = oldPlaneX * Math.sin(rotSpeed) + planeY * Math.cos(rotSpeed);
            }
        
        
    }
/*

    input.js library by christopher deboy
    Copyright (c) 2012 Chris DeBoy

    Permission is hereby granted, free of charge, to any person obtaining a copy of
    this software and associated documentation files (the "Software"), to deal in the
    Software without restriction, including without limitation the rights to use, 
    copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the 
    Software, and to permit persons to whom the Software is furnished to do so, 
    subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all 
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
    FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR 
    COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
    AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH
    THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
    
 */

keyList = {
    w:false, 
    a:false, 
    s:false, 
    d:false, 
    up:false, 
    left:false, 
    right:false, 
    down:false
};
mouseList = new Array(3);
var posX;
var posY;
keysDown = function(event)
{
    
    e = event.keyCode || e;
    console.log(e);
    if(e == 87){keyList.w = true;}
    if(e == 65){keyList.a = true;}
    if(e == 83){keyList.s = true;}
    if(e == 68){keyList.d = true;}
    if(e == 38){keyList.up = true;}
    if(e == 37){keyList.left = true;}
    if(e == 40){keyList.right = true;}
    if(e == 39){keyList.down = true;}
    
};

keysUp = function(event)
{
    
    e = event.keyCode || e;
    if(e == 87){keyList.w = false;}
    if(e == 65){keyList.a = false;}
    if(e == 83){keyList.s = false;}
    if(e == 68){keyList.d = false;}
    if(e == 38){keyList.up = false;}
    if(e == 37){keyList.left = false;}
    if(e == 40){keyList.right = false;}
    if(e == 39){keyList.down = false;}
    
};

mouseDown = function(event)
{
    e = event.button;
    if(e === 0){mouseList.lmb = true;}
    if(e == 1){mouseList.rmb = true;}
    if(e == 2){mouseList.mmb = true;}
};

mouseUp = function(event)
{
    e = event.button;
    if(e === 0){mouseList.lmb = false;}
    if(e == 1){mouseList.rmb = false;}
    if(e == 2){mouseList.mmb = false;}
};

mouseMove = function(event)
{
    e = event;
    if (e.pageX || e.pageY)     {
        posX = e.pageX - (window.innerWidth/2);
        posY = e.pageY - (window.innerHeight/2);
    }
    else if (e.clientX || e.clientY)     {
        posX = e.clientX + document.body.scrollLeft + document.documentElement.scrollLeft - (window.innerWidth/2);
        posY = e.clientY + document.body.scrollTop + document.documentElement.scrollTop - (window.innerHeight/2);
    }
};

function bind( scope, fn ) {

    return function () {

        fn.apply( scope, arguments );

    };

}

document.onLoad = function(){
document.addEventListener("keydown", bind(this, keysDown));
document.addEventListener("keyup", bind(this, keysUp));
document.addEventListener("mousedown", bind(this, mouseDown));
document.addEventListener("mouseup", bind(this, mouseUp));
document.addEventListener("mousemove", bind(this, mouseMove));
};
