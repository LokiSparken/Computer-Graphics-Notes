#ifndef HITABLELIST
#define HITABLELIST

#include "hitable.h"

/* 
    可命中物体列表类。
    继承自抽象的命中类hitable，所以也要实现hit接口。
*/
class hitable_list: public hitable
{
public:
    hitable_list() {}
    hitable_list(hitable **l, int n) { list = l; list_size = n; }
    virtual bool hit(const ray &r, float tmin, float tmax, hit_record &rec) const;
    
    hitable **list; // 列表中为指向可命中物体的指针数组
    int list_size;  // 并记录当前列表中存在多少可命中物体
};

/* 【功能】计算一束观察者光线和当前世界中所有物体的交点。
    因此对列表而言，就是遍历列表中每个物体，让光线与其求交点，并缩小需求参数范围，取离观察者最近的交点。
    遍历过程中对符合条件的都暂时记录，并更新。2333朴素了！求最值嘛[瘫.jpg](嘤嘤嘤这也太难了(不
 */
bool hitable_list::hit(const ray &r, float tmin, float tmax, hit_record &rec) const
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