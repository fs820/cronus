// GeometryPS.hlsl
#include "Common.hlsli"

// エントリーポイント: PS
float PS(PS_INPUT input) : SV_Depth
{
    // テクスチャの色とマテリアルの色を合成
    float4 baseColor = myTexture.Sample(mySampler, input.UV) * input.Color * MaterialDiffuse;

    // アルファカットオフ
    clip(baseColor.a - MaterialAlphaCutoff);

    return input.Pos.z;
}
