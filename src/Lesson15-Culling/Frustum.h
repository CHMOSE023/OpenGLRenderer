#pragma once
class Frustum 
{
public:
    Frustum(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix) 
    {
        // 计算视锥体的六个平面
        glm::mat4 clipMatrix = projectionMatrix * viewMatrix;

        // 左平面
        planes[0] = glm::vec4(clipMatrix[0][3] + clipMatrix[0][0],
            clipMatrix[1][3] + clipMatrix[1][0],
            clipMatrix[2][3] + clipMatrix[2][0],
            clipMatrix[3][3] + clipMatrix[3][0]);
        // 右平面
        planes[1] = glm::vec4(clipMatrix[0][3] - clipMatrix[0][0],
            clipMatrix[1][3] - clipMatrix[1][0],
            clipMatrix[2][3] - clipMatrix[2][0],
            clipMatrix[3][3] - clipMatrix[3][0]);
        // 底平面
        planes[2] = glm::vec4(clipMatrix[0][3] + clipMatrix[0][1],
            clipMatrix[1][3] + clipMatrix[1][1],
            clipMatrix[2][3] + clipMatrix[2][1],
            clipMatrix[3][3] + clipMatrix[3][1]);
        // 顶平面
        planes[3] = glm::vec4(clipMatrix[0][3] - clipMatrix[0][1],
            clipMatrix[1][3] - clipMatrix[1][1],
            clipMatrix[2][3] - clipMatrix[2][1],
            clipMatrix[3][3] - clipMatrix[3][1]);
        // 近平面
        planes[4] = glm::vec4(clipMatrix[0][3] + clipMatrix[0][2],
            clipMatrix[1][3] + clipMatrix[1][2],
            clipMatrix[2][3] + clipMatrix[2][2],
            clipMatrix[3][3] + clipMatrix[3][2]);
        // 远平面
        planes[5] = glm::vec4(clipMatrix[0][3] - clipMatrix[0][2],
            clipMatrix[1][3] - clipMatrix[1][2],
            clipMatrix[2][3] - clipMatrix[2][2],
            clipMatrix[3][3] - clipMatrix[3][2]);

        // 归一化平面
        for (int i = 0; i < 6; ++i) {
            planes[i] /= glm::length(glm::vec3(planes[i]));
        }
    }

    // 判断点是否在视锥体内部
    bool isPointInside(const glm::vec3& point) const {
        for (int i = 0; i < 6; ++i) {
            if (glm::dot(glm::vec3(planes[i]), point) + planes[i].w < 0) {
                return false; // 点在视锥体外部
            }
        }
        return true; // 点在视锥体内部
    }

    // 判断包围球是否在视锥体内部
    bool isSphereInside(const glm::vec3& center, float radius) const {
        for (int i = 0; i < 6; ++i) {
            if (glm::dot(glm::vec3(planes[i]), center) + planes[i].w < -radius) {
                return false; // 球与视锥体平面相交
            }
        }
        return true; // 球完全位于视锥体内部
    }

    // 判断包围盒是否在视锥体内部
    bool isBoundingBoxInside(const glm::vec3& minPoint, const glm::vec3& maxPoint) const {
        for (int i = 0; i < 6; ++i) {
            glm::vec3 p;
            p.x = (planes[i].x > 0) ? maxPoint.x : minPoint.x;
            p.y = (planes[i].y > 0) ? maxPoint.y : minPoint.y;
            p.z = (planes[i].z > 0) ? maxPoint.z : minPoint.z;

            if (glm::dot(glm::vec3(planes[i]), p) + planes[i].w < 0) {
                return false; // 盒子与视锥体平面相交
            }
        }
        return true; // 盒子完全位于视锥体内部
    }

private:
    glm::vec4 planes[6]; // 视锥体的六个平面
};

