float4x4 World;
float4x4 View;
float4x4 Projection;
float4x4 WVP;
texture2D Texture; 

cbuffer cbAnimMatrices{
	float3x4 matGlobal[64];
	float3x4 matGlobalSkeleton[64];
}
Texture2D gDiffuseMap;

struct VertexShaderInput
{
    float4 Position : POSITION0;
    float4 Normal:	NORMAL0;
    float2 TextureCoord: TEXCOORD0;
    float2 TextureCoord2: TEXCOORD1;
    float4 index : BLENDINDICES;
    float4 weight: BLENDWEIGHT;
};
struct VertexShaderOutput
{
    float2 TextureCoord: TEXCOORD0;
    float4 Position : SV_POSITION;
};


float DotProduct(in float4 x, in float4 y) {
    return x[0] * y[0] + x[1] * y[1] + x[2] * y[2];
}

void VectorRotate(in float4 in1, in float3x4 in2, out float4 rez) {
    rez[0] = DotProduct(in1, in2[0]);
    rez[1] = DotProduct(in1, in2[1]);
    rez[2] = DotProduct(in1, in2[2]);
    rez[3]=1;
}

void VectorIRotate(in float4 in1, in float3x4 in2, out float4 rez) {
    rez[0] = in1[0] * in2[0][0] + in1[1] * in2[1][0] + in1[2] * in2[2][0];
    rez[1] = in1[0] * in2[0][1] + in1[1] * in2[1][1] + in1[2] * in2[2][1];
    rez[2] = in1[0] * in2[0][2] + in1[1] * in2[1][2] + in1[2] * in2[2][2];
    rez[3]=0;
}

void VectorTransform(in float4 in1,in float3x4 in2, out float4 rez) {
    rez[0] = DotProduct(in1, in2[0]) + in2[0][3];
    rez[1] = DotProduct(in1, in2[1]) + in2[1][3];
    rez[2] = DotProduct(in1, in2[2]) + in2[2][3];
    rez[3]=0;
}

void VectorITransform(in float4 in1, in float3x4 in2, out float4 rez) {
    float4 tmp;
    tmp[0] = in1[0] - in2[0][3];
    tmp[1] = in1[1] - in2[1][3];
    tmp[2] = in1[2] - in2[2][3];
    tmp[3]=0;
    VectorIRotate(tmp, in2, rez);
}

VertexShaderOutput VS(VertexShaderInput input)
{
    VertexShaderOutput output;

    float4 transformedPosition = float4(0.0,0,0,0);
    float3 transformedNormal = float3(0.0,0,0);
    float4 worldPosition = mul(input.Position, World);
    float4 viewPosition = mul(worldPosition, View);
    output.Position = mul(viewPosition, Projection);
	output.TextureCoord=input.TextureCoord;

    return output;
}

SamplerState gTriLinearSam 
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};



float4 PS(VertexShaderOutput input) : SV_TARGET 
{
	float4 diffuse = gDiffuseMap.Sample( gTriLinearSam, input.TextureCoord );
	//float4 diffuse = float4( 0.5 , 0.5 , 0.5, 0.5);
	//float4 diffuse = float4( 1.0 , 1.0 , 1.0, 1.0);
	return diffuse ;
}

VertexShaderOutput VertexShaderFunction2(VertexShaderInput input)
{
    VertexShaderOutput output;

	float4 transformedPosition = float4(0.0,0,0,0);
    float3 transformedNormal = float3(0.0,0,0);

    float4 curIndex = input.index;
    float4 curWeight = input.weight;

    for (int i = 0; i < 4; i++)
    {
        float3x4 g44 = matGlobal[int(curIndex.x)];
        float3x4 s44 = matGlobalSkeleton[int(curIndex.x)];
        float4 vert = float4(0,0,0,0);
        float4 norm = float4(0,0,0,0);
        float4 tmpNorm = float4(0,0,0,0);
        float4 tmpVert = float4(0,0,0,0);

        VectorITransform(input.Position, s44, tmpVert);
        VectorTransform(tmpVert, g44, vert);//g
        vert[3]=1;
        transformedPosition += vert * curWeight.x;

        float4 preNormal=float4(input.Normal.xyz,1);
        VectorIRotate(preNormal, s44, tmpNorm);
        VectorRotate(tmpNorm, g44, norm);
        norm[3]=1;
        transformedNormal += float3(norm.xyz) * curWeight.x;

        // shiftam sa avem urmatoarele valori pentru pondere si indice de os
        curIndex = curIndex.yzwx;
        curWeight = curWeight.yzwx;
    }
    float4 worldPosition = mul(transformedPosition, World);
    float4 viewPosition = mul(worldPosition, View);
    output.Position = mul(viewPosition, Projection);
	output.TextureCoord=input.TextureCoord;

    return output;
}

technique11 MS3DShader
{
    pass P0
    {
		SetVertexShader( CompileShader( vs_4_0, VS() ) );
        SetGeometryShader( NULL ) ; 
		SetHullShader( NULL ) ; 
		SetDomainShader( NULL ) ; 
        SetPixelShader( CompileShader( ps_4_0, PS() ) );
	SetComputeShader( NULL ) ;


    }
    pass P1
    {
    		SetVertexShader( CompileShader( vs_4_0, VertexShaderFunction2() ) );
        SetGeometryShader( NULL ) ; 
		SetHullShader( NULL ) ; 
		SetDomainShader( NULL ) ; 
        SetPixelShader( CompileShader( ps_4_0, PS() ) );
	SetComputeShader( NULL ) ;
    }
}
