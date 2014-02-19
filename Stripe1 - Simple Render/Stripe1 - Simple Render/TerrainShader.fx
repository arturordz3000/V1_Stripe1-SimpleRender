//--------------------------------------------------------------------------------------
// File: CubeShader.fx
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
cbuffer ConstantBuffer : register( b0 )
{
	matrix World;
	matrix View;
	matrix Projection;
}

//--------------------------------------------------------------------------------------
struct VS_INPUT
{
    float4 pos : POSITION;
	float2 tex0 : TEXCOORD0;
	float2 blendTex : TEXCOORD1;
	float3 normal : NORMAL0;
};

struct PS_INPUT
{
	float4 pos : SV_POSITION;
	float2 tex0 : TEXCOORD0;
	float2 blendTex : TEXCOORD1;
	float3 normal : NORMAL0;
};

Texture2D colorMap : register(t0);
Texture2D colorMap2 : register(t1);
Texture2D blendMap : register(t2);
SamplerState samplerLinear : register( s0 );

PS_INPUT VS(VS_INPUT vertex)
{
	PS_INPUT vsOut = (PS_INPUT)0;
	vsOut.pos = mul(vertex.pos, World);
	vsOut.pos = mul(vsOut.pos, View);
	vsOut.pos = mul(vsOut.pos, Projection);

	vsOut.tex0 = vertex.tex0;
	vsOut.blendTex = vertex.blendTex;
	vsOut.normal = normalize(mul(vertex.normal, World));

	return vsOut;
}

float4 PS(PS_INPUT pix) : SV_TARGET
{
	float3 ambient = float3(0.1f, 0.1f, 0.1f);

	float4 text = colorMap.Sample(samplerLinear, pix.tex0);
	float4 text2 = colorMap2.Sample(samplerLinear, pix.tex0);

	/////////////////////////BLEND MAPPING/////////////////////////////////////

	/**
	*	El siguiente código obtiene un valor de blend
	*	de acuerdo a un blendmap, aunque también se puede
	*	poner directamente si así lo deseamos (código comentado)
	**/

	//float4 alphaBlend = float4(0.7f, 0.7f, 0.7f, 1.0f);
	float4 alphaBlend = blendMap.Sample(samplerLinear, pix.blendTex);	

	float4 textf = (text * alphaBlend) + ((1.0 - alphaBlend) * text2);

	//////////////////////////////////////////////////////////////////////////

	float3 DiffuseDirection = float3(0.0f, -1.0f, 0.2f);
	float4 DiffuseColor = float4(1.0f, 1.0f, 1.0f, 1.0f);
	float3 diffuse = dot(-DiffuseDirection, pix.normal);
	diffuse = saturate(diffuse*DiffuseColor.rgb);
	diffuse = saturate(diffuse+ambient);

	float4 fColor = float4(textf.rgb*diffuse, 1.0f);

	return fColor;
}
