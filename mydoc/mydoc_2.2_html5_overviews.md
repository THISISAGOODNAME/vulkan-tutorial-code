---
title: HTML5简介
last_updated: February 24, 2016
summary: "使用HTML5技术制作canvas动画需要了解的一些基本知识"
---

## HTML5简介

&#160; &#160; &#160; &#160;HTML5是最新一代HTML(Hyper Text Markup Language超文本标记语言)，该语言用于将结构化有组织的层次并展现在浏览器上。HTML元素是创建网页的基石。

## 对canvas的支持

&#160; &#160; &#160; &#160;主流浏览器都对canvas提供了支持，万一某个浏览器不支持canvas元素，在HTML文件中，开发者仍然可以提供一些备用内容，来告知用户他的浏览器不支持canvas

```html
<canvas id="canvas" width="400" height="400">
	对不起，您的浏览器不支持<code>canvas</code>
</canvas>
```

&#160; &#160; &#160; &#160;也可以加入以下JavaScript代码，判断浏览器是否支持canvas

```js
if (document.createElement('canvas').getContext) {
	console.log("您的浏览器支持canvas");
}
```

&#160; &#160; &#160; &#160;下表列出了主流Web浏览器开始支持canvas元素的最小版本号

 IE|Firefox|Safari|Chrome|Opera|iOS Safari|Android
:--:|:-----:|:----:|:----:|:---:|:--------:|:-----:|
9|3.5|3.2|9|10.6|3.2|2.1

## HTML5基本文档

&#160; &#160; &#160; &#160;下面这个代码片段是本站所有实例是初始设置

```html
<!doctype html>
<html>
  <head>
    <meta charset="utf-8">
    <title></title>
    <link rel="stylesheet" href="style.css">
  </head>
  <body>
    <canvas id="canvas" width="400" height="400"></canvas>
    <script>
    window.onload = function () {
      //Our code here...
    };
    </script>
  </body>
</html>

```

&#160; &#160; &#160; &#160;本站几乎所有代码都放在`window.onload`回调函数中，该方法在文件中所有元素加载完成后才执行，可以确保canvas元素在调用代码的时候可以正确访问。不过，在加载大量文件和大文件(比如图片)时，`window.onload`需要等待很久才会被执行，最好使用JavaScript来加载那些耗时的资源。

## CSS样式表

&#160; &#160; &#160; &#160;我不准备深究CSS相关的问题，只在此提供本站使用的CSS文件

```css
body {
	background-color: #bbb;
}

#canvas {
	background-color: #fff;
}
```

## 基础模板运行效果

<iframe height="450px" width="450px" src="http://aicdg.com/html5-animation/html5-animation/examples/ch02/01-skeleton.html" frameborder="0"></iframe>
