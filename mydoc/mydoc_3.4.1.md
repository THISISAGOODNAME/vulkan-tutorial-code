---
title: 平滑的上下运动
last_updated: February 25, 2016
summary: "使用正弦的周期特性制作摆动"
---

&#160; &#160; &#160; &#160;通过不断地增加角的度数可以模拟实现从0到1再变到-1最后回到0的效果，通过不断增加角的度数可以不断得到上下波动的波形。

## 实际效果

<iframe height="450px" width="450px" src="http://aicdg.com/html5-animation/html5-animation/examples/ch03/03-bobbing-2.html" frameborder="0"></iframe>

## ball.js

&#160; &#160; &#160; &#160;示例使用到了一个根据Ball类定义的新对象。ball.js如下所示

```javascript
function Ball (radius, color) {
  if (radius === undefined) { radius = 40; }
  if (color === undefined) { color = "#ff0000"; }
  this.x = 0;
  this.y = 0;
  this.radius = radius;
  this.rotation = 0;
  this.scaleX = 1;
  this.scaleY = 1;
  this.color = utils.parseColor(color);
  this.lineWidth = 1;
}

Ball.prototype.draw = function (context) {
  context.save();
  context.translate(this.x, this.y);
  context.rotate(this.rotation);
  context.scale(this.scaleX, this.scaleY);
  
  context.lineWidth = this.lineWidth;
  context.fillStyle = this.color;
  context.beginPath();
  //x, y, radius, start_angle, end_angle, anti-clockwise
  context.arc(0, 0, this.radius, 0, (Math.PI * 2), true);
  context.closePath();
  context.fill();
  if (this.lineWidth > 0) {
    context.stroke();
  }
  context.restore();
};
```

{{site.data.alerts.note}}当创建ball对象时，默认半径为40，默认颜色为红色，但可以根据需要自定义颜色和半径{{site.data.alerts.end}}

## 完整代码

```html
<!doctype html>
<html>
  <head>
    <meta charset="utf-8">
    <title>Bobbing 2</title>
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
          speed = 0.1;
        
      ball.x = canvas.width / 2;

      (function drawFrame () {
        window.requestAnimationFrame(drawFrame, canvas);
        context.clearRect(0, 0, canvas.width, canvas.height);
          
        ball.y = centerY + Math.sin(angle) * range;     
        angle += speed;
        ball.draw(context);
      }());
    };
    </script>
  </body>
</html>
```


