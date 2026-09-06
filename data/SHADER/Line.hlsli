// Line.hlsli
#ifndef __LINE_HLSLI__
#define __LINE_HLSLI__

// --------------------------------------------------------
// 定数バッファ (スロット番号を固定管理)
// --------------------------------------------------------

// b1: ビュー・プロジェクション行列 (VSで使用)
cbuffer VPMatrixBuffer : register(b0)
{
    row_major matrix View;
    row_major matrix Proj;
}

// --------------------------------------------------------
// シェーダー間データ (VS -> PS)
// --------------------------------------------------------
struct PS_INPUT
{
    float4 Position : SV_POSITION;
    float4 Color : COLOR;
};

#endif
