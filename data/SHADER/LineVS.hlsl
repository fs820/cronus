// 3DPolygonVS.hlsl
#include "Line.hlsli"

// 入力頂点データ: C++の Vertex3D 構造体と対応させる
struct VS_INPUT
{
    float3 Position : POSITION;
    float4 Color : COLOR;
};

//--------------------------------------------------------------------------------------
// 頂点シェーダー (Vertex Shader)
// 座標変換を担当
//--------------------------------------------------------------------------------------
PS_INPUT VS(VS_INPUT input)
{
    PS_INPUT output;
    // ライン頂点は既にワールド座標系として渡すため、View * Proj のみ適用
    float4 worldPos = float4(input.Position, 1.0f);
    float4 viewPos = mul(worldPos, View);
    output.Position = mul(viewPos, Proj);
    output.Color = input.Color;
    return output;
}
