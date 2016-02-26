#include "PointLight.h"

Color3 PointLight::render(IntersectResult& result,Ray& ray,Scene* scene)
{
	Color3 rgb;
	MaterialAttribute& attr = result.primitive->attr;
	Vec3 r = origin-result.point;
	double rr = Length(r);

	if(!scene->isInShadow(Ray(result.point-ray.direction*EPS,r),this))
	{
		//calculate the diffuse color
		Vec3 s = Normalize(r);
		double mDots = Dot(s,result.normal);
		if(mDots>0.0) rgb+= (mDots*attr.kd).multiple(attr.color);

		//calculate the specular color
		Vec3 v = ray.direction.flip();
		Vec3 h = Normalize(s+v);
		double mDotH = Dot(h,result.normal);
		if(mDotH>0.0) rgb+= (pow(mDotH,attr.roughness)*attr.ks).multiple(attr.emission);
	}

	return rgb;
}