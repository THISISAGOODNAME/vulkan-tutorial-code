---
title: 圆和椭圆
last_updated: February 25, 2016
summary: "圆周运动和椭圆运动"
---

## 圆周运动效果

<iframe height="450px" width="450px" src="http://aicdg.com/html5-animation/html5-animation/examples/ch03/08-circle.html" frameborder="0"></iframe>

## 圆周运动完整代码

```html
<!doctype html>
<html>
  <head>
    <meta charset="utf-8">
    <title>Circle</title>
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
          centerX = canvas.width / 2,
          centerY = canvas.height / 2,
          radius = 50,
          speed = 0.05;
      
      (function drawFrame () {
        window.requestAnimationFrame(drawFrame, canvas);
        context.clearRect(0, 0, canvas.width, canvas.height);

        ball.x = centerX + Math.cos(angle) * radius;
        ball.y = centerY + Math.sin(angle) * radius;
        angle += speed;
        ball.draw(context);
      }());
    };
    </script>
  </body>
</html>

```

&#160; &#160; &#160; &#160;圆周运动和之前的伪随机运动类似，只不过正弦用于计算y坐标，而余弦用于计算x坐标

## 椭圆运动效果

<iframe height="450px" width="450px" src="http://aicdg.com/html5-animation/html5-animation/examples/ch03/09-oval.html" frameborder="0"></iframe>

## 椭圆运动完整代码

```html
<!doctype html>
<html>
  <head>
    <meta charset="utf-8">
    <title>Oval</title>
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
          centerX = canvas.width / 2,
          centerY = canvas.height / 2,
          radiusX = 150,
          radiusY = 100,
          speed = 0.05;
        
      (function drawFrame () {
        window.requestAnimationFrame(drawFrame, canvas);
        context.clearRect(0, 0, canvas.width, canvas.height);
        
        ball.x = centerX + Math.cos(angle) * radiusX;
        ball.y = centerY + Math.sin(angle) * radiusY;
        angle += speed;
        ball.draw(context);
      }());
    };
    </script>
  </body>
</html>

```

&#160; &#160; &#160; &#160;椭圆运动在圆周运动的基础上，，将x和y方向的半径乘以一个不同的系数即可实现