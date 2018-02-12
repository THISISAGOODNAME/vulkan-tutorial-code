---
title: 坐标旋转
last_updated: February 26, 2016
summary: "三维坐标系中想旋转"
---

## 数学概念

&#160; &#160; &#160; &#160;在二维坐标系中，坐标点绕着z轴旋转，只有x和y坐标在改变。而在三维坐标系中，也可以绕x轴或者y轴旋转。

### 旋转坐标公式

&#160; &#160; &#160; &#160;二维坐标旋转公式

```javascript
x1 = x * cos(angle) - y * sin(angle)
y1 = y * cos(angle) + x * sin(angle)
```

&#160; &#160; &#160; &#160;三维坐标旋转公式，在三维系统中基本相同，但是要指定绕哪条轴旋转，这样就有三组不同的公式

```javascript
x1 = x * cos(angleZ) - y * sin(angleZ)
y1 = y * cos(angleZ) + x * sin(angleZ)

x1 = x * cos(angleY) - z * sin(angleY)
z1 = z * cos(angleY) + x * sin(angleY)

y1 = y * cos(angleX) - z * sin(angleX)
y1 = z * cos(angleX) + y * sin(angleX)
```

## 绕Y轴旋转

### 实际效果

<iframe height="450px" width="450px" src="http://aicdg.com/html5-animation/html5-animation/examples/ch15/12-rotate-y.html" frameborder="0"></iframe>

### 完整代码

```html
<!doctype html>
<html>
  <head>
    <meta charset="utf-8">
    <title>Rotate Y</title>
    <link rel="stylesheet" href="../include/style.css">
  </head>
  <body>
 
    <canvas id="canvas" width="400" height="400"></canvas>
    <aside>Move mouse left or right on canvas element.</aside>

    <script src="../include/utils.js"></script>
    <script src="./classes/ball3d.js"></script>
    <script>
    window.onload = function () {
      var canvas = document.getElementById('canvas'),
          context = canvas.getContext('2d'),
          mouse = utils.captureMouse(canvas),
          balls = [],
          numBalls = 50,
          fl = 250,
          vpX = canvas.width / 2,
          vpY = canvas.height / 2,
          angleY;

      for (var ball, i = 0; i < numBalls; i++) {
        ball = new Ball3d(15);
        ball.xpos = Math.random() * 200 - 100;
        ball.ypos = Math.random() * 200 - 100;
        ball.zpos = Math.random() * 200 - 100;
        balls.push(ball);
      }

      function rotateY (ball, angle) {
        var cos = Math.cos(angle),
            sin = Math.sin(angle),
            x1 = ball.xpos * cos - ball.zpos * sin,
            z1 = ball.zpos * cos + ball.xpos * sin;
        
        ball.xpos = x1;
        ball.zpos = z1;
        
        if (ball.zpos > -fl) {
          var scale = fl / (fl + ball.zpos);
          ball.scaleX = ball.scaleY = scale;
          ball.x = vpX + ball.xpos * scale;
          ball.y = vpY + ball.ypos * scale;
          ball.visible = true;
        } else {
          ball.visible = false;
        }
      }

      function move (ball) {
        rotateY(ball, angleY);
      }

      function zSort (a, b) {
        return (b.zpos - a.zpos);
      }
      
      function draw (ball) {
        if (ball.visible) {
          ball.draw(context);
        }
      }

      (function drawFrame () {
        window.requestAnimationFrame(drawFrame, canvas);
        context.clearRect(0, 0, canvas.width, canvas.height);
        
        angleY = (mouse.x - vpX) * 0.001;
        balls.forEach(move);
        balls.sort(zSort);
        balls.forEach(draw);
      }());
    };
    </script>
  </body>
</html>

```

&#160; &#160; &#160; &#160;获得一个角度，把它和每个小球传入函数 rotateY 。在这个函数中计算这个角度的正弦值和余弦值，进行旋转相关的计算，然后把旋转后的 x1 和 z1 赋值给小球的 xpos 和 zpos 属性，最后是标准的透视图和z排序。

## 旋转叠加

### 实际效果

<iframe height="450px" width="450px" src="http://aicdg.com/html5-animation/html5-animation/examples/ch15/13-rotate-xy.html" frameborder="0"></iframe>

### 完整代码

```html
<!doctype html>
<html>
  <head>
    <meta charset="utf-8">
    <title>Rotate XY</title>
    <link rel="stylesheet" href="../include/style.css">
  </head>
  <body>
 
    <canvas id="canvas" width="400" height="400"></canvas>
    <aside>Move mouse on canvas element.</aside>

    <script src="../include/utils.js"></script>
    <script src="./classes/ball3d.js"></script>
    <script>
    window.onload = function () {
      var canvas = document.getElementById('canvas'),
          context = canvas.getContext('2d'),
          mouse = utils.captureMouse(canvas),
          balls = [],
          numBalls = 50,
          fl = 250,
          vpX = canvas.width / 2,
          vpY = canvas.height / 2,
          angleX, angleY;

      for (var ball, i = 0; i < numBalls; i++) {
        ball = new Ball3d(15);
        ball.xpos = Math.random() * 200 - 100;
        ball.ypos = Math.random() * 200 - 100;
        ball.zpos = Math.random() * 200 - 100;
        balls.push(ball);
      }

      function rotateX (ball, angle) {                      
        var cos = Math.cos(angle),
            sin = Math.sin(angle),
            y1 = ball.ypos * cos - ball.zpos * sin,
            z1 = ball.zpos * cos + ball.ypos * sin;
        ball.ypos = y1;
        ball.zpos = z1;
      }
      
      function rotateY (ball, angle) {
        var cos = Math.cos(angle),
            sin = Math.sin(angle),
            x1 = ball.xpos * cos - ball.zpos * sin,
            z1 = ball.zpos * cos + ball.xpos * sin;
        ball.xpos = x1;
        ball.zpos = z1;
      }

      function setPerspective (ball) {
        if (ball.zpos > -fl) {
          var scale = fl / (fl + ball.zpos);
          ball.scaleX = ball.scaleY = scale;
          ball.x = vpX + ball.xpos * scale;
          ball.y = vpY + ball.ypos * scale;
          ball.visible = true;
        } else {
          ball.visible = false;
        }
      }

      function move (ball) {
        rotateX(ball, angleX);
        rotateY(ball, angleY);
        setPerspective(ball);
      }

      function zSort (a, b) {
        return (b.zpos - a.zpos);
      }
      
      function draw (ball) {
        if (ball.visible) {
          ball.draw(context);
        }
      }

      (function drawFrame () {
        window.requestAnimationFrame(drawFrame, canvas);
        context.clearRect(0, 0, canvas.width, canvas.height);
        
        angleX = (mouse.y - vpY) * 0.001;
        angleY = (mouse.x - vpX) * 0.001;
        balls.forEach(move);
        balls.sort(zSort);
        balls.forEach(draw);
      }());
    };
    </script>
  </body>
</html>

```

&#160; &#160; &#160; &#160;根据鼠标指针的y坐标和屏幕中心点可以得到一个角，计算这个角度的正弦和余弦值，根据他们得到y1和z1，再赋值给小球的ypos和zpos属性。