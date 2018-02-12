---
title: 旋转
last_updated: February 25, 2016
summary: "实现箭头跟着鼠标旋转"
---

&#160; &#160; &#160; &#160;在本节将要实现：绘制一个物体，并让它随着鼠标旋转

## 具体效果

<iframe height="450px" width="450px" src="http://aicdg.com/html5-animation/html5-animation/examples/ch03/01-rotate-to-mouse.html" frameborder="0"></iframe>


## 绘制箭头

&#160; &#160; &#160; &#160;首先，需要一个用来旋转的对象，该对象包含使用canvas上下文在canvas上绘制一个箭头的功能。由于该箭头会重复使用，我们将其封装成一个类，并写到arrow.js中，以后使用时直接在html中调用即可。

```javascript
function Arrow () {
  this.x = 0;
  this.y = 0;
  this.color = "#ffff00";
  this.rotation = 0;
}

Arrow.prototype.draw = function (context) {
  context.save();
  context.translate(this.x, this.y);
  context.rotate(this.rotation);
  
  context.lineWidth = 2;
  context.fillStyle = this.color;
  context.beginPath();
  context.moveTo(-50, -25);
  context.lineTo(0, -25);
  context.lineTo(0, -50);
  context.lineTo(50, 0);
  context.lineTo(0, 50);
  context.lineTo(0, 25);
  context.lineTo(-50, 25);
  context.lineTo(-50, -25);
  context.closePath();
  context.fill();
  context.stroke();
  
  context.restore();
};
```

{{site.data.alerts.note}}draw(context) 方法根据传入的 canvas 上下文参数使用 canvas 绘图API来绘制一个箭头{{site.data.alerts.end}}

## 计算旋转角度

&#160; &#160; &#160; &#160;现在，可以先想办法获取鼠标的坐标值 mouse.x 和 mouse.y，可以使用js原生的 `mousemove` 监听器。现在，只需要通过 `Math.atan2(dx, dy)` 方法算出角度大小并赋值给箭头对象的 rotation 属性。过程如下所示。

```javascript
var dx = mouse.x - arrow.x,
    dy = mouse.y - arrow.y;
          
arrow.rotation = Math.atan2(dy, dx); 
```

## 完整的HTML文件

```html
<!doctype html>
<html>
  <head>
    <meta charset="utf-8">
    <title>Rotate to Mouse</title>
    <link rel="stylesheet" href="../include/style.css">
  </head>
  <body>

    <canvas id="canvas" width="400" height="400"></canvas>
    <aside>Move mouse on canvas element.</aside>
    
    <script src="../include/utils.js"></script>
    <script src="./classes/arrow.js"></script>
    <script>
    window.onload = function () {
      var canvas = document.getElementById('canvas'),
          context = canvas.getContext('2d'),
          mouse = utils.captureMouse(canvas),
          arrow = new Arrow();
        
      arrow.x = canvas.width / 2;
      arrow.y = canvas.height / 2;
        
      (function drawFrame () {
        window.requestAnimationFrame(drawFrame, canvas);
        context.clearRect(0, 0, canvas.width, canvas.height);
          
        var dx = mouse.x - arrow.x,
            dy = mouse.y - arrow.y;
          
        arrow.rotation = Math.atan2(dy, dx); //radians
        arrow.draw(context);
      }());
    };
    </script>
  </body>
</html>
```

{{site.data.alerts.note}}引用的utils.js是一个通过的函数库，功能包括 requestAnimationFrame 兼容调整，鼠标/键盘事件绑定等功能，完整文件可以在[这里](https://github.com/THISISAGOODNAME/html5-animation/blob/gh-pages/html5-animation/examples/include/utils.js)找到 {{site.data.alerts.end}}

