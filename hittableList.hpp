#ifndef HITTABLE_LIST_HPP
#define HITTABLE_LIST_HPP

#include "hittable.hpp"

#include <memory>
#include <vector>

class HittableList : public Hittable
{
public:
	HittableList()
	{}

	HittableList(std::shared_ptr<Hittable> object)
	{
		add(object);
	}

	void clear()
	{
		objects.clear();
	}

	void add(std::shared_ptr<Hittable> object)
	{
		objects.emplace_back(object);
	}

	virtual bool hit(
		Ray const& r,
		double t_min,
		double t_max,
		HitRecord& record) const override
	{
		HitRecord rec;
		bool hit_anything = false;
		double closest = t_max;

		for (auto const& object : objects)
		{
			if (object->hit(r, t_min, closest, rec))
			{
				hit_anything = true;
				closest = rec.t;
				record = rec;
			}
		}

		return hit_anything;
	}

private:
	std::vector<std::shared_ptr<Hittable>> objects;
};

#endif // HITTABLE_LIST_HPP

