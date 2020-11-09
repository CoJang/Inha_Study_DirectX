
//--------------------------------------------------------------//
// ToonShader
//--------------------------------------------------------------//
//--------------------------------------------------------------//
// Pass 0
//--------------------------------------------------------------//

float4x4 gWorldMatrix : World;
float4x4 gViewMatrix : View;
float4x4 gProjectionMatrix : Projection;
float4x4 gInvWorldMatrix : WorldInverse;

float4 gWorldLightPos = float4( 500.00, 500.00, -500.00, 1.00 );
float4 gWorldCameraPos : ViewPosition;

struct VS_INPUT 
{
   float4 mPosition : POSITION0;
   float3 mNormal   : NORMAL;
   float2 mUV       : TEXCOORD0;
};

struct VS_OUTPUT 
{
   float4 mPosition   : POSITION0;
   float2 mUV         : TEXCOORD0;
   float3 mDiffuse    : TEXCOORD1;
};

VS_OUTPUT VS( VS_INPUT Input )
{
   VS_OUTPUT Output;

   Output.mPosition = mul(Input.mPosition, gWorldMatrix);
   Output.mPosition = mul(Output.mPosition, gViewMatrix);
   Output.mPosition = mul(Output.mPosition, gProjectionMatrix);

   float3 objectLightPosition = mul(gWorldLightPos, gInvWorldMatrix);
   float3 lightDir = normalize(Input.mPosition.xyz - objectLightPosition);

   Output.mDiffuse = dot(-lightDir, normalize(Input.mNormal));

   return( Output );
}


struct PS_INPUT
{
   float2 mUV         : TEXCOORD0;
   float3 mDiffuse    : TEXCOORD1;
};

texture DiffuseMap_Tex;

sampler2D DiffuseSampler = sampler_state
{
   Texture = (DiffuseMap_Tex);
};

float4 PS(PS_INPUT Input) : COLOR0
{   
   float4 albedo = tex2D(DiffuseSampler, Input.mUV);

   return albedo;
}




//--------------------------------------------------------------//
// Technique Section for ToonShader
//--------------------------------------------------------------//
technique ToonShader
{
   pass Pass_0
   {
      VertexShader = compile vs_2_0 VS();
      PixelShader = compile ps_2_0 PS();
   }

}

