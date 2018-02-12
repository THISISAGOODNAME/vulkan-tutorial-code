---
title: 增加线性垂直运动
last_updated: February 25, 2016
summary: "在垂直方向的周期运动的基础上，水平方向添加线性运动"
---

## 实际效果

<iframe height="450px" width="450px" src="http://aicdg.com/html5-animation/html5-animation/examples/ch03/04-wave-1.html" frameborder="0"></iframe>


## 完整代码

```html
<!doctype html>
<html>
  <head>
    <meta charset="utf-8">
    <title>Wave 1</title>
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
          angle = 0,
          centerY = 200,
          range = 50,
          xspeed = 1,
          yspeed = 0.05;
        
      ball.x = 0;
        
      (function drawFrame () {
        window.requestAnimationFrame(drawFrame, canvas);
        context.clearRect(0, 0, canvas.width, canvas.height);

        ball.x += xspeed;

        if (ball.x > canvas.width) ball.x = 0;

        ball.y = centerY + Math.sin(angle) * range;
        angle += yspeed;
        ball.draw(context);
      }());
    };
    </script>
  </body>
</html>
```

