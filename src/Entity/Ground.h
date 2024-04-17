#pragma once
#include "Entity.h"
#include <glm/glm.hpp>
#include "../Core/Camera.h"
#include "../Shader/Shader_P3_C4_T2.h"
class Ground :public Entity
{
	typedef struct Vertex
	{
		glm::vec3 pos;
		glm::vec4 col;
		glm::vec2 uv;
	} Vertex;

public:
	Ground() 
	{
		m_vao = -1;
		m_vbo = -1;			
	};
	~Ground(){};

	virtual void Init()  // ����׼��
	{
		float   gSize = 100;
		float   gPos = -5;
		float   rept = 20;

		// ���Ƶ�������	
		static const Vertex grounds[6] =
		{
			//       ����                    ��ɫ                   UV                
		   { { -gSize, gPos,-gSize }, { 1.f, 1.f, 1.f,1.0f },{  0.0f,0.0f } },
		   { {  gSize, gPos,-gSize }, { 1.f, 1.f, 1.f,1.0f },{  rept,0.0f } },
		   { {  gSize, gPos, gSize }, { 1.f, 1.f, 1.f,1.0f },{  rept,rept }},

		   { { -gSize, gPos,-gSize }, { 1.f, 1.f, 1.f,1.0f },{  0.0f,0.0f } },
		   { {  gSize, gPos, gSize }, { 1.f, 1.f, 1.f,1.0f },{  rept,rept } },
		   { { -gSize, gPos, gSize }, { 1.f, 1.f, 1.f,1.0f },{   0.0f,rept } }

		};

		m_shader.Initialize(); // ��ʼ��shader		
	

		// �����Դ沢�򶥵㻺���������	
		glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(grounds), grounds, GL_STATIC_DRAW);

		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);
		glEnableVertexAttribArray(m_shader.m_position);
		glVertexAttribPointer(m_shader.m_position, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		glEnableVertexAttribArray(m_shader.m_color);
		glVertexAttribPointer(m_shader.m_color, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)12);
		glEnableVertexAttribArray(m_shader.m_uv);
		glVertexAttribPointer(m_shader.m_uv, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)28);
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}


	virtual void Render(glm::mat4 &mat4) // ����
	{
		glm::mat4 mvp= mat4;
		m_shader.Begin();
		glBindVertexArray(m_vao);
		glUniformMatrix4fv(m_shader.m_mvp, 1, GL_FALSE, (const GLfloat*)&mvp);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		m_shader.End();
	}


public:
	unsigned        m_vao;
	unsigned        m_vbo;
	Shader_P3_C4_T2 m_shader;

};
