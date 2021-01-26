Shader "Unity Shaders Book/Chapter 8/AlphaBlendBothSided"
{
	Properties
	{
		_Color("Main Tint", Color) = (1,1,1,1)
		_MainTex("Main Tex", 2D) = "white" {}
		_AlphaScale("Alpha Scale", Range(0, 1)) = 1
	}
		SubShader
		{
			Tags
			{
				"Queue" = "Transparent"					// 指定渲染队列
				"IgnoreProjector" = "True"				// 不受 Projector 影响
				"RenderType" = "Transparent"			// 将当前 Shader 分类到使用透明混合的组 Transparent
			}

		Pass
		{
			Tags { "LightMode" = "ForwardBase" }

			Cull Front

			ZWrite Off								// 关闭深度写入
			Blend SrcAlpha OneMinusSrcAlpha			// 开启混合模式，并设源颜色（当前片元最终颜色）混合因子为 SrcAlpha，目标颜色（Color Buffer中颜色）混合因子为OneMinusSrcAlpha

			CGPROGRAM

			#pragma vertex vert
			#pragma fragment frag
			#include "Lighting.cginc"

			// 颜色四通道，纹理，纹理缩放，透明度
			fixed4 _Color;
			sampler2D _MainTex;
			float4 _MainTex_ST;
			fixed _AlphaScale;

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
				float2 uv : TEXCOORD2;
			};

			// 求法线/顶点位置的世界空间坐标，纹理坐标做缩放平移后传给片段着色器
			v2f vert(a2v v)
			{
				v2f o;
				o.pos = UnityObjectToClipPos(v.vertex);

				o.worldNormal = UnityObjectToWorldNormal(v.normal);

				o.worldPos = mul(unity_ObjectToWorld, v.vertex).xyz;

				o.uv = TRANSFORM_TEX(v.texcoord, _MainTex);

				return o;
			}


			fixed4 frag(v2f i) : SV_Target
			{
				// 归一化法线和光源（世界空间）
				fixed3 worldNormal = normalize(i.worldNormal);
				fixed3 worldLightDir = normalize(UnityWorldSpaceLightDir(i.worldPos));

				// 纹理采样
				fixed4 texColor = tex2D(_MainTex, i.uv);

				fixed3 albedo = texColor.rgb * _Color.rgb;

				fixed3 ambient = UNITY_LIGHTMODEL_AMBIENT.xyz * albedo;

				fixed3 diffuse = _LightColor0.rgb * albedo * max(0, dot(worldNormal, worldLightDir));

				// 设置片元着色器返回值中的透明通道为纹素透明通道和材质参数 _AlphaScale 乘积
				return fixed4(ambient + diffuse, texColor.a * _AlphaScale);
			}

			ENDCG
		}

		Pass
		{
			Tags { "LightMode" = "ForwardBase" }

			Cull Back
			ZWrite Off								// 关闭深度写入
			Blend SrcAlpha OneMinusSrcAlpha			// 开启混合模式，并设源颜色（当前片元最终颜色）混合因子为 SrcAlpha，目标颜色（Color Buffer中颜色）混合因子为OneMinusSrcAlpha

			CGPROGRAM

			#pragma vertex vert
			#pragma fragment frag
			#include "Lighting.cginc"

			// 颜色四通道，纹理，纹理缩放，透明度
			fixed4 _Color;
			sampler2D _MainTex;
			float4 _MainTex_ST;
			fixed _AlphaScale;

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
				float2 uv : TEXCOORD2;
			};

			// 求法线/顶点位置的世界空间坐标，纹理坐标做缩放平移后传给片段着色器
			v2f vert(a2v v)
			{
				v2f o;
				o.pos = UnityObjectToClipPos(v.vertex);

				o.worldNormal = UnityObjectToWorldNormal(v.normal);

				o.worldPos = mul(unity_ObjectToWorld, v.vertex).xyz;

				o.uv = TRANSFORM_TEX(v.texcoord, _MainTex);

				return o;
			}


			fixed4 frag(v2f i) : SV_Target
			{
				// 归一化法线和光源（世界空间）
				fixed3 worldNormal = normalize(i.worldNormal);
				fixed3 worldLightDir = normalize(UnityWorldSpaceLightDir(i.worldPos));

				// 纹理采样
				fixed4 texColor = tex2D(_MainTex, i.uv);

				fixed3 albedo = texColor.rgb * _Color.rgb;

				fixed3 ambient = UNITY_LIGHTMODEL_AMBIENT.xyz * albedo;

				fixed3 diffuse = _LightColor0.rgb * albedo * max(0, dot(worldNormal, worldLightDir));

				// 设置片元着色器返回值中的透明通道为纹素透明通道和材质参数 _AlphaScale 乘积
				return fixed4(ambient + diffuse, texColor.a * _AlphaScale);
			}
			ENDCG
		}
	}
	Fallback "Transparent/VertexLit"	// Fallback 也与透明测试不同
}
