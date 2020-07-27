#include "hittable_list.h"
using namespace rtLib;

constexpr double T0 {0.0};
constexpr double T1 {1.0};

hittable_list GenerateRandomScene();
hittable_list TwoPerlinSpheres();
hittable_list Earth();
hittable_list SimpleLight();
hittable_list CornellBox();
hittable_list CornellSmoke();
hittable_list CrazyScene();
