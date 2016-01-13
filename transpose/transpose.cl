__kernel void transpose(__global float *dst, __global float* src, int width, int height)
{
    unsigned int xgid = get_global_id(0);
    unsigned int ygid = get_global_id(1);

    unsigned int iid = ygid * width + xgid;
    unsigned int oid = xgid * height + ygid;

    dst[oid] = src[iid];
}

