#pragma once

#include "DirectXMath.h"
#include <vector>

// create a box, vertex only have attribute position 
void CreateBox(const DirectX::XMFLOAT3 center, const float width/*x*/, const float length/*y*/, const float depth/**/, 
    std::vector<DirectX::XMFLOAT3> vertex_vec, std::vector<unsigned int> index_vec);