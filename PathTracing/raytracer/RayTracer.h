#ifndef __RAYTRACER_H__
#define __RAYTRACER_H__
#include <thread>
#include <mutex>
#include "Scene.h"
#include "Ray.h"

class RayTracer
{
public:
	RayTracer();
	~RayTracer();
	void run(const char* obj_file);
	Color3** render();
	Scene* getScene();

private:
	Color3 trace(Ray& ray,int currDepth = 0,Vec3 weight = Vec3(1,1,1));
	Ray mcSelect(Ray& ray,IntersectResult& result);
	Vec3 importanceSampleUpperHemisphere(Vec3& upVector, double n=-1);

	//TODO blockSize
	int blockSize;//像素块大小
	int pxSampleNum;//每个像素的采样数目
	int mcSampleNum;//蒙特卡洛采样数目
	int threadNum;//渲染线程数目
	int maxRecursiveDepth;//光线最大递归深度

	Scene scene;
};

#endif