#include "AppClass.h"
void Application::InitVariables(void)
{
	//Change this to your name and email
	m_sProgrammer = "Ian Davis - icd9008@rit.edu";
	
	//Set the position and target of the camera
	//(I'm at [0,0,10], looking at [0,0,0] and up is the positive Y axis)
	m_pCameraMngr->SetPositionTargetAndUpward(AXIS_Z * 20.0f, ZERO_V3, AXIS_Y);

	//if the light position is zero move it
	if (m_pLightMngr->GetPosition(1) == ZERO_V3)
		m_pLightMngr->SetPosition(vector3(0.0f, 0.0f, 3.0f));

	//if the background is cornflowerblue change it to black (its easier to see)
	if (vector3(m_v4ClearColor) == C_BLUE_CORNFLOWER)
	{
		m_v4ClearColor = vector4(ZERO_V3, 1.0f);
	}
	
	//if there are no segments create 7
	if(m_uOrbits < 1)
		m_uOrbits = 7;

	float fSize = 1.0f; //initial size of orbits

	//creating a color using the spectrum 
	uint uColor = 650; //650 is Red
	//prevent division by 0
	float decrements = 250.0f / (m_uOrbits > 1? static_cast<float>(m_uOrbits - 1) : 1.0f); //decrement until you get to 400 (which is violet)
	/*
		This part will create the orbits, it start at 3 because that is the minimum subdivisions a torus can have
	*/
	uint uSides = 3; //start with the minimal 3 sides
	for (uint i = uSides; i < m_uOrbits + uSides; i++)
	{
		vector3 v3Color = WaveLengthToRGB(uColor); //calculate color based on wavelength
		m_shapeList.push_back(m_pMeshMngr->GenerateTorus(fSize, fSize - 0.1f, 3, i, v3Color)); //generate a custom torus and add it to the meshmanager
		fSize += 0.5f; //increment the size for the next orbit
		uColor -= static_cast<uint>(decrements); //decrease the wavelength
	}
	
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

	matrix4 m4View = m_pCameraMngr->GetViewMatrix(); //view Matrix
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix(); //Projection Matrix
	matrix4 m4Offset = IDENTITY_M4; //offset of the orbits, starts as the global coordinate system
	/*
		The following offset will orient the orbits as in the demo, start without it to make your life easier.
	*/
	//m4Offset = glm::rotate(IDENTITY_M4, 1.5708f, AXIS_Z);

	//Get a timer
	static float fTimer = 0;	//store the new timer
	static uint uClock = m_pSystem->GenClock(); //generate a new clock for that timer
	fTimer += m_pSystem->GetDeltaTime(uClock); //get the delta time for that timer
	vector3 v3Start;
	vector3 v3End;
	float fPercentage = static_cast<float>(MapValue(fTimer, 0.0f, 5.0f, 0.0f, 1.0f));
	std::vector<std::vector<vector3>> stopListList;
	uint uSides = 3;//will be used to help generate stops in each torus
	//variables for generating stops
	float step;
	float sine;
	float cosine;
	static float lerpCounter=0.0f;
	while (stopListList.size() < m_uOrbits)//purpose is to generate stops & list to full before lerp 
	{
		float radCount = 0.0f;//used to increase radius
		//creating stops for each shape
		for (float angle = 0.0f; angle < 2.0f*PI; angle += step)
		{
			step = (2.0f*PI) / (float)uSides;
			cosine = cos(angle);
			sine = sin(angle);
			int radius = 1 + (.5f*radCount);
			vector3 stop = vector3(0 + (cosine*radius), 0 + (sine*radius), 0);
			m_stopsList.push_back(stop);
		}
		uSides++;
		radCount++;
		stopListList.push_back(m_stopsList);
		stopStates.push_back(0);
	}
	// draw a shapes
	for (uint i = 0; i < m_uOrbits; ++i)
	{
		m_pMeshMngr->AddMeshToRenderList(m_shapeList[i], glm::rotate(m4Offset, 1.5708f, AXIS_X));
		//calculating each sphere's position
		vector3 v3CurrentPos = ZERO_V3;
		//reset stop counter
		if (stopStates[i] >= stopListList[i].size())//gets sphere from last point to 1st point
			stopStates[i] = 0;
		else
			stopStates[i]++;
		//LERP each sphere's position
		if (stopStates[i] >= stopListList[i].size())//connects last & 1st point
			v3CurrentPos = glm::lerp(stopListList[i][stopStates[i]], stopListList[i][0], fPercentage);
		else
			v3CurrentPos = glm::lerp(stopListList[i][stopStates[i]], stopListList[i][stopStates[i]], fPercentage);
		//increment lerp counter
		lerpCounter += 0.003f;
		//calculate current position
		matrix4 m4Model = glm::translate(m4Offset, v3CurrentPos);

		//draw spheres
		m_pMeshMngr->AddSphereToRenderList(m4Model * glm::scale(vector3(0.2)), C_WHITE);
	}
	if (lerpCounter > 1.0f)
		lerpCounter = 0.0f;
	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	//clear the render list
	m_pMeshMngr->ClearRenderList();
	
	//draw gui
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
	std::cout << "stopListList.size "<<stopListList.size()<<"\n";
	std::cout << "m_stopsList.size "<<m_stopsList.size() << "\n";
	std::cout << "stopStates.size "<<stopStates.size()<<"\n";
}
void Application::Release(void)
{
	//release GUI
	ShutdownGUI();
}