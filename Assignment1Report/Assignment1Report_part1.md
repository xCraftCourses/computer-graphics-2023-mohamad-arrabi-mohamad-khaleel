1) bresenham algorithm:
void Renderer::DrawLine(const glm::vec2& p1, const glm::vec2& p2, const glm::vec3& color)
{
	// TODO: Implement bresenham algorithm
	// https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
	float a, e, p, q, x1, y1, x2, y2;
	if (p1.x > p2.x)
	{
		x1 = p2.x; y1 = p2.y;
		x2 = p1.x; y2 = p1.y;
	}
	else
	{
		x1 = p1.x; y1 = p1.y;
		x2 = p2.x; y2 = p2.y;
	}
	if (p1.x != p2.x)
		a = (float)(y2 - y1) / (float)(x2 - x1);
	p = x2 - x1; q = y2 - y1;
	e = -1 * p;
	if (x1 == x2)
	{
		if (q > 0)
		{
			while (y1 < y2 || y1 == y2)
			{
				PutPixel(x1, y1, color);
				y1++;
			}
		}
		else if (q < 0)
		{
			while (y1 > y2 || y1 == y2)
			{
				PutPixel(x1, y1, color);
				y1--;
			}
		}
	}
	else
	{
		if (a == 1)
		{
			while (x1 < x2 || x1 == x2)
			{
				PutPixel(x1, y1, color);
				x1++;
				y1++;
			}
		}
		if (a == 0)
		{
			while (x1 < x2 || x1 == x2)
			{
				PutPixel(x1, y1, color);
				x1++;
			}
		}
		if (a == -1)
		{
			while (x1 < x2 || x1 == x2)
			{
				PutPixel(x1, y1, color);
				x1++;
				y1--;
			}
		}
		if (0 < a && a < 1)
		{
			while (x1 < x2 || x1 == x2)
			{
				if (e > 0)
				{
					y1++;
					e = e - (2 * p);
				}
				PutPixel(x1, y1, color);
				x1++;
				e = e + (2 * q);
			}
		}
		if (a > 1)
		{
			while (y1 < y2 || y1 == y2)
			{
				if (e > 0)
				{
					x1++;
					e = e - (2 * q);
				}
				PutPixel(x1, y1, color);
				y1++;
				e = e + (2 * p);
			}
		}
		if (-1 < a && a < 0)
		{
			e = p;
			while (x1 < x2 || x1 == x2)
			{
				if (e < 0)
				{
					y1--;
					e = e + (2 * p);
				}
				PutPixel(x1, y1, color);
				x1++;
				e = e + (2 * q);
			}
		}
		if (a < -1)
		{
			while (y1 > y2 || y1 == y2)
			{
				if (e > 0)
				{
					x1++;
					e = e + (2 * q);
				}
				PutPixel(x1, y1, color);
				y1--;
				e = e + (2 * p);
			}
		}
	}
}



2) circle picture:
https://github.com/HaifaGraphicsCourses/computer-graphics-2023-mohamad-arrabi-mohamad-khaleel/blob/master/Assignment1Report/circle.png

3) car picture:
https://github.com/HaifaGraphicsCourses/computer-graphics-2023-mohamad-arrabi-mohamad-khaleel/blob/master/Assignment1Report/car.png