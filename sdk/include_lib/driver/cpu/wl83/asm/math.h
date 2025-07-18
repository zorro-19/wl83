
//a  : 输入参数 (PI/6)
//aQ : 位宽 (20) 用于定点转浮点
//rsin: 结果
//rcos: 结果
//rQ : 返回位宽
// sin cos函数
void math_cos_sin(int a, int aQ, int *rsin, int *rcos, int *rQ);
void math_arctan(int y, int x, int *rarctan, int *rQ);
void math_arctanh(int y, int x, int *rarctanh, int *rQ);
void math_atan2(int y, int x, int *ratan2, int *rQ);
void math_sinh_cosh(int x, int xQ, int *rsinh, int *rcosh, int *rQ);
void math_exp(int a, int aQ, int *r, int *rQ);
void math_log(int a, int aQ, int *r, int *rQ);
void math_sqrt(int a, int aQ, int *r, int *rQ);
void math_srss(int x, int xQ, int y, int yQ, int *r, int *rQ);
void math_sds(int x, int xQ, int y, int yQ, int *r, int *rQ);

