// Upgrade NOTE: replaced '_Object2World' with 'unity_ObjectToWorld'
// Upgrade NOTE: replaced '_World2Object' with 'unity_WorldToObject'
// Upgrade NOTE: replaced 'mul(UNITY_MATRIX_MVP,*)' with 'UnityObjectToClipPos(*)'

Shader "Unity Shaders Book/Chapter 6/SpecularVertexLevel"
{
	Properties
	{
		// 在材质面板添加属性项
		_Diffuse("Diffuse", Color) = (1, 1, 1, 1)
		_Specular("Specular", Color) = (1, 1, 1, 1)    // 高光反射颜色
		_Gloss("Gloss", Range(8.0, 256)) = 20          // 高光区域大小
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
			// 定义实际可用的属性变量
			fixed4 _Diffuse;
			fixed4 _Specular;
			float _Gloss;

			struct a2v
			{
				float4 vertex : POSITION;   // 顶点局部坐标
				float3 normal : NORMAL;     // 顶点法向
			};

			struct v2f
			{
				float4 pos : SV_POSITION;   // 顶点裁剪坐标
				fixed3 color : COLOR;       // 在顶点着色器中的光照模型计算结果
			};

			v2f vert(a2v v)
			{
				v2f output;
				output.pos = UnityObjectToClipPos(v.vertex);       // 坐标MVP变换
				fixed3 ambient = UNITY_LIGHTMODEL_AMBIENT.xyz;      // 获取环境光

				// 获取并归一化法向、光源
				fixed3 worldNormal = normalize(mul(v.normal, (float3x3)unity_WorldToObject));
				fixed3 worldLight = normalize(_WorldSpaceLightPos0.xyz);

				// 计算漫反射项
				fixed3 diffuse = _LightColor0.rgb * _Diffuse.rgb * saturate(dot(worldNormal, worldLight));

				// 计算并归一化反射向量
				fixed3 reflectDir = normalize(reflect(-worldLight, worldNormal));
				// 视角向量 = 视点 - 着色点，记得转换到同一坐标空间乘起来才有用
				fixed3 viewDir = normalize(_WorldSpaceCameraPos.xyz - mul(unity_ObjectToWorld, v.vertex).xyz);

				fixed3 specular = _LightColor0.rgb * _Specular.rgb * pow(saturate(dot(reflectDir, viewDir)), _Gloss);

				output.color = ambient + diffuse + specular;

				return output;
			}

			fixed4 frag(v2f input) : SV_Target
			{
				return fixed4(input.color, 1.0);
			}

			ENDCG
		}
	}
	Fallback "Specular"
}