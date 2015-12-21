#define PI       3.14159265358979323846
#define PI_2     1.57079632679489661923

__kernel void transpose(__global float *dst, __global float* src, int n)
{
    unsigned int xgid = get_global_id(0);
    unsigned int ygid = get_global_id(1);

    unsigned int iid = ygid * n + xgid;
    unsigned int oid = xgid * n + ygid;

    dst[iid] = 255 - src[iid];

}


