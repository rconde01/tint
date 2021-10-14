RWTexture2D<float4> t_rgba8unorm : register(u0, space0);
RWTexture2D<float4> t_rgba8snorm : register(u1, space0);
RWTexture2D<uint4> t_rgba8uint : register(u2, space0);
RWTexture2D<int4> t_rgba8sint : register(u3, space0);
RWTexture2D<uint4> t_rgba16uint : register(u4, space0);
RWTexture2D<int4> t_rgba16sint : register(u5, space0);
RWTexture2D<float4> t_rgba16float : register(u6, space0);
RWTexture2D<uint4> t_r32uint : register(u7, space0);
RWTexture2D<int4> t_r32sint : register(u8, space0);
RWTexture2D<float4> t_r32float : register(u9, space0);
RWTexture2D<uint4> t_rg32uint : register(u10, space0);
RWTexture2D<int4> t_rg32sint : register(u11, space0);
RWTexture2D<float4> t_rg32float : register(u12, space0);
RWTexture2D<uint4> t_rgba32uint : register(u13, space0);
RWTexture2D<int4> t_rgba32sint : register(u14, space0);
RWTexture2D<float4> t_rgba32float : register(u15, space0);

[numthreads(1, 1, 1)]
void main() {
  t_rgba8unorm;
  t_rgba8snorm;
  t_rgba8uint;
  t_rgba8sint;
  t_rgba16uint;
  t_rgba16sint;
  t_rgba16float;
  t_r32uint;
  t_r32sint;
  t_r32float;
  t_rg32uint;
  t_rg32sint;
  t_rg32float;
  t_rgba32uint;
  t_rgba32sint;
  t_rgba32float;
  return;
}
