---
title: 本章重要公式
last_updated: February 25, 2016
summary: "动画中常用的三角函数总结"
---

## 三角函数基础

```javascript
sine_of_angle = opposite / hypotense
cosine_of_angle = adjacent / hypotense
tangent_of_angle = opposite / adjacent
```

## 角度与弧度转换

```javascript
radians = degrees * Math.PI / 180
degrees = radians * 180 / Math.PI
```

## 朝鼠标(或任意一点)旋转

```javascript
dx = mouse.x - object.x;
dy = mouse.y - object.y;
object.rotation = Math.atan2(dy, dx) * 180 / Math.PI;
```

## 创建正弦波

```javascript
(function drawFrame(){
	window.requestAnimationFrame(drawFrame, canvas);
	
	value = center + Math.sin(angle) * range;
	angle += speed;
}());
```

## 创建圆周

```javascript
(function drawFrame(){
	window.requestAnimationFrame(drawFrame, canvas);
	
	xposition = centerX + Math.cos(angle) * radius;
	yposition = centerY + Math.sin(angle) * radius;
	angle += speed;
}());
```

## 创建椭圆

```javascript
(function drawFrame(){
	window.requestAnimationFrame(drawFrame, canvas);
	
	xposition = centerX + Math.cos(angle) * radiusX;
	yposition = centerY + Math.sin(angle) * radiusY;
	angle += speed;
}());
```

## 获取两点间距离

```javascript
dx = x2 - x1;
dy = y2 - y1;
dist = Math.sqrt(dx * dx + dy * dy);
```