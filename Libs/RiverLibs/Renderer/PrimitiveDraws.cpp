//
//  PrimitiveDraws.cpp
//  RiverEngine
//
//  Created by 大川恭平 on 2018/07/12.
//  Copyright © 2018年 BiGRiVER. All rights reserved.
//

#include "PrimitiveDraws.hpp"

namespace PrimitiveDraws
{
    void drawPlaneCircle(Vector3 pos,float radius,Color4 color)
    {
        auto useProgram = Director::getInstance()->getGLProgram("PCStatic");
        
        GLint attr_pos = useProgram->getAttribLocation("attr_pos");
        GLint attr_color = useProgram->getAttribLocation("attr_color");
        
        GLint unif_lookat = useProgram->getUnifLocation("unif_lookat");
        GLint unif_projection = useProgram->getUnifLocation("unif_projection");
        GLint unif_world = useProgram->getUnifLocation("unif_world");
        GLint unif_color = useProgram->getUnifLocation("unif_color");
        
        vector<PositionColor> vertex;
        vertex.push_back({{0.0f,0.0f,0.0f},{255,255,255,255}});
        for(int i = 0; i <= 360; i+=12)
        {
            vertex.push_back({{radius*cosf(Deg2Rad(i)),0.0f,radius*sinf(Deg2Rad(i))},{255,255,255,255}});
        }
        
        auto mesh = MeshResource<PositionColor>::createWithVertex(vertex);
        
        useProgram->use();
        glEnable(GL_DEPTH_TEST);
        glEnableVertexAttribArray(attr_pos);
        glEnableVertexAttribArray(attr_color);
        
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        Matrix4x4 lookAt,projection;
        Director::getInstance()->getScene()->GetMainCamera()->GetLookAtProjection(lookAt, projection);
        
        Matrix4x4 posMat;
        posMat = Matrix4x4::createTranslate(pos.x, pos.y, pos.z);
        Matrix4x4 world = posMat;
        
        glUniformMatrix4fv(unif_lookat, 1, GL_FALSE, lookAt.matrix);
        glUniformMatrix4fv(unif_projection, 1, GL_FALSE, projection.matrix);
        glUniformMatrix4fv(unif_world, 1, GL_FALSE, world.matrix);
        glUniform4f(unif_color, color.r, color.g, color.b, color.a);
        
        glVertexAttribPointer(attr_pos, 3, GL_FLOAT, GL_FALSE, sizeof(PositionColor), (GLvoid*)mesh->GetVertexPointer());
        glVertexAttribPointer(attr_color, 4, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(PositionColor), (GLvoid*)((GLubyte*)mesh->GetVertexPointer() + sizeof(GLfloat)*3));
        
        glDrawArrays(GL_TRIANGLE_FAN, 0, (GLsizei)mesh->GetVertexCount());
        
        glDisable(GL_DEPTH_TEST);
        glDisableVertexAttribArray(attr_pos);
        glDisableVertexAttribArray(attr_color);
        
        glDisable(GL_BLEND);
    }
}
