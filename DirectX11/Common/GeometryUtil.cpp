#include "GeometryUtil.h"

void CreateBox(const DirectX::XMFLOAT3 center, const float width/*x*/, const float length/*y*/, const float depth/**/, 
    std::vector<DirectX::XMFLOAT3> &vertex_vec, std::vector<unsigned int> &index_vec)
{
    float half_width = width / 2;
    float half_length = length / 2;
    float half_depth = depth / 2;

    vertex_vec.push_back(DirectX::XMFLOAT3(center.x - half_width, center.y - half_length, center.z - half_depth));  // 0
    vertex_vec.push_back(DirectX::XMFLOAT3(center.x - half_width, center.y + half_length, center.z - half_depth));  // 1
    vertex_vec.push_back(DirectX::XMFLOAT3(center.x - half_width, center.y - half_length, center.z + half_depth));  // 2
    vertex_vec.push_back(DirectX::XMFLOAT3(center.x - half_width, center.y + half_length, center.z + half_depth));  // 3
    vertex_vec.push_back(DirectX::XMFLOAT3(center.x + half_width, center.y - half_length, center.z - half_depth));  // 4
    vertex_vec.push_back(DirectX::XMFLOAT3(center.x + half_width, center.y + half_length, center.z - half_depth));  // 5
    vertex_vec.push_back(DirectX::XMFLOAT3(center.x + half_width, center.y - half_length, center.z + half_depth));  // 6
    vertex_vec.push_back(DirectX::XMFLOAT3(center.x + half_width, center.y + half_length, center.z + half_depth));  // 7

    index_vec = {
        0, 1, 3,
        0, 3, 2,
        4, 7, 5,
        4, 6, 7,
        0, 2, 6,
        0, 6, 4,
        1, 7, 3,
        1, 5, 7,
        2, 3, 6,
        3, 7, 6,
        0, 4, 1,
        1, 4, 5
    };
}