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
	float3 cameraPosition;
	float padding; // No se usa
}

//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
struct VS_INPUT
{
    float4 Pos : POSITION;
    float2 Tex : TEXCOORD0;
	float3 Normal : NORMAL0;
	float3 Tangent: TANGENT;
};

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float2 Tex : TEXCOORD0;
	float3 Normal : NORMAL0;
	float3 Tangent : TANGENT;
	float3 Binormal : BINORMAL;
	float3 ViewDirection : TEXCOORD1;
};

Texture2D txDiffuse : register( t0 );
Texture2D txNormal : register( t1 );
SamplerState samLinear : register( s0 );

float3 computeTangentSpaceNormal(PS_INPUT input)
{
	float3 finalNormal;
	float3 normalMap;

	// Inicializo el vector final con el valor de entrada
	finalNormal = input.Normal;

	// Obtengo el color del pixel del normal map
	normalMap = txNormal.Sample( samLinear, input.Tex);

	// Esto se hace porque recuerda que el rango de los valores de un texel
	// van de 0 a 1. Para este cálculo necesitamos que ese rango sea de -1 a 1
	normalMap = ( normalMap * 2.0f) - 1.0f;

	// Obtenemos la matriz que me contiene el tangent space
	float3x3 TBN = float3x3( input.Tangent, input.Binormal,  input.Normal );

	// Calculamos el vector normal final y lo normalizamos
	normalMap = mul(normalMap, TBN);
	finalNormal = normalize(normalMap);

	return finalNormal;
}


//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VS( VS_INPUT input )
{
	float4 worldPosition;

	// Se cambia el vector de posicion
	// para que los calculos de matrices
	// se hagan apropiadamente
	worldPosition.w = 1.0f;

    PS_INPUT output = (PS_INPUT)0;
    output.Pos = mul( input.Pos, World );
    output.Pos = mul( output.Pos, View );
    output.Pos = mul( output.Pos, Projection );
    output.Tex = input.Tex;

	// Damos las transformaciones necesarias a las normales
	output.Normal = normalize(mul( input.Normal, (float3x3)World ));

	// Damos las transformaciones necesarias a la tangente
	// RECUERDA: las tangentes y binormales son vectores paralelos a la superfice del poligono
	output.Tangent = normalize(mul( input.Tangent, (float3x3)World ));

	// Calculamos la binormal de este vertice
	output.Binormal = normalize(cross( output.Normal, output.Tangent ));

	// Obtenemos la posicion del vertice
	worldPosition = mul(input.Pos, World);

	// Calculamos el vector de direccion desde el vertice hasta la camara
	output.ViewDirection = normalize(cameraPosition.xyz - worldPosition.xyz);
    
    return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS( PS_INPUT input) : SV_Target
{	
	float3 lightDirection;
	float lightIntensity;

	float specularPower;
	float4 specularColor;
	float specularLighting;

	float4 textureColor;
	float4 outputColor;

	float3 reflectionVector;

	// Inicializamos el specularPower
	specularPower = .8f;

	// Inicializamos el color de salida con el ambient color
	outputColor = float4(0.1f, 0.1f, 0.1f, 1.0f);

	// Obtenemos el color correspondiente al vertice
	textureColor = txDiffuse.Sample( samLinear, input.Tex );

	// Inicializamos la direccion de la luz
	lightDirection = float3(1.0f, -1.0f, 1.0f);

	// Invertimos el vector para llevar a cabo los calculos
	lightDirection = -lightDirection;

	// Calculamos la normal de acuerdo al mapa de normales y su tangent space
	input.Normal = computeTangentSpaceNormal(input);

	// Obtenemos la intensidad de luz que recibe el vertice de acuerdo a su normal
	// y a la direccion de la luz
	lightIntensity = saturate(dot(input.Normal, lightDirection));

	// Le llega luz al vertice?
	if(lightIntensity > 0.0f)
	{
		// Obtenemos el color iluminado de acuerdo a la intensidad de luz
		// que recibe el vertice. RECUERDA: el primer parametro es el diffuse color
		outputColor += float4(1.0f, 1.0f, 1.0f, 1.0f) * lightIntensity;
		outputColor = saturate(outputColor);

		// Se calcula el vector de refraccion con la sig. formula:
		//		ReflectionVector = 2 * LightIntensity * VertexNormal - LightDirection
		reflectionVector = normalize(2 * lightIntensity * input.Normal - lightDirection);

		// Determinamos la cantidad de luz specular:
		//		SpecularLighting = SpecularLightColor * (ViewingDirection dot ReflectionVector) power SpecularReflectionPower
		// En este caso, no pondremos el SpecularLightColor, y se dejara la luz blanca
		specularLighting = pow(saturate(dot(reflectionVector, input.ViewDirection)), specularPower);
	}

	// Difuminamos el color del vertice de acuerdo a la
	// cantidad de luz que se recibe
	outputColor = outputColor * textureColor;

	// Agregamos el componente specular
	outputColor = saturate(outputColor + specularLighting);

    //return txDiffuse.Sample( samLinear, input.Tex );
	return outputColor;
}
