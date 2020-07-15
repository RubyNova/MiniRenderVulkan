#ifndef CAMERABUFFEROBJECT_H
#define CAMERABUFFEROBJECT_H

#include "../../ThirdParty/glm/glm/glm.hpp"
#include "../../ThirdParty/glm/glm/gtc/quaternion.hpp"
#include "../../ThirdParty/glm/glm/gtc/matrix_transform.hpp"

struct CameraBufferObject {
    glm::mat4 view;
    glm::mat4 proj;
};

#endif //!CAMERABUFFEROBJECT_H