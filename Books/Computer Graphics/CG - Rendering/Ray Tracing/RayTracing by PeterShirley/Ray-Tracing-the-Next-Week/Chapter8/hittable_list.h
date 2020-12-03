#ifndef HITTABLELISTH
#define HITTABLELISTH

#include "hittable.h"

/* 
    可命中物体列表类。
    继承自抽象的命中类hittable，所以也要实现hit接口。
*/
class hittable_list: public hittable
{
public:
    hittable_list() {}
    hittable_list(hittable **l, int n) { list = l; list_size = n; }
    virtual bool hit(const ray &r, float tmin, float tmax, hit_record &rec) const;
    virtual bool bounding_box(float t0, float t1, aabb &box) const;
    
    hittable **list; // 列表中为指向可命中物体的指针数组
    int list_size;  // 并记录当前列表中存在多少可命中物体
};

/* 【功能】从某小包围盒衍生大盒。 */
bool hittable_list::bounding_box(float t0, float t1, aabb &box) const
{
    if (list_size < 1) return false;    // 空表
    aabb temp_box;
    bool first_true = list[0]->bounding_box(t0, t1, temp_box);  // 若list[0]中是个可击中物体，则会生成其包围盒赋给temp_box并返回true
    if (!first_true) return false;  // 其它情况
    else box = temp_box;    // 无异常
    
    for (int i = 1; i < list_size; i++)
    {
        if(list[i]->bounding_box(t0, t1, temp_box)) // 逐个判断list[i]的情况，无异常则生成更大的包围盒
            box = surrounding_box(box, temp_box);   // in "aabb.h"
        else
            return false;
    }

    return true;
}

/* 【功能】计算一束观察者光线和当前世界中所有物体的交点。
    因此对列表而言，就是遍历列表中每个物体，让光线与其求交点，并缩小需求参数范围，取离观察者最近的交点。
    遍历过程中对符合条件的都暂时记录，并更新。2333朴素了！求最值嘛[瘫.jpg](嘤嘤嘤这也太难了(不
 */
bool hittable_list::hit(const ray &r, float tmin, float tmax, hit_record &rec) const
{
    hit_record temp_rec;
    bool hit_anything = false;      // 标记这束观察者光线有没有命中物体
    double closest_so_far = tmax;
    for (int i = 0; i < list_size; i++)
    {
        // 每个可命中物体再调用它们自身的hit函数接口。[成了！.jpg]
        if (list[i]->hit(r, tmin, closest_so_far, temp_rec))
        {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    // 当有命中物体时调用处知道结果，并从&rec中得到相关数据
    return hit_anything;
}

#endif