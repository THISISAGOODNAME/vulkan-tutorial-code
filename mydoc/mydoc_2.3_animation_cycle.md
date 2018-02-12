---
title: 用代码实现动画
last_updated: February 25, 2016
summary: "本节主要是动画循环相关的知识"
---

<link rel="stylesheet" type="text/css" href="http://cdn.bootcss.com/mermaid/0.5.8/mermaid.min.css">
<link rel="stylesheet" type="text/css" href="http://cdn.bootcss.com/mermaid/0.5.8/mermaid.forest.min.css">
<script type="text/javascript" src="http://cdn.bootcss.com/mermaid/0.5.8/mermaid.min.js"></script>
<script>mermaid.initialize({startOnLoad:true});</script>

&#160; &#160; &#160; &#160;在准备好HTML5文件的基本模板之后，已经可以编码了，只要再有一个支持HTML5的web浏览器，就完事具备

## 动画循环

&#160; &#160; &#160; &#160;几乎所有程序动画都会表现为某种形式的循环

<div class="mermaid">
	graph LR
		A(显示<br>第1帧)-->B(显示<br>第2帧)
		B-->C(显示<br>第3帧)
		C-->D(......)
</div>

<center>逐帧动画</center>

&#160; &#160; &#160; &#160;代码会读取这些相关数据，并根据这些数据将对象绘制出来，从而显示这些帧

<div class="mermaid">
	graph LR
		A(渲染<br>第1帧)-->B(渲染<br>第2帧)
		B-->C(渲染<br>第3帧)
		C-->D(......)
</div>

<center>渲染并显示每一帧</center>

&#160; &#160; &#160; &#160;而描述一个动态的，编码的动画流程图则如下图所示

<div class="mermaid">
	graph LR
		A(获取初<br>始状态)-->B(渲染帧)
		B-->C(应用<br>规则)
		C-->D(结束了?)
		D-->|是|E(显示帧)
		D-->|否|B
</div>

<center>脚本动画</center>

&#160; &#160; &#160; &#160;同一套规则(e.g:球向右移动5像素)会不断重复利用，构成循环，就能形成动画。但是，下面的解释是许多初学者的一种误解：循环的运行依赖于几乎所有编程语言中的while循环结构

```javascript
while(true) {
	ball.x += 1;
}
```
{{site.data.alerts.warning}}乍看，没什么问题，求沿着x轴运动指导运动到canvas之外，但是，其实，你什么都看不到。因为没有更新canvas元素的显示{{site.data.alerts.end}}

&#160; &#160; &#160; &#160;为了实现动画，要为每一帧执行以下操作：

1. 执行该帧锁钥调用到的代码
2. 将所有对象绘制到canvas上
3. 重复该过程渲染下一帧

&#160; &#160; &#160; &#160;所以，代码实质应该是一个类似下面的代码

```javascript
function drawFrame() {
	ball.x += 1;
	ball.draw(context);
}

window.setInterval(drawFrame, 1000/60);
```

&#160; &#160; &#160; &#160;本例中，以1000/60的时间间隔来调用 drawFrame 函数，即60FPS，每隔大约 17ms 执行一次绘制函数。

## 使用requestAnimationFrame的动画循环

&#160; &#160; &#160; &#160;由于开发者对基于HTML5的动画兴趣日益增长，Web浏览器专门为JavaScript的开发者实现了一个API，用过它提供了基于浏览器的优化实现。 window.requestAnimationFrame 接受一个回调函数作为参数，并确保在重绘屏幕之前执行该回调函数。可以通过对 requestAnimationFrame 函数的链式调用实现动画循环：

```javascript
(function drawFrame(){
	window.requestAnimationFrame(drawFrame, canvas);
	
	// animation code
}());
```

&#160; &#160; &#160; &#160;上面的代码，定义了drawFrame函数，包含了每帧要执行的动画代码，第一行调用了window.requestAnimationFrame 函数，将drawFrame函数自身的引用作为参数传入。第二个可选参数是要绘制的canvas。

&#160; &#160; &#160; &#160;当执行drawFrame函数时，window.requestAnimationFrame 将drawFrame函数放入队列等待下一个动画间隔中再次执行，而它再次执行时又会重复着一过程。由于不断的请求执行该函数，因此串联成了一个循环。

{{site.data.alerts.tip}}为了启动循环，在定义好 drawFrame 函数后，就用一个圆括号将其包起来并立即调用它，这是利用JavaScript立即执行函数的简略写法，但使用上存在争议。更为传统的方法是定义好函数后，再下一行调用它。{{site.data.alerts.end}}

&#160; &#160; &#160; &#160;由于 requestAnimationFrame 是一个相对新的功能，因此目前的浏览器还致力于各自的实现。如果希望代码具备更好的跨平台性，下面一段代码可以用来规范该函数在不同浏览器中的实现。

```javascript
if (!window.requestAnimationFrame) {
  window.requestAnimationFrame = (window.webkitRequestAnimationFrame ||
                                  window.mozRequestAnimationFrame ||
                                  window.msRequestAnimationFrame ||
                                  window.oRequestAnimationFrame ||
                                  function (callback) {
                                    return window.setTimeout(callback, 17 /*~ 1000/60*/);
                                  });
```

