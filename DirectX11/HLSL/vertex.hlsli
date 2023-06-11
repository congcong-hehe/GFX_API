struct VertexIn_pos_color
{
    float3 pos : POSITION;
    float4 color : COLOR;
};

struct VertexOut_pos_color
{
    float4 posH : SV_POSITION;
    float4 color : COLOR;
};

struct VertexIn_pos
{
    float3 pos : POSITION;
};

struct VertexOut_pos
{
    float4 posH : SV_POSITION;
};