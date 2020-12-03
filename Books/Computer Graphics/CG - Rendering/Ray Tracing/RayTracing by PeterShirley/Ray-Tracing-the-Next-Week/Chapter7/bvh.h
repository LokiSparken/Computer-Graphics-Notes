#ifndef BVHH
#define BVHH

#include <iostream>
#include "hittable.h"
#include "mymath.h"


class bvh_node : public hittable
{
public:
    bvh_node() {}
    bvh_node(hittable **l, int n, float time0, float time1);
    virtual bool hit(const ray &r, float tmin, float tmax, hit_record &rec) const;
    virtual bool bounding_box(float t0, float t1, aabb &b) const;

    hittable *left, *right;
    aabb box;
};

/* 【功能】获取当前结点的包围盒box。 */
bool bvh_node::bounding_box(float t0, float t1, aabb &b) const
{
    b = box;
    return true;
}

/* 【功能】光线递归射击BVH树上结点， */
bool bvh_node::hit(const ray &r, float tmin, float tmax, hit_record &rec) const
{
    if (box.hit(r, tmin, tmax))
    {
        // printf("hit box:\n");
        // cout << "node: ([" << box.min().x() << ", " << box.min().y() << ", " << box.min().z() << "], [" << box.max().x() << ", " << box.max().y() << ", " << box.max().z() << "])\n";

        hit_record left_rec, right_rec;
        bool hit_left = left->hit(r, tmin, tmax, left_rec);
        bool hit_right = right->hit(r, tmin, tmax, right_rec);
        if (hit_left && hit_right)  // 光线命中两包围盒重叠部分
        {
            if (left_rec.t < right_rec.t)   // 取参数t值小的，即离观察者近的渲染到屏幕
                rec = left_rec;
            else
                rec = right_rec;
            return true;
        }
        else if (hit_left)
        {
            rec = left_rec;
            return true;
        }
        else if (hit_right)
        {
            rec = right_rec;
            return true;
        }
        else
            return false;
    }
    
    return false;  // 直到遇到光线无法命中的包围盒返回。
}

/* 【功能】按两包围盒较小边界的x坐标排序。 */
int box_x_compare(const void *a, const void *b)
{
    aabb box_left, box_right;
    hittable *ah = *(hittable**)a, *bh = *(hittable**)b;
    if (!ah->bounding_box(0, 0, box_left) || !bh->bounding_box(0, 0, box_right))  // 确认结点无异常
        std::cerr << "no bounding box in bvh_node constructor\n";
    if (box_left.min().x() - box_right.min().x() < 0.0)
        return -1;
    else
        return 1;
}

int box_y_compare(const void *a, const void *b)
{
    aabb box_left, box_right;
    hittable *ah = *(hittable**)a, *bh = *(hittable**)b;
    if (!ah->bounding_box(0, 0, box_left) || !bh->bounding_box(0, 0, box_right))  // 确认结点无异常
        std::cerr << "no bounding box in bvh_node constructor\n";
    if (box_left.min().y() - box_right.min().y() < 0.0)
        return -1;
    else
        return 1;
}

int box_z_compare(const void *a, const void *b)
{
    aabb box_left, box_right;
    hittable *ah = *(hittable**)a, *bh = *(hittable**)b;
    if (!ah->bounding_box(0, 0, box_left) || !bh->bounding_box(0, 0, box_right))  // 确认结点无异常
        std::cerr << "no bounding box in bvh_node constructor\n";
    if (box_left.min().z() - box_right.min().z() < 0.0)
        return -1;
    else
        return 1;
}

/* 【功能】BVH建树。 */
void debug_bvh_constructor(aabb &box, aabb &box_left, aabb &box_right)
{
    cout << "node: ";   box.print();
    cout << "l: ";      box_left.print();
    cout << "r: ";      box_right.print();
    cout << "\n";
}

bvh_node::bvh_node(hittable **l, int n, float time0, float time1)
{
    // 随机以某轴将管辖的包围盒排序
    int axis = int(3*random_double());
    if (axis == 0)
        qsort(l, n, sizeof(hittable *), box_x_compare);
    else if (axis == 1)
        qsort(l, n, sizeof(hittable *), box_y_compare);
    else
        qsort(l, n, sizeof(hittable *), box_z_compare);
    
    if (n == 1)
    {
        left = right = l[0];    // 避免在hit时对结点的判空
    }
    else if (n == 2)
    {
        left = l[0]; 
        right = l[1];
    }
    else    // 递归构造两子树并得到其指针left、right
    {
        left = new bvh_node(l, n/2, time0, time1);
        right = new bvh_node(l + n/2, n - n/2, time0, time1);
    }

    aabb box_left, box_right;
    // 获取两子结点包围盒信息，防空
    if (!left->bounding_box(time0, time1, box_left) || !right->bounding_box(time0, time1, box_right))
        std::cerr << "no bounding_box in bvh_node constructor\n";
    // 通过两子结点包围盒构造当前结点包围盒
    box = surrounding_box(box_left, box_right);

    // debug_bvh_constructor(box, box_left, box_right);
}


#endif

