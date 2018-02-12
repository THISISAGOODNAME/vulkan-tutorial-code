---
title: 本节重要公式
last_updated: February 26, 2016
summary: "本节重要公式是三维透视图、坐标旋转和距离计算"
---

## 基本透视图

```javascript
scale = f1 / (f1 + zpos);
object.scaleX = boject.scaleY = scale;
pbject.alpha = scale; // optional
object.x = vanishingPointX + xpos * scale;
object.y = vanishingPointY + ypos * scale;
```

## Z排序

```javascript
//assumes an array of 3D objects with a zpos property
function zSort(a, b) {
	return (b.zpos - a.zpos)
}

objects.sort(zSort);
```

## 坐标旋转

```javascript
x1 = x * cos(angleZ) - y * sin(angleZ)
y1 = y * cos(angleZ) + x * sin(angleZ)

x1 = x * cos(angleY) - z * sin(angleY)
z1 = z * cos(angleY) + x * sin(angleY)

y1 = y * cos(angleX) - z * sin(angleX)
y1 = z * cos(angleX) + y * sin(angleX)
```

## 三维距离计算

```javascript
dist = Math.sqrt(dx * dx + dy * dy + dz * dz);
```