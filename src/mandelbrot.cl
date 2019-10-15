float	map(float current, float end, float new_start, float new_end)
{
	return (current / end * (new_end - new_start) + new_start);
}

__kernel void render(__global int *out) {
  int i = get_global_id(0) / 1920;
  int j = get_global_id(0) % 1920;
  float x_z = map(j, 1920, -2.5, 1);
			float y_z = map(i, 1080, -1, 1);
			float x = 0;
			float y = 0;
			int iter = 0;
			float x_temp;
			while (x*x + y*y <= 4 && iter < 256)
			{
				x_temp = x*x - y*y + x_z;
				y = 2*x*y + y_z;
				x = x_temp;
				iter++;
			}
			if (iter == 256)
			{
				out[i * 1920 + j] = 0;
			}
			else
			{
				out[i * 1920 + j] = iter;
			}
}
