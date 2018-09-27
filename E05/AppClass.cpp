#include "AppClass.h"
#include <vector>
void Application::InitVariables(void)
{
	//init the mesh
	m_pMesh = new MyMesh();
	for (size_t i = 0; i < 46; i++)
	{
		m_pMesh->GenerateCube(1.0f, C_BLACK);
	}
	//m_pMesh->GenerateCube(1.0f, C_BLACK);
	//m_pMesh->GenerateSphere(1.0f, 5, C_WHITE);
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	matrix4 m4View = m_pCameraMngr->GetViewMatrix();
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();
	
	matrix4 m4Scale = glm::scale(IDENTITY_M4, vector3(2.0f,2.0f,2.0f));
	static float value = 0.0f;
	matrix4 m4Translate = glm::translate(IDENTITY_M4, vector3(value, 2.0f, 3.0f));
	matrix4 m4Translate2 = glm::translate(IDENTITY_M4, vector3(value, 4.0f, 3.0f));
	matrix4 m4Translate3 = glm::translate(IDENTITY_M4, vector3(value, 6.0f, 3.0f));
	matrix4 m4Translate4 = glm::translate(IDENTITY_M4, vector3(value, 8.0f, 3.0f));
	matrix4 m4Translate5 = glm::translate(IDENTITY_M4, vector3(value-2, 2.0f, 3.0f));
	matrix4 m4Translate6 = glm::translate(IDENTITY_M4, vector3(value-2, 4.0f, 3.0f));
	matrix4 m4Translate7 = glm::translate(IDENTITY_M4, vector3(value-2, 6.0f, 3.0f));
	matrix4 m4Translate8 = glm::translate(IDENTITY_M4, vector3(value-2, 8.0f, 3.0f));
	matrix4 m4Translate9 = glm::translate(IDENTITY_M4, vector3(value + 2, 2.0f, 3.0f));
	matrix4 m4Translate10 = glm::translate(IDENTITY_M4, vector3(value + 2, 4.0f, 3.0f));
	matrix4 m4Translate11 = glm::translate(IDENTITY_M4, vector3(value + 2, 6.0f, 3.0f));
	matrix4 m4Translate12 = glm::translate(IDENTITY_M4, vector3(value + 2, 8.0f, 3.0f));

	matrix4 m4Translate13 = glm::translate(IDENTITY_M4, vector3(value - 4, 2.0f, 3.0f));
	matrix4 m4Translate14 = glm::translate(IDENTITY_M4, vector3(value - 4, 4.0f, 3.0f));
	matrix4 m4Translate15 = glm::translate(IDENTITY_M4, vector3(value - 4, 8.0f, 3.0f));
	matrix4 m4Translate16 = glm::translate(IDENTITY_M4, vector3(value + 4, 2.0f, 3.0f));
	matrix4 m4Translate17 = glm::translate(IDENTITY_M4, vector3(value + 4, 4.0f, 3.0f));
	matrix4 m4Translate18 = glm::translate(IDENTITY_M4, vector3(value + 4, 8.0f, 3.0f));

	matrix4 m4Translate19 = glm::translate(IDENTITY_M4, vector3(value - 6, 2.0f, 3.0f));
	matrix4 m4Translate20 = glm::translate(IDENTITY_M4, vector3(value - 6, 4.0f, 3.0f));
	matrix4 m4Translate21 = glm::translate(IDENTITY_M4, vector3(value - 6, 6.0f, 3.0f));
	matrix4 m4Translate22 = glm::translate(IDENTITY_M4, vector3(value - 6, 8.0f, 3.0f));
	matrix4 m4Translate23 = glm::translate(IDENTITY_M4, vector3(value + 6, 2.0f, 3.0f));
	matrix4 m4Translate24 = glm::translate(IDENTITY_M4, vector3(value + 6, 4.0f, 3.0f));
	matrix4 m4Translate25 = glm::translate(IDENTITY_M4, vector3(value + 6, 6.0f, 3.0f));
	matrix4 m4Translate26 = glm::translate(IDENTITY_M4, vector3(value + 6, 8.0f, 3.0f));
	matrix4 m4Translate27 = glm::translate(IDENTITY_M4, vector3(value + 6, 0.0f, 3.0f));
	matrix4 m4Translate28 = glm::translate(IDENTITY_M4, vector3(value - 6, 0.0f, 3.0f));

	matrix4 m4Translate29 = glm::translate(IDENTITY_M4, vector3(value + 4, 10.0f, 3.0f));
	matrix4 m4Translate30 = glm::translate(IDENTITY_M4, vector3(value - 4, 10.0f, 3.0f));
	matrix4 m4Translate31 = glm::translate(IDENTITY_M4, vector3(value + 6, 12.0f, 3.0f));
	matrix4 m4Translate32 = glm::translate(IDENTITY_M4, vector3(value - 6, 12.0f, 3.0f));
	value += 0.01f;

	matrix4 m4Model = m4Translate * m4Scale;
	matrix4 m4Model2= m4Translate2 * m4Scale;
	matrix4 m4Model3 = m4Translate3 * m4Scale;
	matrix4 m4Model4 = m4Translate4 * m4Scale;
	matrix4 m4Model5 = m4Translate5 * m4Scale;
	matrix4 m4Model6 = m4Translate6 * m4Scale;
	matrix4 m4Model7 = m4Translate7 * m4Scale;
	matrix4 m4Model8 = m4Translate8 * m4Scale;
	matrix4 m4Model9 = m4Translate9 * m4Scale;
	matrix4 m4Model10 = m4Translate10 * m4Scale;
	matrix4 m4Model11 = m4Translate11 * m4Scale;
	matrix4 m4Model12 = m4Translate12 * m4Scale;

	matrix4 m4Model13 = m4Translate13 * m4Scale;
	matrix4 m4Model14 = m4Translate14 * m4Scale;
	matrix4 m4Model15 = m4Translate15 * m4Scale;
	matrix4 m4Model16 = m4Translate16 * m4Scale;
	matrix4 m4Model17 = m4Translate17 * m4Scale;
	matrix4 m4Model18 = m4Translate18 * m4Scale;

	matrix4 m4Model19 = m4Translate19 * m4Scale;
	matrix4 m4Model20 = m4Translate20 * m4Scale;
	matrix4 m4Model21 = m4Translate21 * m4Scale;
	matrix4 m4Model22 = m4Translate22 * m4Scale;
	matrix4 m4Model23 = m4Translate23 * m4Scale;
	matrix4 m4Model24 = m4Translate24 * m4Scale;
	matrix4 m4Model25 = m4Translate25 * m4Scale;
	matrix4 m4Model26 = m4Translate26 * m4Scale;
	matrix4 m4Model27 = m4Translate27 * m4Scale;
	matrix4 m4Model28 = m4Translate28 * m4Scale;

	matrix4 m4Model29 = m4Translate29 * m4Scale;
	matrix4 m4Model30 = m4Translate30 * m4Scale;

	matrix4 m4Model31 = m4Translate31 * m4Scale;
	matrix4 m4Model32 = m4Translate32 * m4Scale;

	m_pMesh->Render(m4Projection, m4View, m4Model);
	m_pMesh->Render(m4Projection, m4View, m4Model2);
	m_pMesh->Render(m4Projection, m4View, m4Model3);
	m_pMesh->Render(m4Projection, m4View, m4Model4);
	m_pMesh->Render(m4Projection, m4View, m4Model5);
	m_pMesh->Render(m4Projection, m4View, m4Model6);
	m_pMesh->Render(m4Projection, m4View, m4Model7);
	m_pMesh->Render(m4Projection, m4View, m4Model8);
	m_pMesh->Render(m4Projection, m4View, m4Model9);
	m_pMesh->Render(m4Projection, m4View, m4Model10);
	m_pMesh->Render(m4Projection, m4View, m4Model11);
	m_pMesh->Render(m4Projection, m4View, m4Model12);

	m_pMesh->Render(m4Projection, m4View, m4Model13);
	m_pMesh->Render(m4Projection, m4View, m4Model14);
	m_pMesh->Render(m4Projection, m4View, m4Model15);
	m_pMesh->Render(m4Projection, m4View, m4Model16);
	m_pMesh->Render(m4Projection, m4View, m4Model17);
	m_pMesh->Render(m4Projection, m4View, m4Model18);

	m_pMesh->Render(m4Projection, m4View, m4Model19);
	m_pMesh->Render(m4Projection, m4View, m4Model20);
	m_pMesh->Render(m4Projection, m4View, m4Model21);
	m_pMesh->Render(m4Projection, m4View, m4Model22);
	m_pMesh->Render(m4Projection, m4View, m4Model23);
	m_pMesh->Render(m4Projection, m4View, m4Model24);
	m_pMesh->Render(m4Projection, m4View, m4Model25);
	m_pMesh->Render(m4Projection, m4View, m4Model26);
	m_pMesh->Render(m4Projection, m4View, m4Model27);
	m_pMesh->Render(m4Projection, m4View, m4Model28);

	m_pMesh->Render(m4Projection, m4View, m4Model29);
	m_pMesh->Render(m4Projection, m4View, m4Model30);
	m_pMesh->Render(m4Projection, m4View, m4Model31);
	m_pMesh->Render(m4Projection, m4View, m4Model32);
	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();
	
	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	//clear the render list
	m_pMeshMngr->ClearRenderList();
	
	//draw gui
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();

}
void Application::Release(void)
{
	SafeDelete(m_pMesh);

	//release GUI
	ShutdownGUI();
}