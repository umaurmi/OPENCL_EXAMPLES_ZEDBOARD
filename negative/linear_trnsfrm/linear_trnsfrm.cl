__kernel void linear_trnsfrm(__global float *dst, __global float* src, int n, int thresh)
//__kernel void linear_trnsfrm(__global float *dst, __global float* src, int n)

{
    unsigned int xgid = get_global_id(0);
    unsigned int ygid = get_global_id(1);

    unsigned int iid = ygid * n + xgid;
    
    /* threshold values :
        for test_image => 10-80;
                          35-70(better clarity)
        for lena       => around 127
        for einstein   => 20-40
        
    */
       
    if( src[iid] > thresh){
       dst[iid] = 255;
    }else {
       dst[iid] = 0;
    }  
             
}


