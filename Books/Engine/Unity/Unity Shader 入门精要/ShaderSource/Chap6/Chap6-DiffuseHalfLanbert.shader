// Upgrade NOTE: replaced '_World2Object' with 'unity_WorldToObject'
// Upgrade NOTE: replaced 'mul(UNITY_MATRIX_MVP,*)' with 'UnityObjectToClipPos(*)'

Shader "Unity Shaders Book/Chapter 6/DiffuseHalfLambert"
{
	properties
	{
		_Diffuse("Diffuse", Color) = (1, 1, 1, 1)
	}
		SubShader
	{
		Pass
		{
			Tags { "LightMode" = "ForwardBase"}

			CGPROGRAM

			#pragma vertex vert
			#pragma fragment frag

			#include "Lighting.cginc"
			fixed4 _Diffuse;

			struct a2v
			{
				float4 vertex : POSITION;
				float3 normal : NORMAL;
			};

			struct v2f
			{
				float4 pos : SV_POSITION;
				fixed3 worldNormal : TEXCOORD0;
			};

			v2f vert(a2v v)
			{
				v2f output;
				// 1. 将顶点坐标做MVP变换，从模型空间变换到裁剪空间
				output.pos = UnityObjectToClipPos(v.vertex);
				// 2. 计算法线的世界空间表示
				output.worldNormal = normalize(mul(v.normal, (float3x3)unity_WorldToObject));
				return output;
			}

			fixed4 frag(v2f input) : SV_Target
			{
				// 1. 获取环境光
				fixed3 ambient = UNITY_LIGHTMODEL_AMBIENT.xyz;
				// 2. 归一化法线和光源方向
				fixed3 worldNormal = normalize(input.worldNormal);
				fixed3 worldLight = normalize(_WorldSpaceLightPos0.xyz);
				// 3. 计算漫反射项
                fixed halfLambert = 0.5 * dot(worldNormal, worldLight) + 0.5;
				fixed3 diffuse = _LightColor0.rgb * _Diffuse.rgb * halfLambert;

				fixed3 color = ambient + diffuse;
				return fixed4(color, 1.0);
			}

			ENDCG
		}
	}
		Fallback "Diffuse"
}