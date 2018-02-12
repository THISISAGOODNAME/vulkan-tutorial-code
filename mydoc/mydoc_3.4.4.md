---
title: 使用两个角产生波
last_updated: February 25, 2016
summary: "使用两个角产生波来产生随机运动"
---

## 实际效果

<iframe height="450px" width="450px" src="http://aicdg.com/html5-animation/html5-animation/examples/ch03/06-random.html" frameborder="0"></iframe>

## 完整代码

```html
<!doctype html>
<html>
  <head>
    <meta charset="utf-8">
    <title>Random</title>
    <link rel="stylesheet" href="../include/style.css">
  </head>  
  <body>

    <canvas id="canvas" width="400" height="400"></canvas>
    
    <script src="../include/utils.js"></script>
    <script src="./classes/ball.js"></script>
    <script>
    window.onload = function () {
      var canvas = document.getElementById('canvas'),
          context = canvas.getContext('2d'),
          ball = new Ball(),
          angleX = 0,
          angleY = 0,
          range = 50,
          centerX = canvas.width / 2,
          centerY = canvas.height / 2,
          xspeed = 0.07,
          yspeed = 0.11;
        
      (function drawFrame () {
        window.requestAnimationFrame(drawFrame, canvas);
        context.clearRect(0, 0, canvas.width, canvas.height);

        ball.x = centerX + Math.sin(angleX) * range;
        ball.y = centerY + Math.sin(angleY) * range;
        angleX += xspeed;
        angleY += yspeed;
        ball.draw(context);
      }());
    };
    </script>
  </body>
</html>

```

&#160; &#160; &#160; &#160;本例中，使用两个角，一个角的正弦用于英雄球的x坐标，另一个用于改变球的y坐标，两个角角速度不同，所以尽管数学上可以准确预测球的运动方向，但看起来球是随机运动的

