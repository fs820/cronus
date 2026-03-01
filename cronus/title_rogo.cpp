//--------------------------------------------
//
// タイトルロゴ [title_rogo.cpp]
// Author: Fuma Sato
//
//--------------------------------------------
#include "title_rogo.h"
#include "object.h"
#include "trans_comp.h"

namespace factory
{
    GameObject createTitleLogo()
    {
        GameObject logo{};
        logo.Add<TransformComponent>(Transform(Vector3(500,500,0), Quaternion::Identity(), Vector3::One()));
        return logo;
    }
}
