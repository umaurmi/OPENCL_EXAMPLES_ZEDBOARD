__kernel void power_law(__global float *dst, __global float* src, int n, float gamma)
{
    unsigned int xgid = get_global_id(0);
    unsigned int ygid = get_global_id(1);

    unsigned int iid = ygid * n + xgid;

    unsigned int C = 1;
        
    dst[iid] = C * (pow(src[iid],gamma));
    
}


