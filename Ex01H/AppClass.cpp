/*
* ERRORS: Many "pencils" are rendered instead of one, but still circle around lines & vertices as intended.
* Pencils are not oriented to be perpendicular to whatever face they are on
* Pencil positions do not change when guide cube rotates
* Pencil tips are hard to see because the cylinders obstruct them and they are not oriented to each face
*/
#include "AppClass.h"
using namespace Simplex;
void Application::InitVariables(void)
{
#pragma region DOES NOT NEED CHANGES
	/*
		This part initialize the camera position so I can see the scene better; 
		the guide cube and the tip of the pencil so all solutions on the exam 
		look the same to the grader
	*/
	m_pCameraMngr->SetPositionTargetAndUpward(AXIS_Z * 35.0f, ZERO_V3, AXIS_Y);
		
	m_pGuideCube = new MyMesh();
	m_pGuideCube->GenerateCube(10.0f, C_WHITE);

	m_pMesh = new MyMesh();
	m_pMesh->GenerateCone(1.0f, 2.0f, 8, vector3(0.0f, 0.0f, 0.0f));
#pragma endregion

	//Please change to your name and email
	m_sProgramer = "Ian Davis - icd9008@rit.edu";

	//generating cylinder to match cone
	m_pMesh2 = new MyMesh();
	m_pMesh2->GenerateCylinder(1.0f,1.0f,8,vector3(255.0f,199.0f,0.0f));
}
void Application::Update(void)
{
#pragma region DOES NOT NEED CHANGES
	/*
		This updates the internal clock of the Simplex library and process the Arcball
	*/
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();
#pragma endregion
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();
	matrix4 m4View = m_pCameraMngr->GetViewMatrix();

	//Get a timer
	static uint uClock = m_pSystem->GenClock(); //generate a new clock
	fTimer += m_pSystem->GetDeltaTime(uClock); //get the start time for that clock
	std::vector<vector3>stopsList;
	vector3 v3Start;
	vector3 v3End;
	//creating stops
	for (int i = 0; i < m_pGuideCube->GetVertexList().size(); i++)//length is number of vertices on a cube
	{
		stopsList.push_back(m_pGuideCube->GetVertexList()[i]);
	}
	matrix4 m4Model;
	vector3 v3CurrentPos = ZERO_V3;
	//loop to lerp to each cube vertex
	for (int i = 1; i < stopsList.size(); i++)//i starts at 1 to prevent out of index exceptions
	{
		
		v3Start = stopsList[i-1];
		v3End = stopsList[i];
		float fPercentage = static_cast<float>(MapValue(fTimer, 0.0f, speed, 0.0f, 1.0f));;
		//calculate the current position
		v3CurrentPos = glm::lerp(v3Start, v3End, fPercentage);
		if(fPercentage>1.0f)
			fTimer= m_pSystem->GetDeltaTime(uClock);
		matrix4 m4MVP = m4Projection * m4View*m4Model;
		m4Model = glm::translate(IDENTITY_M4, v3CurrentPos);
		//------------------------------------------------------------------------
		//NOTE: This is the code that generates multiple renders of the same objects.
		//Being in the loop does this but putting this outside the loop only has it
		//travel between the last two vertcies.
		//Tried creating a render list using m_pMeshMngr but wouldn't accept parameters
		//even after examining exact parameters in the header.
		//Does not appear to be any method in MyMesh class to stop the render
		//while also not deleting the whole mesh.
		//Creating my own render list and looping through that has caused similar problems.
		//Leaving this part of the code in to show that at least the objects go to
		//the intended vertices.
		//-------------------------------------------------------------------------
		m_pMesh->Render(m4Projection, m4View, m4Model);
		m_pMesh2->Render(m4Projection, m4View, m4Model);
	}
	
#pragma region DOES NOT NEED CHANGES
	/*
		This part does not need any changes at all, it is just for rendering the guide cube, the 
		skybox as a frame of reference and the gui display
	*/
	//Render the guide cube
	m_pGuideCube->Render(m4Projection, m4View, ToMatrix4(m_qArcBall)); 

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
#pragma endregion
}

void Application::Release(void)
{
	//release GUI
	ShutdownGUI();

	//I already deallocated the memory for the meshes if you allocate new memory please
	//deallocate it before ending the program
	SafeDelete(m_pMesh);
	SafeDelete(m_pMesh2);
	SafeDelete(m_pGuideCube);
}