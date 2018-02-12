---
title: 使用绘图API产生的波
last_updated: February 25, 2016
summary: "使用绘图API来制作类似三角函数函数曲线的动画"
---

## 实际效果

<iframe height="450px" width="450px" src="http://aicdg.com/html5-animation/html5-animation/examples/ch03/07-wave-2.html" frameborder="0"></iframe>

## 完整代码

```html
<!doctype html>
<html>
  <head>
    <meta charset="utf-8">
    <title>Wave 2</title>
    <link rel="stylesheet" href="../include/style.css">
  </head>  
  <body>

    <canvas id="canvas" width="400" height="400"></canvas>
    
    <script src="../include/utils.js"></script>
    <script>
    window.onload = function () {
      var canvas = document.getElementById('canvas'),
          context = canvas.getContext('2d'),
          angle = 0,
          range = 50,
          centerY = canvas.height / 2,
          xspeed = 1,
          yspeed = 0.05,
          xpos = 0,
          ypos = centerY;

      context.lineWidth = 2;

      (function drawFrame () {
        window.requestAnimationFrame(drawFrame, canvas);
        
        context.beginPath();
        context.moveTo(xpos, ypos);
        //Calculate the new position.
        xpos += xspeed;
        angle += yspeed;
        ypos = centerY + Math.sin(angle) * range;
        context.lineTo(xpos, ypos);
        context.stroke();
      }());
    };
    </script>
  </body>
</html>

```

&#160; &#160; &#160; &#160;本例中，在drawFrame中取消了对context.clearRect的调用，这样canvas元素就不会在每一帧开始的时候擦除之前绘制的图像，使得每一帧绘制的图像都保留在canvas上
