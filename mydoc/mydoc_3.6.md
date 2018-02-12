---
title: 两点间的距离
last_updated: February 25, 2016
summary: "计算鼠标到坐标原点间的距离"
---

## 实际效果

<iframe height="490px" width="450px" src="http://aicdg.com/html5-animation/html5-animation/examples/ch03/11-mouse-distance.html" frameborder="0"></iframe>

## 勾股定理

&#160; &#160; &#160; &#160;根据两直角边长度的平方等于斜边的平方，可以得到两件间距离公式

```javascript
var dx = x2 - x1,
    dy = y2 - y1,
    dist = Math.sqrt(dx * dx + dy * dy);
```

## 完整代码

```html
<!doctype html>
<html>
  <head>
    <meta charset="utf-8">
    <title>Mouse Distance</title>
    <link rel="stylesheet" href="../include/style.css">
  </head>
  <body>

    <canvas id="canvas" width="400" height="400"></canvas>
    <textarea id="log"></textarea>
    <aside>Move mouse on canvas element.</aside>
    
    <script src="../include/utils.js"></script>
    <script>
    window.onload = function () {
      var canvas = document.getElementById('canvas'),
          context = canvas.getContext('2d'),
          mouse = utils.captureMouse(canvas),
          log = document.getElementById('log'),
          rect = {x: canvas.width / 2, y: canvas.height / 2};
        
      (function drawFrame () {
        window.requestAnimationFrame(drawFrame, canvas);
        context.clearRect(0, 0, canvas.width, canvas.height);
          
        var dx = rect.x - mouse.x,
            dy = rect.y - mouse.y,
            dist = Math.sqrt(dx * dx + dy * dy);
    
        //draw square
        context.fillStyle = "#000000";
        context.fillRect(rect.x - 2, rect.y - 2, 4, 4);
        //draw line
        context.beginPath();
        context.moveTo(rect.x, rect.y);
        context.lineTo(mouse.x, mouse.y);
        context.closePath();
        context.stroke();
    
        //log output of distance value to screen
        log.value = "distance: " + dist;
      }());
    };
    </script>
  </body>
</html>

```

