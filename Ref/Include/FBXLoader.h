//#pragma once
//#include "VIBuffer.h"
//
//// https://m.blog.naver.com/PostView.nhn?blogId=lifeisforu&logNo=80105645663&proxyReferer=https:%2F%2Fwww.google.com%2F
//// https://github.com/walbourn/contentexporter/tree/master/importfbx
//// https://m.blog.naver.com/PostView.nhn?blogId=doun1290&logNo=221377410153&proxyReferer=https:%2F%2Fwww.google.com%2F
//// 참고
//class FBXLoader :
//	public VIBuffer
//{
//public:
//	FBXLoader();
//	~FBXLoader();
//
//	// VIBuffer을(를) 통해 상속됨
//	virtual void Initialize(wstring _fp = L"") override;
//
//private:
//	Vector3 ReadNormal(FbxMesh* _mesh, int _controlPointIndex, int _vertexCount);
//	Vector3 ReadBinormal(FbxMesh* _mesh, int _controlPointIndex, int _vertexCount);
//	Vector3 ReadTangent(FbxMesh* _mesh, int _controlPointIndex, int _vertexCount);
//	Vector2 ReadUV(FbxMesh* _mesh, int _controlPointIndex, int _uvIndex);
//
//private:
//	template <typename T>
//	Vector3 GetPoint(fbxsdk::FbxLayerElement* _element, int _contolPointIndex, int _vertexCount)
//	{
//		Vector3 result;
//
//		auto e = _element->GetMappingMode();
//		auto refMode = _element->GetReferenceMode();
//		switch (e)
//		{
//		case fbxsdk::FbxLayerElement::eByControlPoint:
//		{
//			switch (refMode)
//			{
//			case fbxsdk::FbxLayerElement::eDirect:
//			{
//				result.x = float(((T*)_element)->GetDirectArray().GetAt(_contolPointIndex).mData[0]);
//				result.y = float(((T*)_element)->GetDirectArray().GetAt(_contolPointIndex).mData[1]);
//				result.z = float(((T*)_element)->GetDirectArray().GetAt(_contolPointIndex).mData[2]);
//				break;
//			}
//			case fbxsdk::FbxLayerElement::eIndexToDirect:
//			{
//				int index = ((T*)_element)->GetIndexArray().GetAt(_contolPointIndex);
//				result.x = float(((T*)_element)->GetDirectArray().GetAt(index).mData[0]);
//				result.y = float(((T*)_element)->GetDirectArray().GetAt(index).mData[1]);
//				result.z = float(((T*)_element)->GetDirectArray().GetAt(index).mData[2]);
//				break;
//			}
//			default:
//				assert(L"Error! Invalid vertex reference mode!" && 0);
//				break;
//			}
//			break;
//		}
//		case fbxsdk::FbxLayerElement::eByPolygonVertex:
//		{
//			switch (refMode)
//			{
//			case fbxsdk::FbxLayerElement::eDirect:
//			{
//				result.x = float(((T*)_element)->GetDirectArray().GetAt(_vertexCount).mData[0]);
//				result.y = float(((T*)_element)->GetDirectArray().GetAt(_vertexCount).mData[1]);
//				result.z = float(((T*)_element)->GetDirectArray().GetAt(_vertexCount).mData[2]);
//				break;
//			}
//		
//			case fbxsdk::FbxLayerElement::eIndexToDirect:
//			{
//				int index = ((T*)_element)->GetIndexArray().GetAt(_vertexCount);
//				result.x = float(((T*)_element)->GetDirectArray().GetAt(index).mData[0]);
//				result.y = float(((T*)_element)->GetDirectArray().GetAt(index).mData[1]);
//				result.z = float(((T*)_element)->GetDirectArray().GetAt(index).mData[2]);
//				break;
//			}
//			default:
//				assert(L"Error! Invalid vertex reference mode!" && 0);
//				break;
//			}
//
//
//			break;
//		}
//		default:
//			break;
//		}
//
//
//		return result;
//	}
//};
//
