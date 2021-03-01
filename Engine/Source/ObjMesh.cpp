#include "..\Include\ObjMesh.h"
#include <fstream>
ObjMesh::ObjMesh()
{
}

ObjMesh::~ObjMesh()
{
}

void ObjMesh::Initialize(wstring _fp)
{
	m_filePath = _fp;
	if (L"" == m_filePath)
	{
		assert(0 && L"Please, Insert to FilePath");
		return;
	}

	CreateVertexBuffer();
	CreateIndexBuffer();

}

void ObjMesh::CreateVertexBuffer()
{

	vector<float> vertex;
	vector<float> uv;
	vector<float> vn;

	{
#pragma region VERTEX POS IMPORT

		ifstream file;
		file.open(m_filePath);
		string str;
		

		// v 찾기

		while (!file.eof())
		{
			getline(file, str);
			if ('v' == str[0]) // T면 라인개행을을 멈춰라
				break;
		}

		while ('v' == str[0]) // 첫번째 문자열이 v일때
		{
			int iIndex = 0;

			while (true)
			{
				while (' ' == str[iIndex])
				{
					// 공백이면 뛰어 넘기기
					++iIndex;
				}
				iIndex += 3; // 0번째 인덱스에서
																	//for . x 위치
				int XMin = iIndex, XMax = iIndex;				// 문자열 인덱스 위치
				while (' ' != str[iIndex])
				{
					++iIndex;
					XMax = iIndex; // 숫자 문자열 길이
				}
				double x = atof(str.substr(XMin, XMax - XMin).c_str()); // 그위치에 범위를 지정하면 ?자료형으로 값 하나를 반환

				while (' ' == str[iIndex])						    //for. Y위치
				{
					++iIndex;
				}
				int YMin = iIndex, YMax = iIndex;
				while (str[iIndex] != ' ') {
					++iIndex;
					YMax = iIndex;
				}
				double y = atof(str.substr(YMin, YMax - YMin).c_str());

				while (' ' == str[iIndex])						    //for. Z위치
				{
					++iIndex;
				}
				int  ZMin = iIndex, ZMax = iIndex;
				while (' ' != str[iIndex]) {
					size_t a = str.length();
					if (str.length() <= iIndex)
						break;

					iIndex++;
					ZMax = iIndex;

				}
				double z = atof(str.substr(ZMin, ZMax - ZMin).c_str());

				// 한줄읽고 탈출, 
				vertex.emplace_back((float)x);
				vertex.emplace_back((float)y);
				vertex.emplace_back((float)z);

				break;

			}
			getline(file, str);

		}
		file.close();
#pragma endregion
	}

	{
#pragma region UV IMPORT
	
	ifstream file;
	file.open(m_filePath);
	string str;

	// v 찾기

	while (!file.eof())
	{
		getline(file, str);
		if ('v' == str[0] && 't' == str[1])
			break;
			
	}

	while ('t' == str[1]) // 첫번째 문자열이 v일때
	{
		int iIndex = 0;

		while (true)
		{
			while (' ' == str[iIndex])
			{
				// 공백이면 뛰어 넘기기
				++iIndex;
			}
			iIndex += 3; // 0번째 인덱스에서
						 //for . x 위치
			int XMin = iIndex, XMax = iIndex;				// 문자열 인덱스 위치
			while (' ' != str[iIndex])
			{
				++iIndex;
				XMax = iIndex; // 숫자 문자열 길이
			}
			double x = atof(str.substr(XMin, XMax - XMin).c_str()); // 그위치에 범위를 지정하면 ?자료형으로 값 하나를 반환

			while (' ' == str[iIndex])						    //for. Y위치
			{
				++iIndex;
			}
			int YMin = iIndex, YMax = iIndex;
			while (str[iIndex] != ' ') {
				++iIndex;
				YMax = iIndex;
			}
			double y = atof(str.substr(YMin, YMax - YMin).c_str());

			while (' ' == str[iIndex])						    //for. Z위치
			{
				++iIndex;
			}
			int  ZMin = iIndex, ZMax = iIndex;
			while (' ' != str[iIndex]) {
				size_t a = str.length();
				if (str.length() <= iIndex)
					break;

				iIndex++;
				ZMax = iIndex;

			}
			double z = atof(str.substr(ZMin, ZMax - ZMin).c_str());

			// 한줄읽고 탈출, 
			Vector3 vec3 = D3DXVECTOR3((float)x, (float)y, (float)z);
			uv.emplace_back((float)x);
			uv.emplace_back((float)y);
			uv.emplace_back((float)z);
			break;

		}
		getline(file, str);
		
	}
	file.close();
#pragma endregion
	}

	{
#pragma region VN IMPORT
		ifstream file;
		file.open(m_filePath);
		string str;

		// v 찾기

		while (!file.eof())
		{
			getline(file, str);
			if ('v' == str[0] && 'n' == str[1])
				break;

		}

		while ('n' == str[1]) // 첫번째 문자열이 v일때
		{
			int iIndex = 0;

			while (true)
			{
				while (' ' == str[iIndex])
				{
					// 공백이면 뛰어 넘기기
					++iIndex;
				}
				iIndex += 3; // 0번째 인덱스에서
							 //for . x 위치
				int XMin = iIndex, XMax = iIndex;				// 문자열 인덱스 위치
				while (' ' != str[iIndex])
				{
					++iIndex;
					XMax = iIndex; // 숫자 문자열 길이
				}
				double x = atof(str.substr(XMin, XMax - XMin).c_str()); // 그위치에 범위를 지정하면 ?자료형으로 값 하나를 반환

				while (' ' == str[iIndex])						    //for. Y위치
				{
					++iIndex;
				}
				int YMin = iIndex, YMax = iIndex;
				while (str[iIndex] != ' ') {
					++iIndex;
					YMax = iIndex;
				}
				double y = atof(str.substr(YMin, YMax - YMin).c_str());

				while (' ' == str[iIndex])						    //for. Z위치
				{
					++iIndex;
				}
				int  ZMin = iIndex, ZMax = iIndex;
				while (' ' != str[iIndex]) {
					size_t a = str.length();
					if (str.length() <= iIndex)
						break;

					iIndex++;
					ZMax = iIndex;

				}
				double z = atof(str.substr(ZMin, ZMax - ZMin).c_str());

				// 한줄읽고 탈출, 
				D3DXVECTOR3 vec3 = D3DXVECTOR3((float)x, (float)y, (float)z);
				vn.emplace_back((float)x);
				vn.emplace_back((float)y);
				vn.emplace_back((float)z);
				break;

			}
			getline(file, str);

		}
		file.close();

#pragma endregion
	}




	ThrowIfFailed(m_device->CreateVertexBuffer(
		sizeof(INPUT_LAYOUT_POSITION_NORMAL_UV) * (UINT)vertex.size(),
		0, // 파티클이나 각종 옵션 조절
		NULL, //D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE2(0),
		D3DPOOL_MANAGED,
		&m_vBuffer,
		nullptr
	));
	
	INPUT_LAYOUT_POSITION_NORMAL_UV* vertices = nullptr;
	m_vBuffer->Lock(0, 0, (void**)&vertices, 0);
	
	
	size_t size = vertex.size() / 3;
	for (size_t i = 0; i < size; ++i)
	{
		vertices[i].position.x = (vertex[i * 3]);
		vertices[i].position.y = (vertex[i * 3 + 1]);
		vertices[i].position.z = (vertex[i * 3 + 2]);
	}
	
	size = uv.size() / 3;
	for (size_t i = 0; i <size; ++i)
	{
		vertices[i].uv.x = (uv[i * 3]);
		vertices[i].uv.y = (uv[i * 3 + 1]);
	}
	size = vn.size() / 3;
	for (int i = 0; i < size; ++i)
	{
		vertices[i].normal.x = (vn[i * 3]);
		vertices[i].normal.y = (vn[i * 3 + 1]);
		vertices[i].normal.z = (vn[i * 3 + 2]);
	}
	

	D3DXComputeBoundingSphere(&vertices[0].position, (DWORD)vertex.size(), sizeof(INPUT_LAYOUT_POSITION_NORMAL_UV), &m_boundingSphereCenter, &m_boundingSphereRadius);
	m_vBuffer->Unlock();
	SetVertexCount((UINT)vertex.size());
	vertex.clear();
	uv.clear();
	vn.clear();



}

void ObjMesh::CreateIndexBuffer()
{
	/*f 1 / 1 / 1 2 / 2 / 1 3 / 3 / 1
		f 4 / 4 / 1 3 / 3 / 1 2 / 2 / 1*/
	vector<float> faces;
	ifstream file;
	file.open(m_filePath);

	string str;
	while (!file.eof())
	{
		getline(file, str);
		if (str[0] == 'f') {
			break;
		}
	}

	while ('f' == str[0])
	{
		int iIndex = 0;
		while (true)
		{
			// 1. 만약에 'f' 뒤에 공백이 쳐있을경우의 예외처리 
			while (' ' == str[iIndex])
				++iIndex;
			

			iIndex += 2; // 읽어야될 인덱스 위치

			int XMin = iIndex, XMax = iIndex;				// 문자열 인덱스 위치
			while ('/' != str[iIndex])
			{
				++iIndex;
				XMax = iIndex; // 숫자 문자열 길이
			}
			int IndexPos_0 = atoi(str.substr(XMin, XMax - XMin).c_str());


			while (' ' != str[iIndex])
				++iIndex;
			int YMin = iIndex, YMax = iIndex;				// 문자열 인덱스 위치
			while ('/' != str[iIndex])
			{
				++iIndex;
				YMax = iIndex; // 숫자 문자열 길이
			}
			int IndexPos_1 = atoi(str.substr(YMin, YMax - YMin).c_str());


			while (' ' != str[iIndex])
				++iIndex;
			int ZMin = iIndex, ZMax = iIndex;				// 문자열 인덱스 위치
			while ('/' != str[iIndex])
			{
				++iIndex;
				ZMax = iIndex; // 숫자 문자열 길이
			}
			int IndexPos_2 = atoi(str.substr(ZMin, ZMax - ZMin).c_str());

			//Vector3 face = Vector3((float)IndexPos_0, (float)IndexPos_1, (float)IndexPos_2);
			// 추가 : 
			faces.emplace_back((float)IndexPos_0);
			faces.emplace_back((float)IndexPos_1);
			faces.emplace_back((float)IndexPos_2);

			break;
		}
		getline(file, str);
	}

	file.close();


	ThrowIfFailed(m_device->CreateIndexBuffer(
		sizeof(short) * (UINT)(faces.size()),
		0,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_iBuffer,
		nullptr));

	short* test = nullptr;
	m_iBuffer->Lock(0, 0, (void**)&test, 0);

	for (size_t i = 0; i < faces.size(); ++i)
	{
		if (i >= faces.size())
			break;
	
		test[i] = (short)faces[i] - 1;

		
	}
	m_iBuffer->Unlock();
	SetFigureCount((UINT)faces.size());
	faces.clear();

}


