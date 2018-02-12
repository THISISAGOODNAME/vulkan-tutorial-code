---
title: 脉冲运动
last_updated: February 25, 2016
summary: "把周期运动的对象从y坐标变成半径"
---

## 实际效果

<iframe height="450px" width="450px" src="http://aicdg.com/html5-animation/html5-animation/examples/ch03/05-pulse.html" frameborder="0"></iframe>

## 完整代码

```html
<!doctype html>
<html>
  <head>
    <meta charset="utf-8">
    <title>Pulse</title>
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
          centerScale = 1,
          range = 0.5,
          speed = 0.05;
        
      ball.x = canvas.width / 2;
      ball.y = canvas.height / 2;
        
      (function drawFrame () {
        window.requestAnimationFrame(drawFrame, canvas);
        context.clearRect(0, 0, canvas.width, canvas.height);

        ball.scaleX = ball.scaleY = centerScale + Math.sin(angle) * range;
        angle += speed;
        ball.draw(context);
      }());
    };
    </script>
  </body>
</html>
```

&#160; &#160; &#160; &#160;本例中，使用正弦值改变球在x方向和y方向的比例


