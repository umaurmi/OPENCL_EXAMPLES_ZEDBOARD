__kernel void logtrns(__global float *dst, __global float* src, int n)
{
    unsigned int xgid = get_global_id(0);
    unsigned int ygid = get_global_id(1);

    unsigned int iid = ygid * n + xgid;

    unsigned int C = 100; //calculated as 255/(log(1+R)) where R is max pixel value of input
    
    dst[iid] = C * (log10(src[iid]+1));
    
}


