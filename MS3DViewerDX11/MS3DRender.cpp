#include "stdafx.h"
#include "MS3DRender.h"

#include "Util/FileName.h"

#include "DX11/DX11Win32Renderer.h"
#include "DX11/Texture/DX11Texture.h"

namespace BWSG
{
#define	Q_PI	3.14159265358979323846
#define DotProduct(x,y) ((x)[0]*(y)[0]+(x)[1]*(y)[1]+(x)[2]*(y)[2])


	void FillJointIndicesAndWeights(const MS3DVertex *vertex, int jointIndices[4], int jointWeights[4]) 
	{
		jointIndices[0] = vertex->boneId;
		jointIndices[1] = vertex->boneIds[0];
		jointIndices[2] = vertex->boneIds[1];
		jointIndices[3] = vertex->boneIds[2];
		jointWeights[0] = 100;
		jointWeights[1] = 0;
		jointWeights[2] = 0;
		jointWeights[3] = 0;
		if (vertex->weights[0] != 0 || vertex->weights[1] != 0 || vertex->weights[2] != 0)
		{
			jointWeights[0] = vertex->weights[0];
			jointWeights[1] = vertex->weights[1];
			jointWeights[2] = vertex->weights[2];
			jointWeights[3] = 100 - (vertex->weights[0] + vertex->weights[1] + vertex->weights[2]);
		}
	}


	void VectorRotate (const vec3_t in1, const float in2[3][4], vec3_t out)
	{
		out[0] = DotProduct(in1, in2[0]);
		out[1] = DotProduct(in1, in2[1]);
		out[2] = DotProduct(in1, in2[2]);
	}

	void VectorIRotate (const vec3_t in1, const float in2[3][4], vec3_t out)
	{
		out[0] = in1[0]*in2[0][0] + in1[1]*in2[1][0] + in1[2]*in2[2][0];
		out[1] = in1[0]*in2[0][1] + in1[1]*in2[1][1] + in1[2]*in2[2][1];
		out[2] = in1[0]*in2[0][2] + in1[1]*in2[1][2] + in1[2]*in2[2][2];
	}

	void VectorTransform (const vec3_t in1, const float in2[3][4], vec3_t out)
	{
		out[0] = DotProduct(in1, in2[0]) + in2[0][3];
		out[1] = DotProduct(in1, in2[1]) +	in2[1][3];
		out[2] = DotProduct(in1, in2[2]) +	in2[2][3];
	}

	void VectorITransform (const vec3_t in1, const float in2[3][4], vec3_t out)
	{
		vec3_t tmp;
		tmp[0] = in1[0] - in2[0][3];
		tmp[1] = in1[1] - in2[1][3];
		tmp[2] = in1[2] - in2[2][3];
		VectorIRotate(tmp, in2, out);
	}

	void AngleMatrix (const vec3_t  angles, float (*matrix)[4] )
	{
		float		angle;
		float		sr, sp, sy, cr, cp, cy;

		angle = angles[2];
		sy = sin(angle);
		cy = cos(angle);
		angle = angles[1];
		sp = sin(angle);
		cp = cos(angle);
		angle = angles[0];
		sr = sin(angle);
		cr = cos(angle);

		matrix[0][0] = cp*cy;
		matrix[1][0] = cp*sy;
		matrix[2][0] = -sp;
		matrix[0][1] = sr*sp*cy+cr*-sy;
		matrix[1][1] = sr*sp*sy+cr*cy;
		matrix[2][1] = sr*cp;
		matrix[0][2] = (cr*sp*cy+-sr*-sy);
		matrix[1][2] = (cr*sp*sy+-sr*cy);
		matrix[2][2] = cr*cp;
		matrix[0][3] = 0.0;
		matrix[1][3] = 0.0;
		matrix[2][3] = 0.0;
	}

	void R_ConcatTransforms (const float in1[3][4], const float in2[3][4], float out[3][4])
	{
		out[0][0] = in1[0][0] * in2[0][0] + in1[0][1] * in2[1][0] +
			in1[0][2] * in2[2][0];
		out[0][1] = in1[0][0] * in2[0][1] + in1[0][1] * in2[1][1] +
			in1[0][2] * in2[2][1];
		out[0][2] = in1[0][0] * in2[0][2] + in1[0][1] * in2[1][2] +
			in1[0][2] * in2[2][2];
		out[0][3] = in1[0][0] * in2[0][3] + in1[0][1] * in2[1][3] +
			in1[0][2] * in2[2][3] + in1[0][3];
		out[1][0] = in1[1][0] * in2[0][0] + in1[1][1] * in2[1][0] +
			in1[1][2] * in2[2][0];
		out[1][1] = in1[1][0] * in2[0][1] + in1[1][1] * in2[1][1] +
			in1[1][2] * in2[2][1];
		out[1][2] = in1[1][0] * in2[0][2] + in1[1][1] * in2[1][2] +
			in1[1][2] * in2[2][2];
		out[1][3] = in1[1][0] * in2[0][3] + in1[1][1] * in2[1][3] +
			in1[1][2] * in2[2][3] + in1[1][3];
		out[2][0] = in1[2][0] * in2[0][0] + in1[2][1] * in2[1][0] +
			in1[2][2] * in2[2][0];
		out[2][1] = in1[2][0] * in2[0][1] + in1[2][1] * in2[1][1] +
			in1[2][2] * in2[2][1];
		out[2][2] = in1[2][0] * in2[0][2] + in1[2][1] * in2[1][2] +
			in1[2][2] * in2[2][2];
		out[2][3] = in1[2][0] * in2[0][3] + in1[2][1] * in2[1][3] +
			in1[2][2] * in2[2][3] + in1[2][3];
	}


	void AngleQuaternion( const vec3_t angles, float quaternion[4] )
	{
		float		angle;
		float		sr, sp, sy, cr, cp, cy;

		angle = angles[2] * 0.5;
		sy = sin(angle);
		cy = cos(angle);
		angle = angles[1] * 0.5;
		sp = sin(angle);
		cp = cos(angle);
		angle = angles[0] * 0.5;
		sr = sin(angle);
		cr = cos(angle);

		quaternion[0] = sr*cp*cy-cr*sp*sy; // X
		quaternion[1] = cr*sp*cy+sr*cp*sy; // Y
		quaternion[2] = cr*cp*sy-sr*sp*cy; // Z
		quaternion[3] = cr*cp*cy+sr*sp*sy; // W
	}

	void QuaternionMatrix( const float  quaternion[4] , float (*matrix)[4] )
	{
		matrix[0][0] = 1.0 - 2.0 * quaternion[1] * quaternion[1] - 2.0 * quaternion[2] * quaternion[2];
		matrix[1][0] = 2.0 * quaternion[0] * quaternion[1] + 2.0 * quaternion[3] * quaternion[2];
		matrix[2][0] = 2.0 * quaternion[0] * quaternion[2] - 2.0 * quaternion[3] * quaternion[1];

		matrix[0][1] = 2.0 * quaternion[0] * quaternion[1] - 2.0 * quaternion[3] * quaternion[2];
		matrix[1][1] = 1.0 - 2.0 * quaternion[0] * quaternion[0] - 2.0 * quaternion[2] * quaternion[2];
		matrix[2][1] = 2.0 * quaternion[1] * quaternion[2] + 2.0 * quaternion[3] * quaternion[0];

		matrix[0][2] = 2.0 * quaternion[0] * quaternion[2] + 2.0 * quaternion[3] * quaternion[1];
		matrix[1][2] = 2.0 * quaternion[1] * quaternion[2] - 2.0 * quaternion[3] * quaternion[0];
		matrix[2][2] = 1.0 - 2.0 * quaternion[0] * quaternion[0] - 2.0 * quaternion[1] * quaternion[1];
	}

	void QuaternionSlerp( const float p[4], float q[4], float t, float qt[4] )
	{
		int i;
		float omega, cosom, sinom, sclp, sclq;

		float a = 0;
		float b = 0;
		for (i = 0; i < 4; i++) {
			a += (p[i]-q[i])*(p[i]-q[i]);
			b += (p[i]+q[i])*(p[i]+q[i]);
		}
		if (a > b) {
			for (i = 0; i < 4; i++) {
				q[i] = -q[i];
			}
		}

		cosom = p[0]*q[0] + p[1]*q[1] + p[2]*q[2] + p[3]*q[3];

		if ((1.0 + cosom) > 0.00000001) {
			if ((1.0 - cosom) > 0.00000001) {
				omega = acos( cosom );
				sinom = sin( omega );
				sclp = sin( (1.0 - t)*omega) / sinom;
				sclq = sin( t*omega ) / sinom;
			}
			else {
				sclp = 1.0 - t;
				sclq = t;
			}
			for (i = 0; i < 4; i++) {
				qt[i] = sclp * p[i] + sclq * q[i];
			}
		}
		else {
			qt[0] = -p[1];
			qt[1] = p[0];
			qt[2] = -p[3];
			qt[3] = p[2];
			sclp = sin( (1.0 - t) * 0.5 * Q_PI);
			sclq = sin( t * 0.5 * Q_PI);
			for (i = 0; i < 3; i++) {
				qt[i] = sclp * p[i] + sclq * qt[i];
			}
		}
	}



	CMS3DRender::CMS3DRender(void)
		: m_pEffect ( nullptr )
		, m_pTech ( nullptr )
		, m_pInputLayout ( nullptr )
		, timer(-1.0f)
		, playani(false)

	{
	}


	CMS3DRender::~CMS3DRender(void)
	{
;
		Destroy();

	}

	void CMS3DRender::Destroy()
	{
		RELEASECOM( m_pInputLayout );
		RELEASECOM( m_pEffect );
		SAFE_DELETE( m_pMS3DVertices );
		SAFE_DELETE( m_pMS3DTriangles );
		SAFE_DELETE_ARRAY( m_pMS3DGroups );
		SAFE_DELETE_ARRAY( m_pMS3DMaterials );
		SAFE_DELETE( m_pMS3DJoint );

	}

	bool	CMS3DRender::CreateShaderFX		( ID3D11Device* pDevice, cchar_t * szFileName , cchar_t * szTechName , cchar_t * szVersion , ShaderMacro * pMacro)
	{
		if ( m_pEffect != nullptr )
			return false;

		HRESULT hr;

		ID3DBlob* pFXBlob = nullptr;
		ID3DBlob *blob = nullptr;

		hr = D3DCompileFromFile( szFileName, nullptr, nullptr, "", "fx_5_0", 0, 0, &pFXBlob, &blob );
		if ( FAILED(hr) )
		{
			if( blob != NULL )
				OutputDebugStringA( (char*)blob->GetBufferPointer() );
			if( blob ) 
				blob->Release();
		}

		hr = D3DX11CreateEffectFromMemory( pFXBlob->GetBufferPointer() , pFXBlob->GetBufferSize() , NULL , pDevice , &m_pEffect  );

		if ( m_pEffect == nullptr )
			return false; 
		m_pTech = m_pEffect->GetTechniqueByName(toMultiByte(szTechName));



		// 인풋 레이아웃 생성 
		{


			D3D11_INPUT_ELEMENT_DESC layoutDesc[] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD", 1, DXGI_FORMAT_R32G32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "BLENDINDICES", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "BLENDWEIGHT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 56, D3D11_INPUT_PER_VERTEX_DATA, 0 }
			};

			D3DX11_PASS_SHADER_DESC VsPassDesc;
			D3DX11_EFFECT_SHADER_DESC VsDesc;

			m_pTech->GetPassByIndex(0)->GetVertexShaderDesc(&VsPassDesc);
			VsPassDesc.pShaderVariable->GetShaderDesc(VsPassDesc.ShaderIndex, &VsDesc);

			pDevice->CreateInputLayout( layoutDesc, 6,
				VsDesc.pBytecode,
				VsDesc.BytecodeLength,
				&m_pInputLayout);

		}
		pFXBlob->Release();

		return true;
	}


	void CMS3DRender::InitShader( ID3D11Device* pDevice )
	{
		CreateShaderFX(pDevice , L"VertexShader.fx" , L"MS3DShader",L"fx_5_0",nullptr);
	}
	void CMS3DRender::LoadMS3D( ID3D11Device* pDevice, ID3D11DeviceContext* pContext, const char * szName )
	{
		strcpy( szFileName, szName);
		InitShader(pDevice);
		unsigned short usVertexCount = 0;
		unsigned short usTriangleCount = 0;
		unsigned short usGroupCount = 0;
		unsigned short usMaterialCount = 0;
		unsigned short usJointCount = 0;

		FILE *fp = fopen(szName, "rb");

		fseek(fp, 0, SEEK_END);
		long fileSize = ftell(fp);
		fseek(fp, 0, SEEK_SET); 


		
		//std::ifstream fin;
		MS3DHeader header;
		(void)fread(header.id, sizeof(char), 10, fp);
		if (strncmp(header.id, "MS3D000000", 10) != 0)
		{
			fclose(fp);
			// "This is not a valid MS3D file format!"
			return ;
		} 
		

		(void)fread(&header.version, sizeof(int), 1, fp);
		if (header.version != 4)
		{
			fclose(fp);
			// "This is not a valid MS3D file version!"
			return ;

		}
#pragma region 버텍스
		
		(void)fread(&usVertexCount, sizeof(unsigned short), 1, fp);
		m_pMS3DVertices = new MS3DVertex[usVertexCount];
		m_NumOfVertices = usVertexCount;
		for (int i = 0; i < usVertexCount; i++)
		{
			(void)fread(&m_pMS3DVertices[i].flags, sizeof(unsigned char), 1, fp);
			(void)fread(&m_pMS3DVertices[i].vertex, sizeof(float), 3, fp);
			(void)fread(&m_pMS3DVertices[i].boneId, sizeof(char), 1, fp);
			(void)fread(&m_pMS3DVertices[i].referenceCount, sizeof(unsigned char), 1, fp); 
		}
#pragma endregion
#pragma region 인덱스
		(void)fread(&usTriangleCount, sizeof(unsigned short), 1, fp);
		if (usTriangleCount >0)
		{
			m_pMS3DTriangles = new MS3DTriangle[usTriangleCount];
			if (m_pMS3DTriangles != nullptr)
			{
				m_NumOfTriangles = usTriangleCount;
				for (int i = 0; i < usTriangleCount; i++)
				{

					(void)fread(&m_pMS3DTriangles[i].flags, sizeof(unsigned short), 1, fp);
					(void)fread(m_pMS3DTriangles[i].vertexIndices, sizeof(unsigned short), 3, fp);
					(void)fread(m_pMS3DTriangles[i].vertexNormals, sizeof(float), 3 * 3, fp);
					(void)fread(m_pMS3DTriangles[i].s, sizeof(float), 3, fp);
					(void)fread(m_pMS3DTriangles[i].t, sizeof(float), 3, fp);
					(void)fread(&m_pMS3DTriangles[i].smoothingGroup, sizeof(unsigned char), 1, fp);
					(void)fread(&m_pMS3DTriangles[i].groupIndex, sizeof(unsigned char), 1, fp); 
				}
			}		
		}	
#pragma endregion
#pragma region 그룹
		(void)fread(&usGroupCount, sizeof(unsigned short), 1, fp);
		if (usGroupCount > 0)  
		{
			m_pMS3DGroups = new MS3DGroup[usGroupCount];
			if (m_pMS3DGroups != NULL)
			{
				m_NumOfGroups = usGroupCount;
				for (int i = 0; i < usGroupCount; i++)
				{
					(void)fread(&m_pMS3DGroups[i].flags, sizeof(unsigned char), 1, fp);
					(void)fread(m_pMS3DGroups[i].name, sizeof(char), 32, fp);
					(void)fread(&m_pMS3DGroups[i].numtriangles, sizeof(unsigned short), 1, fp);
					m_pMS3DGroups[i].triangleIndices= new unsigned short[ m_pMS3DGroups[i].numtriangles];
					if (m_pMS3DGroups[i].numtriangles > 0)
						(void)fread(&m_pMS3DGroups[i].triangleIndices[0], sizeof(unsigned short), m_pMS3DGroups[i].numtriangles, fp);
					(void)fread(&m_pMS3DGroups[i].materialIndex, sizeof(char), 1, fp); 

				}
			}		
		}	
#pragma endregion
#pragma region material information
		(void)fread(&usMaterialCount, sizeof(unsigned short), 1, fp);

		if (usMaterialCount > 0) 
		{
			m_pMS3DMaterials = new MS3DMaterial[usMaterialCount];
			m_NumOfMaterials = usMaterialCount;

			if (m_pMS3DMaterials != nullptr)
			{			
				for (unsigned int i = 0; i < m_NumOfMaterials; i++)
				{



					(void)fread(m_pMS3DMaterials[i].name, sizeof(char), 32, fp);
					(void)fread(&m_pMS3DMaterials[i].ambient, sizeof(float), 4, fp);
					(void)fread(&m_pMS3DMaterials[i].diffuse, sizeof(float), 4, fp);
					(void)fread(&m_pMS3DMaterials[i].specular, sizeof(float), 4, fp);
					(void)fread(&m_pMS3DMaterials[i].emissive, sizeof(float), 4, fp);
					(void)fread(&m_pMS3DMaterials[i].shininess, sizeof(float), 1, fp);
					(void)fread(&m_pMS3DMaterials[i].transparency, sizeof(float), 1, fp);
					(void)fread(&m_pMS3DMaterials[i].mode, sizeof(unsigned char), 1, fp);
					(void)fread(m_pMS3DMaterials[i].texture, sizeof(char), 128, fp);
					(void)fread(m_pMS3DMaterials[i].alphamap, sizeof(char), 128, fp); 



					CFileName name(m_pMS3DMaterials[i].texture);
					CFileName name2(m_pMS3DMaterials[i].alphamap);
					name.ChangeExt("dds");
					strcpy(m_pMS3DMaterials[i].texture, name.GetNameExt());
					strcpy(m_pMS3DMaterials[i].alphamap, name2.GetNameExt());
					
					m_pMS3DMaterials[i].pTexture = _RENDERER_DEF.GetTextureManager()->CreateTextureFromFile(toWideChar(m_pMS3DMaterials[i].texture),0);
					
					/*memcpy(m_pMaterials[i].m_ambient, pMS3DMaterials[i].ambient, sizeof(float)*4);
					memcpy(m_pMaterials[i].m_diffuse, pMS3DMaterials[i].diffuse, sizeof(float)*4);
					memcpy(m_pMaterials[i].m_emissive, pMS3DMaterials[i].emissive, sizeof(float)*4);				
					memcpy(m_pMaterials[i].m_specular, pMS3DMaterials[i].specular, sizeof(float)*4);
					m_pMaterials[i].m_shininess = pMS3DMaterials[i].shininess;

					m_pMaterials[i].m_filename_length = strlen(pMS3DMaterials[i].texture) + 1;
					strcpy(m_pMaterials[i].m_pTextureFilename, pMS3DMaterials[i].texture);*/
				}
			}
		}
#pragma endregion
#pragma region Animation
		// animation

		(void)fread(&m_AnimationFps, sizeof(float), 1, fp);
		if (m_AnimationFps < 1.0f)
			m_AnimationFps = 1.0f;

		(void)fread(&m_CurrentTime, sizeof(float), 1, fp);
		(void)fread(&m_TotalFrames, sizeof(int), 1, fp);



		// joints

		(void)fread(&m_NumOfJoint, sizeof(unsigned short), 1, fp);
		m_pMS3DJoint = new MS3DKeyframeJoint[m_NumOfJoint];
		for (int i = 0; i < m_NumOfJoint; i++)
		{
			(void)fread(&m_pMS3DJoint[i].flags, sizeof(unsigned char), 1, fp);
			(void)(void)fread(m_pMS3DJoint[i].name, sizeof(char), 32, fp);
			(void)fread(m_pMS3DJoint[i].parentName, sizeof(char), 32, fp);
			(void)fread(m_pMS3DJoint[i].rot, sizeof(float), 3, fp);
			(void)fread(m_pMS3DJoint[i].pos, sizeof(float), 3, fp);


			(void)fread(&m_pMS3DJoint[i].numKeyFramesRot, sizeof(unsigned short), 1, fp);
			m_pMS3DJoint[i].keyFramesRot = new MS3DKeyframeRotation[m_pMS3DJoint[i].numKeyFramesRot];

			(void)fread(&m_pMS3DJoint[i].numKeyFramesTrans, sizeof(unsigned short), 1, fp);
			m_pMS3DJoint[i].keyFramesTrans= new MS3DKeyframePosition[m_pMS3DJoint[i].numKeyFramesTrans];



			// the frame time is in seconds, so multiply it by the animation fps, to get the frames
			// rotation channel
			for (int j = 0; j < m_pMS3DJoint[i].numKeyFramesRot; j++)
			{
				(void)fread(&m_pMS3DJoint[i].keyFramesRot[j].time, sizeof(float), 1, fp);
				(void)fread(&m_pMS3DJoint[i].keyFramesRot[j].rotation, sizeof(float), 3, fp);
				m_pMS3DJoint[i].keyFramesRot[j].time *= m_AnimationFps;
			}

			// translation channel
			for (int j = 0; j < m_pMS3DJoint[i].numKeyFramesTrans; j++)
			{
				(void)fread(&m_pMS3DJoint[i].keyFramesTrans[j].time, sizeof(float), 1, fp);
				(void)fread(&m_pMS3DJoint[i].keyFramesTrans[j].position, sizeof(float), 3, fp);
				m_pMS3DJoint[i].keyFramesTrans[j].time *= m_AnimationFps;
			}
		} 


#pragma endregion
#pragma region Comment
		long filePos = ftell(fp);

		if (filePos < fileSize)

		{

			int subVersion = 0;

			(void)fread(&subVersion, sizeof(int), 1, fp);

			if (subVersion == 1)

			{

				int numComments = 0;

				size_t commentSize = 0;



				// group comments

				(void)fread(&numComments, sizeof(int), 1, fp);

				for (int i = 0; i < numComments; i++)

				{

					int index;

					(void)fread(&index, sizeof(int), 1, fp);

					std::vector<char> comment;

					(void)fread(&commentSize, sizeof(size_t), 1, fp);

					comment.resize(commentSize);

					if (commentSize > 0)

						(void)fread(&comment[0], sizeof(char), commentSize, fp);

					/*if (index >= 0 && index < (int) m_groups.size())
						m_groups[index].comment = comment;*/

				}



				// material comments

				(void)fread(&numComments, sizeof(int), 1, fp);

				for (int i = 0; i < numComments; i++)

				{

					int index;

					(void)fread(&index, sizeof(int), 1, fp);

					std::vector<char> comment;

					(void)fread(&commentSize, sizeof(size_t), 1, fp);

					comment.resize(commentSize);

					if (commentSize > 0)

						(void)fread(&comment[0], sizeof(char), commentSize, fp);

					/*if (index >= 0 && index < (int) m_materials.size())
					m_materials[index].comment = comment;*/

				}



				// joint comments

				(void)fread(&numComments, sizeof(int), 1, fp);

				for (int i = 0; i < numComments; i++)

				{

					int index;

					(void)fread(&index, sizeof(int), 1, fp);

					std::vector<char> comment;

					(void)fread(&commentSize, sizeof(size_t), 1, fp);

					comment.resize(commentSize);

					if (commentSize > 0)

						(void)fread(&comment[0], sizeof(char), commentSize, fp);

					//if (index >= 0 && index < (int) m_joints.size())
					//	m_joints[index].comment = comment;

				}



				// model comments

				(void)fread(&numComments, sizeof(int), 1, fp);

				if (numComments == 1)

				{

					std::vector<char> comment;

					(void)fread(&commentSize, sizeof(size_t), 1, fp);

					comment.resize(commentSize);

					if (commentSize > 0)

					(void)fread(&comment[0], sizeof(char), commentSize, fp);
					//m_comment = comment;

				}
			}

			else
			{
				// "Unknown subversion for comments %d\n", subVersion);

			}

		} 



#pragma endregion

#pragma region Extra

		// vertex extra
		filePos = ftell(fp);
		if (filePos < fileSize)
		{
			int subVersion = 0;
			(void)fread(&subVersion, sizeof(int), 1, fp);
			if (subVersion == 2)
			{
				for (int i = 0; i < m_NumOfVertices; i++)
				{
					(void)fread(&m_pMS3DVertices[i].boneIds[0], sizeof(char), 3, fp);
					(void)fread(&m_pMS3DVertices[i].weights[0], sizeof(unsigned char), 3, fp);
					(void)fread(&m_pMS3DVertices[i].extra, sizeof(unsigned int), 1, fp);
				}
			}
			else if (subVersion == 1)
			{
				for (int i = 0; i < m_NumOfVertices; i++)
				{
					(void)fread(&m_pMS3DVertices[i].boneIds[0], sizeof(char), 3, fp);
					(void)fread(&m_pMS3DVertices[i].weights[0], sizeof(unsigned char), 3, fp);
				}
			}
			else
			{
				// "Unknown subversion for vertex extra %d\n", subVersion);
			}

		} 

		// joint extra
		filePos = ftell(fp);
		if (filePos < fileSize)
		{
			int subVersion = 0;
			(void)fread(&subVersion, sizeof(int), 1, fp);
			if (subVersion == 1)
			{
				for (int i = 0; i < m_NumOfJoint; i++)
				{
					(void)fread(&m_pMS3DJoint[i].color, sizeof(float), 3, fp);
				}
			}
			else
			{
				// "Unknown subversion for joint extra %d\n", subVersion);
			}
		} 


		// model extra

		filePos = ftell(fp);

		if (filePos < fileSize)
		{
			int subVersion = 0;
			(void)fread(&subVersion, sizeof(int), 1, fp);
			if (subVersion == 1)
			{
				//(void)fread(&m_jointSize, sizeof(float), 1, fp);
				//(void)fread(&m_transparencyMode, sizeof(int), 1, fp);
				//(void)fread(&m_alphaRef, sizeof(float), 1, fp);
			}

			else

			{

				//"Unknown subversion for model extra %d\n", subVersion);

			}

		} 

#pragma endregion

		RebulidVertex(pDevice , pContext);
		SetupJoints();

		// 필요없으니 파일 닫음. 
		fclose(fp);

	}

	void CMS3DRender::RebulidVertex(ID3D11Device* pDevice, ID3D11DeviceContext* pContext )
	{
		 int cnt = 0;
		 for (unsigned int i = 0; i < m_NumOfGroups; i++)
		 {
			  m_pMS3DGroups[i].numVertices = m_pMS3DGroups[i].numtriangles * 3;
			  m_pMS3DGroups[i].vertices = new BWSG::euVertexPNTTIW[m_pMS3DGroups[i].numVertices];
			  m_pMS3DGroups[i].OriginalVertices = new BWSG::euVertexPNTTIW[m_pMS3DGroups[i].numVertices];

			  for (int k = 0; k < m_pMS3DGroups[i].numtriangles; k++)
			  {
				  m_pMS3DGroups[i].vertices[k * 3 + 0].pos.x = m_pMS3DVertices[m_pMS3DTriangles[m_pMS3DGroups[i].triangleIndices[k]].vertexIndices[0]].vertex[0];
				  m_pMS3DGroups[i].vertices[k * 3 + 0].pos.y = m_pMS3DVertices[m_pMS3DTriangles[m_pMS3DGroups[i].triangleIndices[k]].vertexIndices[0]].vertex[1];
				  m_pMS3DGroups[i].vertices[k * 3 + 0].pos.z = m_pMS3DVertices[m_pMS3DTriangles[m_pMS3DGroups[i].triangleIndices[k]].vertexIndices[0]].vertex[2];
				  m_pMS3DGroups[i].vertices[k * 3 + 0].normal.x = m_pMS3DTriangles[m_pMS3DGroups[i].triangleIndices[k]].vertexNormals[0][0];
				  m_pMS3DGroups[i].vertices[k * 3 + 0].normal.y = m_pMS3DTriangles[m_pMS3DGroups[i].triangleIndices[k]].vertexNormals[0][1];
				  m_pMS3DGroups[i].vertices[k * 3 + 0].normal.z = m_pMS3DTriangles[m_pMS3DGroups[i].triangleIndices[k]].vertexNormals[0][2];
				  m_pMS3DGroups[i].vertices[k * 3 + 0].uv1.x = m_pMS3DTriangles[m_pMS3DGroups[i].triangleIndices[k]].s[0];
				  m_pMS3DGroups[i].vertices[k * 3 + 0].uv1.y = m_pMS3DTriangles[m_pMS3DGroups[i].triangleIndices[k]].t[0];
				  m_pMS3DGroups[i].vertices[k * 3 + 0].boneIndex.x = m_pMS3DVertices[m_pMS3DTriangles[m_pMS3DGroups[i].triangleIndices[k]].vertexIndices[0]].boneId;
				  m_pMS3DGroups[i].vertices[k * 3 + 0].boneIndex.y = 0;
				  m_pMS3DGroups[i].vertices[k * 3 + 0].boneIndex.z = 0;
				  m_pMS3DGroups[i].vertices[k * 3 + 0].boneIndex.w = 0;
				  m_pMS3DGroups[i].vertices[k * 3 + 0].boneweight.x = 1;
				  m_pMS3DGroups[i].vertices[k * 3 + 0].boneweight.y = 0;
				  m_pMS3DGroups[i].vertices[k * 3 + 0].boneweight.z = 0;
				  m_pMS3DGroups[i].vertices[k * 3 + 0].boneweight.w = 0;

				  m_pMS3DGroups[i].vertices[k * 3 + 1].pos.x = m_pMS3DVertices[m_pMS3DTriangles[m_pMS3DGroups[i].triangleIndices[k]].vertexIndices[1]].vertex[0];
				  m_pMS3DGroups[i].vertices[k * 3 + 1].pos.y = m_pMS3DVertices[m_pMS3DTriangles[m_pMS3DGroups[i].triangleIndices[k]].vertexIndices[1]].vertex[1];
				  m_pMS3DGroups[i].vertices[k * 3 + 1].pos.z = m_pMS3DVertices[m_pMS3DTriangles[m_pMS3DGroups[i].triangleIndices[k]].vertexIndices[1]].vertex[2];
				  m_pMS3DGroups[i].vertices[k * 3 + 1].normal.x = m_pMS3DTriangles[m_pMS3DGroups[i].triangleIndices[k]].vertexNormals[1][0];
				  m_pMS3DGroups[i].vertices[k * 3 + 1].normal.y = m_pMS3DTriangles[m_pMS3DGroups[i].triangleIndices[k]].vertexNormals[1][1];
				  m_pMS3DGroups[i].vertices[k * 3 + 1].normal.z = m_pMS3DTriangles[m_pMS3DGroups[i].triangleIndices[k]].vertexNormals[1][2];
				  m_pMS3DGroups[i].vertices[k * 3 + 1].uv1.x = m_pMS3DTriangles[m_pMS3DGroups[i].triangleIndices[k]].s[1];
				  m_pMS3DGroups[i].vertices[k * 3 + 1].uv1.y = m_pMS3DTriangles[m_pMS3DGroups[i].triangleIndices[k]].t[1];
				  m_pMS3DGroups[i].vertices[k * 3 + 1].boneIndex.x = m_pMS3DVertices[m_pMS3DTriangles[m_pMS3DGroups[i].triangleIndices[k]].vertexIndices[0]].boneId;
				  m_pMS3DGroups[i].vertices[k * 3 + 1].boneIndex.x = m_pMS3DVertices[m_pMS3DTriangles[m_pMS3DGroups[i].triangleIndices[k]].vertexIndices[1]].boneId;
				  m_pMS3DGroups[i].vertices[k * 3 + 1].boneIndex.y = 0;
				  m_pMS3DGroups[i].vertices[k * 3 + 1].boneIndex.z = 0;
				  m_pMS3DGroups[i].vertices[k * 3 + 1].boneIndex.w = 0;
				  m_pMS3DGroups[i].vertices[k * 3 + 1].boneweight.x = 1;
				  m_pMS3DGroups[i].vertices[k * 3 + 1].boneweight.y = 0;
				  m_pMS3DGroups[i].vertices[k * 3 + 1].boneweight.z = 0;
				  m_pMS3DGroups[i].vertices[k * 3 + 1].boneweight.w = 0;

				  m_pMS3DGroups[i].vertices[k * 3 + 2].pos.x = m_pMS3DVertices[m_pMS3DTriangles[m_pMS3DGroups[i].triangleIndices[k]].vertexIndices[2]].vertex[0];
				  m_pMS3DGroups[i].vertices[k * 3 + 2].pos.y = m_pMS3DVertices[m_pMS3DTriangles[m_pMS3DGroups[i].triangleIndices[k]].vertexIndices[2]].vertex[1];
				  m_pMS3DGroups[i].vertices[k * 3 + 2].pos.z = m_pMS3DVertices[m_pMS3DTriangles[m_pMS3DGroups[i].triangleIndices[k]].vertexIndices[2]].vertex[2];
				  m_pMS3DGroups[i].vertices[k * 3 + 2].normal.x = m_pMS3DTriangles[m_pMS3DGroups[i].triangleIndices[k]].vertexNormals[2][0];
				  m_pMS3DGroups[i].vertices[k * 3 + 2].normal.y = m_pMS3DTriangles[m_pMS3DGroups[i].triangleIndices[k]].vertexNormals[2][1];
				  m_pMS3DGroups[i].vertices[k * 3 + 2].normal.z = m_pMS3DTriangles[m_pMS3DGroups[i].triangleIndices[k]].vertexNormals[2][2];
				  m_pMS3DGroups[i].vertices[k * 3 + 2].uv1.x = m_pMS3DTriangles[m_pMS3DGroups[i].triangleIndices[k]].s[2];
				  m_pMS3DGroups[i].vertices[k * 3 + 2].uv1.y = m_pMS3DTriangles[m_pMS3DGroups[i].triangleIndices[k]].t[2];
				  m_pMS3DGroups[i].vertices[k * 3 + 2].boneIndex.x = m_pMS3DVertices[m_pMS3DTriangles[m_pMS3DGroups[i].triangleIndices[k]].vertexIndices[0]].boneId;

				  m_pMS3DGroups[i].vertices[k * 3 + 2].boneIndex.x = m_pMS3DVertices[m_pMS3DTriangles[m_pMS3DGroups[i].triangleIndices[k]].vertexIndices[2]].boneId;
				  m_pMS3DGroups[i].vertices[k * 3 + 2].boneIndex.y = 0;
				  m_pMS3DGroups[i].vertices[k * 3 + 2].boneIndex.z = 0;
				  m_pMS3DGroups[i].vertices[k * 3 + 2].boneIndex.w = 0;
				  m_pMS3DGroups[i].vertices[k * 3 + 2].boneweight.x = 1;
				  m_pMS3DGroups[i].vertices[k * 3 + 2].boneweight.y = 0;
				  m_pMS3DGroups[i].vertices[k * 3 + 2].boneweight.z = 0;
				  m_pMS3DGroups[i].vertices[k * 3 + 2].boneweight.w = 0;
				  m_pMS3DGroups[i].OriginalVertices[k * 3 + 0] = m_pMS3DGroups[i].vertices[k * 3 + 0];
				  m_pMS3DGroups[i].OriginalVertices[k * 3 + 1] = m_pMS3DGroups[i].vertices[k * 3 + 1];
				  m_pMS3DGroups[i].OriginalVertices[k * 3 + 2] = m_pMS3DGroups[i].vertices[k * 3 + 2];


			  }
		 }

		 for (unsigned int i = 0; i < m_NumOfGroups; i++)
		 {
			 
			 D3D11_BUFFER_DESC vbdesc;
			 vbdesc.ByteWidth = BWSG::euVertexPNTTIW::GetVBInfo().GetByteSize() *m_pMS3DGroups[i].numVertices ;
			 vbdesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			 vbdesc.Usage = D3D11_USAGE_DYNAMIC;
			 vbdesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			 vbdesc.MiscFlags =0;
			 vbdesc.StructureByteStride = 0;

			 HRESULT hr;

			 if (FAILED(hr =  pDevice->CreateBuffer(&vbdesc, NULL, &m_pMS3DGroups[i].m_pVB)))
			 {
				 return; 
			 }
			 U8 * pLockPtr = nullptr;

			 D3D11_MAPPED_SUBRESOURCE map;
			 hr = pContext->Map(m_pMS3DGroups[i].m_pVB, 0, D3D11_MAP_WRITE_DISCARD, 0, &map);
			 pLockPtr = reinterpret_cast < U8 * > ( map.pData );

			 memcpy( pLockPtr,&(m_pMS3DGroups[i].vertices[0]) , BWSG::euVertexPNTTIW::GetVBInfo().GetByteSize() *m_pMS3DGroups[i].numVertices);

			 pContext->Unmap(m_pMS3DGroups[i].m_pVB , 0);
		 }


		 {


		 }
	}
	int  CMS3DRender::FindJointByName(const char * name)
	{
		for (int i = 0; i < m_NumOfJoint; i++)
			if (!strcmp(m_pMS3DJoint[i].name, name))
				return i;
		return -1;
	}
	void CMS3DRender::SetupJoints() 
	{

		for (int i = 0; i < m_NumOfJoint; i++) {
			m_pMS3DJoint[i].parentIndex = FindJointByName(m_pMS3DJoint[i].parentName);
		}
		for (int i = 0; i < m_NumOfJoint; i++) 
		{
			MS3DKeyframeJoint *joint = &m_pMS3DJoint[i];
			AngleMatrix(joint->rot, joint->matLocalSkeleton);
			joint->matLocalSkeleton[0][3]= joint->pos[0];
			joint->matLocalSkeleton[1][3]= joint->pos[1];
			joint->matLocalSkeleton[2][3]= joint->pos[2];


			if (joint->parentIndex == -1)
			{
				memcpy(joint->matGlobalSkeleton, joint->matLocalSkeleton, sizeof(joint->matGlobalSkeleton));
			}
			else
			{
				MS3DKeyframeJoint *parentJoint = &m_pMS3DJoint[joint->parentIndex];
				R_ConcatTransforms(parentJoint->matGlobalSkeleton, joint->matLocalSkeleton, joint->matGlobalSkeleton);
			}

			SetupTangents();
		}
	}
	void CMS3DRender::SetupTangents()
	{
		for (size_t j = 0; j < m_NumOfJoint; j++)
		{
			MS3DKeyframeJoint *joint = &m_pMS3DJoint[j];
			int numPositionKeys = (int) joint->numKeyFramesTrans;
			joint->keyTangent = new MS3DTangent[numPositionKeys];

			// clear all tangents (zero derivatives)
			for (int k = 0; k < numPositionKeys; k++)
			{
				joint->keyTangent[k].tangentIn[0] = 0.0f;
				joint->keyTangent[k].tangentIn[1] = 0.0f;
				joint->keyTangent[k].tangentIn[2] = 0.0f;
				joint->keyTangent[k].tangentOut[0] = 0.0f;
				joint->keyTangent[k].tangentOut[1] = 0.0f;
				joint->keyTangent[k].tangentOut[2] = 0.0f;
			}

			// if there are more than 2 keys, we can calculate tangents, otherwise we use zero derivatives
			if (numPositionKeys > 2)
			{
				for (int k = 0; k < numPositionKeys; k++)
				{
					// make the curve tangents looped
					int k0 = k - 1;
					if (k0 < 0)
						k0 = numPositionKeys - 1;
					int k1 = k;
					int k2 = k + 1;
					if (k2 >= numPositionKeys)
						k2 = 0;

					// calculate the tangent, which is the vector from key[k - 1] to key[k + 1]
					float tangent[3];
					tangent[0] = (joint->keyFramesTrans[k2].position[0] - joint->keyFramesTrans[k0].position[0]);
					tangent[1] = (joint->keyFramesTrans[k2].position[1] - joint->keyFramesTrans[k0].position[1]);
					tangent[2] = (joint->keyFramesTrans[k2].position[2] - joint->keyFramesTrans[k0].position[2]);

					// weight the incoming and outgoing tangent by their time to avoid changes in speed, if the keys are not within the same interval
					float dt1 = joint->keyFramesTrans[k1].time - joint->keyFramesTrans[k0].time;
					float dt2 = joint->keyFramesTrans[k2].time - joint->keyFramesTrans[k1].time;
					float dt = dt1 + dt2;
					joint->keyTangent[k1].tangentIn[0] = tangent[0] * dt1 / dt;
					joint->keyTangent[k1].tangentIn[1] = tangent[1] * dt1 / dt;
					joint->keyTangent[k1].tangentIn[2] = tangent[2] * dt1 / dt;

					joint->keyTangent[k1].tangentOut[0] = tangent[0] * dt2 / dt;
					joint->keyTangent[k1].tangentOut[1] = tangent[1] * dt2 / dt;
					joint->keyTangent[k1].tangentOut[2] = tangent[2] * dt2 / dt;
				}
			}
		}
	}
	void CMS3DRender::Update()
	{

		
		
		if ( timer > m_TotalFrames )
			timer = 0.0f;

		if (timer < 0.0f )
		{
			for (int i = 0; i < m_NumOfJoint ; i++)
			{
				MS3DKeyframeJoint *joint = &m_pMS3DJoint[i];
				for (int k = 0; k < 3; k++)
				{
					for (int l = 0; l < 4; l++) 
					{
						m_pMS3DJoint[i].matLocal[k][l] = m_pMS3DJoint[i].matLocalSkeleton[k][l];
						m_pMS3DJoint[i].matGlobal[k][l] = m_pMS3DJoint[i].matGlobalSkeleton[k][l];
					}
				}

			}

		}
		else
		{
			RebuildJoints();
		}

		if ( GetKeyState(VK_SPACE) & 0x8000 ) 
		{
			playani =  !playani;
		}

		if ( GetKeyState(VK_RETURN) & 0x8000 ) 
		{
			timer = 0.0f;
		}

  		if ( !playani )
		{
		}
		else
		{
			timer += 0.033f;
		}

	
	}
	void CMS3DRender::RebuildJoints()
	{
		if (timer < 0.0f) 
		{
			for (int i = 0; i < m_NumOfJoint; i++)
			{
				for (int k = 0; k < 3; k++)
				{
					for (int l = 0; l < 4; l++) 
					{
						m_pMS3DJoint[i].matGlobal[k][l] = m_pMS3DJoint[i].matGlobalSkeleton[k][l];
						m_pMS3DJoint[i].matLocalSkeleton[k][l] = m_pMS3DJoint[i].matLocal[k][l];
					}
				}
			}
		} 
		else
		{
			for (int i = 0; i < m_NumOfJoint; i++) 
			{
				RebuildJoint(&m_pMS3DJoint[i]);
			}
		}
	}
	void CMS3DRender::RebuildJoint(MS3DKeyframeJoint *joint)
	{
		  float frame = timer;

		  vec3_t pos = { 0.0f, 0.0f, 0.0f };
		  int numPositionKeys = (int) joint->numKeyFramesTrans;
		  if (numPositionKeys > 0)
		  {
			  int i1 = -1;
			  int i2 = -1;

			  for (int i = 0; i < (numPositionKeys - 1); i++)
			  {
				  if (frame >= joint->keyFramesTrans[i].time && frame < joint->keyFramesTrans[i + 1].time)
				  {
					  i1 = i;
					  i2 = i + 1;
					  break;
				  }
			  }

			  if (i1 == -1 || i2 == -1)
			  {
				  if (frame < joint->keyFramesTrans[0].time)
				  {
					  pos[0] = joint->keyFramesTrans[0].position[0];
					  pos[1] = joint->keyFramesTrans[0].position[1];
					  pos[2] = joint->keyFramesTrans[0].position[2];
				  }

				  else if (frame >= joint->keyFramesTrans[numPositionKeys - 1].time)
				  {
					  pos[0] = joint->keyFramesTrans[numPositionKeys - 1].position[0];
					  pos[1] = joint->keyFramesTrans[numPositionKeys - 1].position[1];
					  pos[2] = joint->keyFramesTrans[numPositionKeys - 1].position[2];
				  }
			  }


			  else
			  {
				  MS3DKeyframePosition *p0 = &joint->keyFramesTrans[i1];
				  MS3DKeyframePosition *p1 = &joint->keyFramesTrans[i2];
				  MS3DTangent *m0 = &joint->keyTangent[i1];
				  MS3DTangent *m1 = &joint->keyTangent[i2];

				  float t = (frame - joint->keyFramesTrans[i1].time) / (joint->keyFramesTrans[i2].time - joint->keyFramesTrans[i1].time);
				  float t2 = t * t;
				  float t3 = t2 * t;

				  float h1 =  2.0f * t3 - 3.0f * t2 + 1.0f;
				  float h2 = -2.0f * t3 + 3.0f * t2;
				  float h3 =         t3 - 2.0f * t2 + t;
				  float h4 =         t3 -        t2;

				  pos[0] = h1 * p0->position[0] + h3 * m0->tangentOut[0] + h2 * p1->position[0] + h4 * m1->tangentIn[0];
				  pos[1] = h1 * p0->position[1] + h3 * m0->tangentOut[1] + h2 * p1->position[1] + h4 * m1->tangentIn[1];
				  pos[2] = h1 * p0->position[2] + h3 * m0->tangentOut[2] + h2 * p1->position[2] + h4 * m1->tangentIn[2];
			  }
		  }

		  BWSB::euVector4 quat = BWSB::euVector4( 0.0f, 0.0f, 0.0f, 1.0f );
		  int numRotationKeys = (int) joint->numKeyFramesRot;
		  if (numRotationKeys > 0)
		  {
			  int i1 = -1;
			  int i2 = -1;

			  for (int i = 0; i < (numRotationKeys - 1); i++)
			  {
				  if (frame >= joint->keyFramesRot[i].time && frame < joint->keyFramesRot[i + 1].time)
				  {
					  i1 = i;
					  i2 = i + 1;
					  break;
				  }
			  }

			  if (i1 == -1 || i2 == -1)
			  {
				  if (frame < joint->keyFramesRot[0].time)
				  {
					  AngleQuaternion(joint->keyFramesRot[0].rotation, quat.v);
				  }

				  else if (frame >= joint->keyFramesRot[numRotationKeys - 1].time)
				  {
					  AngleQuaternion(joint->keyFramesRot[numRotationKeys - 1].rotation, quat.v);
				  }
			  }
			  else
			  {
				  float t = (frame - joint->keyFramesRot[i1].time) / (joint->keyFramesRot[i2].time - joint->keyFramesRot[i1].time);
				  BWSB::euVector4 q1;
				  AngleQuaternion(joint->keyFramesRot[i1].rotation, q1.v);
				  BWSB::euVector4 q2;
				  AngleQuaternion(joint->keyFramesRot[i2].rotation, q2.v);
				  QuaternionSlerp(q1.v, q2.v, t, quat.v);
			  }
		  }

		  // make a matrix from pos/quat
		  float matAnimate[3][4];
		  QuaternionMatrix(quat.v, matAnimate);
		  matAnimate[0][3] = pos[0];
		  matAnimate[1][3] = pos[1];
		  matAnimate[2][3] = pos[2];

		  // animate the local joint matrix using: matLocal = matLocalSkeleton * matAnimate
		  R_ConcatTransforms(joint->matLocalSkeleton, matAnimate, joint->matLocal);

		  // build up the hierarchy if joints
		  // matGlobal = matGlobal(parent) * matLocal
		  if (joint->parentIndex == -1)
		  {
			  memcpy(joint->matGlobal, joint->matLocal, sizeof(joint->matGlobalSkeleton));
		  }
		  else
		  {
			  MS3DKeyframeJoint *parentJoint = &m_pMS3DJoint[joint->parentIndex];
			  R_ConcatTransforms(parentJoint->matGlobal, joint->matLocal, joint->matGlobal);
		  }
	}



	void CMS3DRender::Render( ID3D11DeviceContext* pContext)
	{


		UINT offset = 0;
		UINT stride =  BWSG::euVertexPNTTIW::GetVBInfo().GetByteSize() ;		
		{
			BWSB::euMatrix4 world;
			world.makeIdentity();

			BWSB::euMatrix4 view;
			view.makeIdentity();


			BWSB::euVector3 pos = BWSB::euVector3(0.0f, 50.0f, -100.0f);
			BWSB::euVector3 dir = BWSB::euVector3(0.0f, 0.0f, 0.0f);
			BWSB::euVector3 up = BWSB::euVector3(0.0f, 1.0f, 0.0f);
			view.makeViewMatrix( &pos, &dir , &up);

			BWSB::euMatrix4 pro;
			pro.makeIdentity();
			pro.makePerspectiveLH( 1.570796327f, static_cast < float > ( _RENDERER_DEF.GetClientWidth() ) / static_cast < float > ( _RENDERER_DEF.GetClientHeight() ), 1.0f, 10000.0f);

			m_pEffect->GetVariableByName("World")->AsMatrix()->SetMatrix((world.m1));
			m_pEffect->GetVariableByName("View")->AsMatrix()->SetMatrix((view.m1));
			m_pEffect->GetVariableByName("Projection")->AsMatrix()->SetMatrix((pro.m1));
			m_pEffect->GetVariableByName("WVP")->AsMatrix()->SetMatrix((pro.m1));

			BWSB::euMatrix4 *  matGlobal = new BWSB::euMatrix4[m_NumOfJoint];
			BWSB::euMatrix4 *  matGlobalSkeleton = new BWSB::euMatrix4[m_NumOfJoint];

			for ( int  i = 0 ; i < m_NumOfJoint ; i++ )
			{
				matGlobal[i].m[0][0] = m_pMS3DJoint[i].matGlobal[0][0];
				matGlobal[i].m[0][1] = m_pMS3DJoint[i].matGlobal[0][1];
				matGlobal[i].m[0][2] = m_pMS3DJoint[i].matGlobal[0][2];
				matGlobal[i].m[0][3] = m_pMS3DJoint[i].matGlobal[0][3];

				matGlobal[i].m[1][0] = m_pMS3DJoint[i].matGlobal[1][0];
				matGlobal[i].m[1][1] = m_pMS3DJoint[i].matGlobal[1][1];
				matGlobal[i].m[1][2] = m_pMS3DJoint[i].matGlobal[1][2];
				matGlobal[i].m[1][3] = m_pMS3DJoint[i].matGlobal[1][3];

				matGlobal[i].m[2][0] = m_pMS3DJoint[i].matGlobal[2][0];
				matGlobal[i].m[2][1] = m_pMS3DJoint[i].matGlobal[2][1];
				matGlobal[i].m[2][2] = m_pMS3DJoint[i].matGlobal[2][2];
				matGlobal[i].m[2][3] = m_pMS3DJoint[i].matGlobal[2][3];

				matGlobal[i].m[3][0] = 0;
				matGlobal[i].m[3][1] = 0;
				matGlobal[i].m[3][2] = 0;
				matGlobal[i].m[3][3] = 0;

				matGlobalSkeleton[i].m[0][0] = m_pMS3DJoint[i].matGlobalSkeleton[0][0];
				matGlobalSkeleton[i].m[0][1] = m_pMS3DJoint[i].matGlobalSkeleton[0][1];
				matGlobalSkeleton[i].m[0][2] = m_pMS3DJoint[i].matGlobalSkeleton[0][2];
				matGlobalSkeleton[i].m[0][3] = m_pMS3DJoint[i].matGlobalSkeleton[0][3];

				matGlobalSkeleton[i].m[1][0] = m_pMS3DJoint[i].matGlobalSkeleton[1][0];
				matGlobalSkeleton[i].m[1][1] = m_pMS3DJoint[i].matGlobalSkeleton[1][1];
				matGlobalSkeleton[i].m[1][2] = m_pMS3DJoint[i].matGlobalSkeleton[1][2];
				matGlobalSkeleton[i].m[1][3] = m_pMS3DJoint[i].matGlobalSkeleton[1][3];

				matGlobalSkeleton[i].m[2][0] = m_pMS3DJoint[i].matGlobalSkeleton[2][0];
				matGlobalSkeleton[i].m[2][1] = m_pMS3DJoint[i].matGlobalSkeleton[2][1];
				matGlobalSkeleton[i].m[2][2] = m_pMS3DJoint[i].matGlobalSkeleton[2][2];
				matGlobalSkeleton[i].m[2][3] = m_pMS3DJoint[i].matGlobalSkeleton[2][3];

				matGlobalSkeleton[i].m[3][0] = 0;
				matGlobalSkeleton[i].m[3][1] = 0;
				matGlobalSkeleton[i].m[3][2] = 0;
				matGlobalSkeleton[i].m[3][3] = 0;
			}

			HRESULT hr = m_pEffect->GetVariableByName("matGlobal")->AsMatrix()->SetMatrixArray(matGlobal[0].m1 ,0 , m_NumOfJoint);
			hr = m_pEffect->GetVariableByName("matGlobalSkeleton")->AsMatrix()->SetMatrixArray(matGlobalSkeleton[0].m1 ,0 , m_NumOfJoint);

			delete [] matGlobal;
			delete [] matGlobalSkeleton;
			D3DX11_TECHNIQUE_DESC techDesc;
			m_pTech->GetDesc( &techDesc );

			ID3DX11EffectPass* pEffectPass = NULL;

			pEffectPass = m_pTech->GetPassByName( "P1" );
			for (unsigned int i = 0; i < m_NumOfGroups; i++)
			{
				ITexture * pTexture = m_pMS3DMaterials[m_pMS3DGroups[i].materialIndex].pTexture;
				ID3D11ShaderResourceView * pShaderView = (ID3D11ShaderResourceView*)( ((CDX11Texture*)pTexture)->GetShaderView());
				m_pEffect->GetVariableByName("gDiffuseMap")->AsShaderResource()->SetResource(pShaderView);
				pContext->IASetInputLayout( m_pInputLayout);
				pContext->IASetVertexBuffers(0, 1, &m_pMS3DGroups[i].m_pVB, &stride, &offset);
				pContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
				pEffectPass->Apply(0, RENDERER_CONTEXT11(0) );
				pContext->Draw(m_pMS3DGroups[i].numVertices, 0 );
			}


		}
	}





}
