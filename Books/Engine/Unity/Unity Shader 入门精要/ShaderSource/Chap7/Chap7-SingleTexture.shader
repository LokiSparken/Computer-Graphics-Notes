Shader "Unity Shaders Book/Chapter 7/SingleTexture"
{
	Properties
	{
		// 在材质面板中添加属性控制项
		_Color("Color Tint", Color) = (1,1,1,1)
		_MainTex("Main Tex", 2D) = "white" {}
		_Specular("Specular", Color) = (1, 1, 1, 1)
		_Gloss("Gloss", Range(8.0, 256)) = 20
	}
	SubShader
	{
		Pass
		{
			Tags { "LightMode" = "ForwardBase" }

			CGPROGRAM

			#pragma vertex vert
			#pragma fragment frag
			#include "Lighting.cginc"
			// 对应材质面板中声明的属性定义变量
			fixed4 _Color;          // 控制整体色调
			sampler2D _MainTex;
			/* _<TextureName>_ST声明纹理属性
			 * ST = 缩放Scale & 平移Translation
			 * _<TextureName>_ST.xy存缩放值（Tiling），.zw存偏移值（Offset）
			 */
			float4 _MainTex_ST;
			fixed4 _Specular;
			float _Gloss;

			struct a2v
			{
				float4 vertex : POSITION;
				float3 normal : NORMAL;
				float4 texcoord : TEXCOORD0;
			};

			struct v2f
			{
				float4 pos : SV_POSITION;
				float3 worldNormal : TEXCOORD0;
				float3 worldPos : TEXCOORD1;
				float2 uv : TEXCOORD2;              // 传UV坐标给Fragment Shader做纹理采样
			};

			v2f vert(a2v v)
			{
				v2f output;
				output.pos = mul(UNITY_MATRIX_MVP, v.vertex);
				output.worldNormal = UnityObjectToWorldNormal(v.normal);
				output.worldPos = mul(_Object2World, v.vertex).xyz;

				// 对顶点纹理坐标做缩放和平移
				output.uv = v.texcoord.xy * _MainTex_ST.xy + _MainTex_ST.zw;
				// output.uv = TRANSFORM_TEX(v.texcoord, _MainTex);

				return output;
			}

			fixed4 frag(v2f i) : SV_Target
			{
				// 法向、光源
				fixed3 worldNormal = normalize(i.worldNormal);
				fixed3 worldLight = normalize(UnityWorldSpaceLightDir(i.worldPos));

				// tex2D(纹理, UV坐标) 做采样，返回纹素值，与整体色调做混合
				fixed3 albedo = tex2D(_MainTex, i.uv).rgb * _Color.rgb;

				// 环境光、漫反射、高光反射
				fixed3 ambient = UNITY_LIGHTMODEL_AMBIENT.xyz * albedo;
				fixed3 diffuse = _LightColor0.rgb * albedo * max(0, dot(worldNormal, worldLight));
				fixed3 viewDir = normalize(UnityWorldSpaceViewDir(i.worldPos));
				fixed3 halfDir = normalize(worldLight + viewDir);
				fixed3 specular = _LightColor0.rgb * _Specular.rgb * pow(max(0, dot(worldNormal, halfDir)), _Gloss);

				return fixed4(ambient + diffuse + specular, 1.0);
			}

			ENDCG
		}
	}
	Fallback "Specular"
}