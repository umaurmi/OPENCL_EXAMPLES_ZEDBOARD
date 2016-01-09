__kernel void negative(__global float *dst, __global float* src, int n)
{
    unsigned int xgid = get_global_id(0);
    unsigned int ygid = get_global_id(1);

    unsigned int iid = ygid * n + xgid;
    unsigned int oid = xgid * n + ygid;

    dst[iid] = 255 - src[iid];

}


