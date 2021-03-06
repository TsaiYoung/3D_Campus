/*
-----------------------------------------------------------------------------
Filename:    OgreCampus.cpp
-----------------------------------------------------------------------------


This source file is generated by the
   ___                   _              __    __ _                  _ 
  /___\__ _ _ __ ___    /_\  _ __  _ __/ / /\ \ (_)______ _ _ __ __| |
 //  // _` | '__/ _ \  //_\\| '_ \| '_ \ \/  \/ / |_  / _` | '__/ _` |
/ \_// (_| | | |  __/ /  _  \ |_) | |_) \  /\  /| |/ / (_| | | | (_| |
\___/ \__, |_|  \___| \_/ \_/ .__/| .__/ \/  \/ |_/___\__,_|_|  \__,_|
      |___/                 |_|   |_|                                 
      Ogre 1.8.x Application Wizard for VC10 (May 2012)
      https://bitbucket.org/jacmoe/ogreappwizards
-----------------------------------------------------------------------------
*/

#include "OgreCampus.h"

#include "MyGUI.h"
#include "MyGUI_OgrePlatform.h"

#define PI 3.1415926
//-------------------------------------------------------------------------------------
OgreCampus::OgreCampus(void): mRotate(.5),mMove(250),mCamNode(0),mDirection(Ogre::Vector3::ZERO),
	camera_check(1),MapOn(false),CarAngle(0),HeliAngle(0)
{
	mTerrainGroup = NULL;
	mTerrainGlobals = NULL;
}
//-------------------------------------------------------------------------------------
OgreCampus::~OgreCampus(void)
{
	if (mTerrainGroup)
	{
		OGRE_DELETE mTerrainGroup;
	}

	if (mTerrainGlobals)
	{
		OGRE_DELETE mTerrainGlobals;
	}

}

//-------------------------------------------------------------------------------------

void OgreCampus::createCamera()
{
	//mCamera = mSceneMgr->createCamera("myCam");
	//mCamera->setPosition(0, 300, 500);
	//mCamera->lookAt(0,0,0);
	//mCamera->setNearClipDistance(5);

	//bool infiniteClip = mRoot->getRenderSystem()->getCapabilities()->hasCapability(Ogre::RSC_INFINITE_FAR_PLANE);
	//if (infiniteClip)		//如果相机距离支持无限大就设置为无限距离
	//	mCamera->setFarClipDistance(0);
	//else 
	//	mCamera->setFarClipDistance(50000);

	//mCameraMan = new OgreBites::SdkCameraMan(mCamera);
}

void OgreCampus::createViewports()
{
	//Ogre::Viewport* vp = mWindow->addViewport(mCamera);		//create a Viewport for our scene
	//vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));		//set the background color of the Viewport
	//mCamera->setAspectRatio( Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()) );	// set the aspect ratio of our Camera
}

void OgreCampus::createScene(void)
{

	//ogre 初始化资源组 resource group
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	//相机
	mCamera = mSceneMgr->createCamera("myCam");
	//mCamera->setPosition(0, 300, 500);
	//mCamera->lookAt(5000,0,5000);
	mCamera->setNearClipDistance(5);
	mCameraMan = new OgreBites::SdkCameraMan(mCamera);

	//视口
	Ogre::Viewport* vp = mWindow->addViewport(mCamera);		//create a Viewport for our scene
	vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));	//set the background color of the Viewport
	mCamera->setAspectRatio( Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()) );	// set the aspect ratio of our Camera


	//视角位置
	Ogre::SceneNode* node = mSceneMgr->getRootSceneNode()->createChildSceneNode("CamNode1", Ogre::Vector3(-300, 1000, 300));
	node->yaw( Ogre::Degree(-45) );

	mCamNode = node;
	node->attachObject(mCamera);

	node = mSceneMgr->getRootSceneNode()->createChildSceneNode(	"CamNode2", Ogre::Vector3(13000, 1000, 0));
	node->yaw( Ogre::Degree(45) );

	node = mSceneMgr->getRootSceneNode()->createChildSceneNode(	"CamNode3", Ogre::Vector3(13000, 1000, -13000));
	node->yaw( Ogre::Degree(135) );

	node = mSceneMgr->getRootSceneNode()->createChildSceneNode(	"CamNode4", Ogre::Vector3(0, 1000, -13000));
	node->yaw( Ogre::Degree(225) );

	/*天空*/
	mSceneMgr->setSkyDome(true,"Examples/CloudySky", 5, 2);

	//平面
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);

	Ogre::MeshManager::getSingleton().createPlane("ground",Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,plane, 30000, 30000, 30, 30,true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
	Ogre::Entity*entGround =mSceneMgr->createEntity("ground");
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entGround);
	entGround->setMaterialName("Examples/Cement");
	entGround->setCastShadows(false);
	
	/*Ogre::Entity* jtq = mSceneMgr->createEntity("jtq.mesh");
	jtq->setCastShadows(true);
	Ogre::SceneNode* nodeJTQ = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	nodeJTQ->setPosition(0,0,0);
	nodeJTQ->attachObject(jtq);

	Ogre::Entity* tsg = mSceneMgr->createEntity("tsg.mesh");
	tsg->setCastShadows(true);
	Ogre::SceneNode* nodeTSG = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	nodeTSG->setPosition(0,0,0);
	nodeTSG->attachObject(tsg);*/

	//校园
	Ogre::Entity* campus = mSceneMgr->createEntity("campus.mesh");
	campus->setCastShadows(true);
	Ogre::SceneNode* nodeCampus = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	nodeCampus->setPosition(0,0,0);
	nodeCampus->attachObject(campus);

	//草地
	Ogre::Entity* grass = mSceneMgr->createEntity("grass.mesh");
	grass->setCastShadows(true);
	grass->setMaterialName("Vegetati");
	grass->setMaterialName("_Vegetat");
	//grass->setMaterialName("BackColo");
	//grass->setMaterialName("FrontCol");
	Ogre::SceneNode* nodeGrass = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	nodeGrass->setPosition(0,0,0);
	nodeGrass->attachObject(grass);

	//汽车
	Ogre::Entity* car = mSceneMgr->createEntity("car.mesh");
	car->setCastShadows(true);
	car->setMaterialName("Black");
	car->setMaterialName("Chrome");
	car->setMaterialName("Chrome1");
	car->setMaterialName("Chrome2");
	car->setMaterialName("Dettop");
	car->setMaterialName("Glass1");
	car->setMaterialName("Glases");
	car->setMaterialName("Licenpla");
	car->setMaterialName("Pirina");
	car->setMaterialName("Pirina2");
	car->setMaterialName("Red");
	car->setMaterialName("Wheel");
	car->setMaterialName("White");
	car->setMaterialName("Yellow");
	Ogre::SceneNode* nodeCar = mSceneMgr->getRootSceneNode()->createChildSceneNode("nodeCar");
	nodeCar->pitch( Ogre::Degree(0));
	nodeCar->setPosition(0,50,0);
	nodeCar->attachObject(car);

	//直升飞机
	Ogre::Entity* helicopter = mSceneMgr->createEntity("helicopter.mesh");
	helicopter->setCastShadows(true);
	helicopter->setMaterialName("Foregrou");
	helicopter->setMaterialName("orig_02-Default");
	Ogre::SceneNode* nodeHelic = mSceneMgr->getRootSceneNode()->createChildSceneNode("nodeHelic");
	nodeHelic->setPosition(300,50,300);
	nodeHelic->attachObject(helicopter);

	/*光源*/
	Ogre::Light*light1 =mSceneMgr->createLight("Light1");
	light1->setType(Ogre::Light:: LT_DIRECTIONAL);				//定向光源；LT_POINT点光源；LT_SPOTLIGHT聚光源
	light1->setDirection(Ogre::Vector3(1,-1,0));
	light1->setDiffuseColour(Ogre::ColourValue(1.0f,1.0f,1.0f));	//漫反射颜色
	light1->setSpecularColour(1,1,1);

	Ogre::Light*light2 =mSceneMgr->createLight("Light2");
	light2->setType(Ogre::Light:: LT_DIRECTIONAL);			
	light2->setDirection(Ogre::Vector3(-1,1,0));
	light2->setDiffuseColour(Ogre::ColourValue(1.0f,1.0f,1.0f));	
	light2->setSpecularColour(1.0,1.0,1.0);

	mSceneMgr->setAmbientLight(Ogre::ColourValue(0, 0, 0));
	mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

	//MyGUI---在你初始化 GUI前，确定创建了 一个视口 viewport
	//在ogre 初始化它的资源组 resource group后再初始化 MyGUI
	mPlatform = new MyGUI::OgrePlatform();
	mPlatform->initialise(mWindow,mSceneMgr);

	mGUI = new MyGUI::Gui();
	mGUI->initialise();

	//添加button按钮
	MyGUI::Button* ButtonUp = mGUI->createWidget<MyGUI::Button>("ButtonUpSkin", 40, 0, 60, 50, MyGUI::Align::Default, "Main");
	ButtonUp->eventMouseButtonClick += MyGUI::newDelegate(this,&OgreCampus::MouseButtonClick_Up);
	
	MyGUI::Button* ButtonDown = mGUI->createWidget<MyGUI::Button>("ButtonDownSkin", 40, 90, 60, 50, MyGUI::Align::Default, "Main");
	ButtonDown->eventMouseButtonClick += MyGUI::newDelegate(this,&OgreCampus::MouseButtonClick_Down);

	MyGUI::Button* ButtonLeft = mGUI->createWidget<MyGUI::Button>("ButtonLeftSkin", 0, 40, 50, 60, MyGUI::Align::Default, "Main");
	ButtonLeft->eventMouseButtonClick += MyGUI::newDelegate(this,&OgreCampus::MouseButtonClick_Left);

	MyGUI::Button* ButtonRight = mGUI->createWidget<MyGUI::Button>("ButtonRightSkin", 90, 40, 50, 60, MyGUI::Align::Default, "Main");
	ButtonRight->eventMouseButtonClick += MyGUI::newDelegate(this,&OgreCampus::MouseButtonClick_Right);

	MyGUI::Button* butCam1 = mGUI->createWidget<MyGUI::Button>("Button", 210, 0, 50, 50, MyGUI::Align::Default, "Main");
	MyGUI::ImageBox* imgCam1 = butCam1->createWidget<MyGUI::ImageBox>("ImageBox", 0, 0, 50, 50, MyGUI::Align::Default, "Main");
	imgCam1->setImageTexture("camera1.png");
	imgCam1->eventMouseButtonClick += MyGUI::newDelegate(this,&OgreCampus::MouseButtonClickCamera1);

	MyGUI::Button* butCam2 = mGUI->createWidget<MyGUI::Button>("Button", 280, 0, 50, 50, MyGUI::Align::Default, "Main");
	MyGUI::ImageBox* imgCam2 = butCam2->createWidget<MyGUI::ImageBox>("ImageBox", 0, 0, 50, 50, MyGUI::Align::Default, "Main");
	imgCam2->setImageTexture("camera2.png");
	imgCam2->eventMouseButtonClick += MyGUI::newDelegate(this,&OgreCampus::MouseButtonClickCamera2);

	MyGUI::Button* butCam3 = mGUI->createWidget<MyGUI::Button>("Button", 350, 0, 50, 50, MyGUI::Align::Default, "Main");
	MyGUI::ImageBox* imgCam3 = butCam3->createWidget<MyGUI::ImageBox>("ImageBox", 0, 0, 50, 50, MyGUI::Align::Default, "Main");
	imgCam3->setImageTexture("camera3.png");
	imgCam3->eventMouseButtonClick += MyGUI::newDelegate(this,&OgreCampus::MouseButtonClickCamera3);

	MyGUI::Button* butCam4 = mGUI->createWidget<MyGUI::Button>("Button", 420, 0, 50, 50, MyGUI::Align::Default, "Main");
	MyGUI::ImageBox* imgCam4 = butCam4->createWidget<MyGUI::ImageBox>("ImageBox", 0, 0, 50, 50, MyGUI::Align::Default, "Main");
	imgCam4->setImageTexture("camera4.png");
	imgCam4->eventMouseButtonClick += MyGUI::newDelegate(this,&OgreCampus::MouseButtonClickCamera4);

	MyGUI::Button* butCar= mGUI->createWidget<MyGUI::Button>("Button", 490, 0, 50, 50, MyGUI::Align::Default, "Main");
	MyGUI::ImageBox* imgCar = butCar->createWidget<MyGUI::ImageBox>("ImageBox", 0, 0, 50, 50, MyGUI::Align::Default, "Main");
	imgCar->setImageTexture("car.png");
	imgCar->eventMouseButtonClick += MyGUI::newDelegate(this,&OgreCampus::MouseButtonClickCar);

	MyGUI::Button* butHeli= mGUI->createWidget<MyGUI::Button>("Button", 560, 0, 50, 50, MyGUI::Align::Default, "Main");
	MyGUI::ImageBox* imgHeli = butHeli->createWidget<MyGUI::ImageBox>("ImageBox", 0, 0, 50, 50, MyGUI::Align::Default, "Main");
	imgHeli->setImageTexture("helicopter.png");
	imgHeli->eventMouseButtonClick += MyGUI::newDelegate(this,&OgreCampus::MouseButtonClickHelicopter);

	MyGUI::Button* butMap= mGUI->createWidget<MyGUI::Button>("Button", 630, 0, 50, 50, MyGUI::Align::Default, "Main");
	MyGUI::ImageBox* ButImgMap = butMap->createWidget<MyGUI::ImageBox>("ImageBox", 0, 0, 50, 50, MyGUI::Align::Default, "Main");
	ButImgMap->setImageTexture("butMap.png");
	ButImgMap->eventMouseButtonClick += MyGUI::newDelegate(this,&OgreCampus::MouseButtonClickMap);

	imgMap = mGUI->createWidget<MyGUI::ImageBox>("ImageBox",770, 0, 240, 240, MyGUI::Align::Default, "Main");
	imgMap->setVisible(false);
	CarPos = imgMap->createWidget<MyGUI::Button>("ButtonCloseSkin", 25, 215, 10, 10, MyGUI::Align::Default, "Main");
	CarPos->setColour(MyGUI::Colour(0.982456,0,0));
	CarPos->setVisible(false);
	HeliPos = imgMap->createWidget<MyGUI::Button>("ButtonCloseSkin", 30, 220, 10, 10, MyGUI::Align::Default, "Main");
	HeliPos->setColour(MyGUI::Colour(0.982456,0,0));
	HeliPos->setVisible(false);

	/*地形*/
	////设置相机
	//mCamera->setPosition(Ogre::Vector3(1683, 50, 2116));
	//mCamera->lookAt(Ogre::Vector3(1963, 50, 1660));
	//mCamera->setNearClipDistance(0.1);
	//bool infiniteClip = mRoot->getRenderSystem()->getCapabilities()->hasCapability(Ogre::RSC_INFINITE_FAR_PLANE);
	//if (infiniteClip)		//如果相机距离支持无限大就设置为无线距离
	//	mCamera->setFarClipDistance(0);
	//else 
	//	mCamera->setFarClipDistance(50000);

	////Ogre::MaterialManager::getSingleton().setDefaultTextureFiltering(Ogre::TFO_ANISOTROPIC);//设置材质的一些属性，这里是设置默认的各向异性值
	////Ogre::MaterialManager::getSingleton().setDefaultAnisotropy(7);


	//mSceneMgr->setAmbientLight(Ogre::ColourValue(0.2, 0.2, 0.2));

	//Ogre::Vector3 lightdir(0.55, -0.3, 0.75); //光线方向
	//lightdir.normalise();

	//Ogre::Light* light = mSceneMgr->createLight("TestLight");
	//light->setType(Ogre::Light::LT_DIRECTIONAL);
	//light->setDirection(lightdir);
	//light->setDiffuseColour(Ogre::ColourValue::White);				//漫反射光
	////light->setSpecularColour(Ogre::ColourValue(0.4, 0.4, 0.4));		//镜面反射光

	//mTerrainGlobals = OGRE_NEW Ogre::TerrainGlobalOptions();		//a class that holds information for all of the terrains we might create
	//mTerrainGroup = OGRE_NEW Ogre::TerrainGroup(mSceneMgr, Ogre::Terrain::ALIGN_X_Z, 513, 12000.0);	// parameters:SceneManager,alignment option, terrain size, and terrain world size
	//mTerrainGroup->setFilenameConvention(Ogre::String("terrain"), Ogre::String("dat"));				//allows us to choose how our terrain will be saved
	//mTerrainGroup->setOrigin(Ogre::Vector3::ZERO);					//set the origin(起点) to be used for our terrain

	//configureTerrainDefaults(light);		//组合地形

	//for (long x = 0; x <= 0; ++x)
	//	for (long y = 0; y <= 0; ++y)
	//		defineTerrain(x, y);	//define our terrains and ask the TerrainGroup to load them all

	//mTerrainGroup->loadAllTerrains(true);	//加载地形

	////初始化混合地形的地图
	//if (mTerrainsImported)//是否导入地形
	//{
	//	Ogre::TerrainGroup::TerrainIterator ti = mTerrainGroup->getTerrainIterator();

	//	while (ti.hasMoreElements())
	//	{
	//		Ogre::Terrain* t = ti.getNext()->instance;
	//		initBlendMaps(t);//初始化
	//	}
	//}
	//mTerrainGroup->freeTemporaryResources();	//free临时资源

	//Listener
	

}

void OgreCampus::Overview(int Move, int* X, int* Y)
{
	if (camera_check == 5)
	{
		float sinA = sin(CarAngle*PI/180);
		float cosA = cos(CarAngle*PI/180);

		if (sinA >= 0)
			*X = int( (240.0/60000.0*Move) * sin(CarAngle*PI/180) + 0.5);	//当角度小于等于180度，加0.5：四舍五入
		else
			*X = int( (240.0/60000.0*Move) * sin(CarAngle*PI/180) - 0.5);	//当角度大于180度，减0.5：四舍五入

		if (cosA >= 0)
			*Y = int( (240.0/48500.0*Move) * cos(CarAngle*PI/180) + 0.5);
		else	
			*Y = int( (240.0/48500.0*Move) * cos(CarAngle*PI/180) - 0.5);
	}
	if (camera_check == 6)
	{
		float sinA = sin(HeliAngle*PI/180);
		float cosA = cos(HeliAngle*PI/180);

		if (sinA >= 0)
			*X = int( (240.0/60000.0*Move) * sin(HeliAngle*PI/180) + 0.5);	//当角度小于等于180度，加0.5：四舍五入
		else
			*X = int( (240.0/60000.0*Move) * sin(HeliAngle*PI/180) - 0.5);	//当角度大于180度，减0.5：四舍五入

		if (cosA >= 0)
			*Y = int( (240.0/48500.0*Move) * cos(HeliAngle*PI/180) + 0.5);
		else	
			*Y = int( (240.0/48500.0*Move) * cos(HeliAngle*PI/180) - 0.5);
	}
}

void OgreCampus::MouseButtonClickCamera1(MyGUI::WidgetPtr _sender)
{
	mCamera->getParentSceneNode()->detachObject(mCamera);
	mCamNode = mSceneMgr->getSceneNode("CamNode1");
	mCamNode->attachObject(mCamera);

	camera_check =1;

	if (MapOn)
	{
		imgMap->setImageTexture("map1.png");
	}
}

void OgreCampus::MouseButtonClickCamera2(MyGUI::Widget* _sender)
{
	mCamera->getParentSceneNode()->detachObject(mCamera);
	mCamNode = mSceneMgr->getSceneNode("CamNode2");
	mCamNode->attachObject(mCamera);

	camera_check = 2;

	if (MapOn)
	{
		imgMap->setImageTexture("map2.png");
	}
}

void OgreCampus::MouseButtonClickCamera3(MyGUI::Widget* _sender)
{
	mCamera->getParentSceneNode()->detachObject(mCamera);
	mCamNode = mSceneMgr->getSceneNode("CamNode3");
	mCamNode->attachObject(mCamera);

	camera_check = 3;

	if (MapOn)
	{
		imgMap->setImageTexture("map3.png");
	}
}

void OgreCampus::MouseButtonClickCamera4(MyGUI::Widget* _sender)
{
	mCamera->getParentSceneNode()->detachObject(mCamera);
	mCamNode = mSceneMgr->getSceneNode("CamNode4");
	mCamNode->attachObject(mCamera);

	camera_check = 4;

	if (MapOn)
	{
		imgMap->setImageTexture("map4.png");
	}
}

void OgreCampus::MouseButtonClickCar(MyGUI::Widget* _sender)
{
	camera_check = 5;

	mCamera->getParentSceneNode()->detachObject(mCamera);
	mCamNode = mSceneMgr->getSceneNode("nodeCar");
	mCamNode->attachObject(mCamera);

	if (MapOn)
	{
		imgMap->setImageTexture("map.png");
		CarPos->setVisible(true);
		HeliPos->setVisible(false);
	}
}

void OgreCampus::MouseButtonClickHelicopter(MyGUI::Widget* _sender)
{
	camera_check = 6;

	mCamera->getParentSceneNode()->detachObject(mCamera);
	mCamNode = mSceneMgr->getSceneNode("nodeHelic");
	mCamNode->attachObject(mCamera);

	if (MapOn)
	{
		imgMap->setImageTexture("map.png");
		CarPos->setVisible(false);
		HeliPos->setVisible(true);
	}
}

void OgreCampus::MouseButtonClick_Up(MyGUI::Widget* _sender)
{
	if (camera_check == 6)
	{
		mSceneMgr->getSceneNode("nodeHelic")->pitch(Ogre::Degree(30 * mRotate));
	}
	if (camera_check == 1)
	{
		mSceneMgr->getSceneNode("CamNode1")->pitch(Ogre::Degree(30 * mRotate));
	}
	if (camera_check == 2)
	{
		mSceneMgr->getSceneNode("CamNode2")->pitch(Ogre::Degree(30 * mRotate));
	}
	if (camera_check == 3)
	{
		mSceneMgr->getSceneNode("CamNode3")->pitch(Ogre::Degree(30 * mRotate));
	}
	if (camera_check == 4)
	{
		mSceneMgr->getSceneNode("CamNode4")->pitch(Ogre::Degree(30 * mRotate));
	}
}

void OgreCampus::MouseButtonClick_Down(MyGUI::Widget* _sender)
{
	if (camera_check == 6)
	{
		mSceneMgr->getSceneNode("nodeHelic")->pitch(Ogre::Degree(-30 * mRotate));
	}
	if (camera_check == 1)
	{
		mSceneMgr->getSceneNode("CamNode1")->pitch(Ogre::Degree(-30 * mRotate));
	}
	if (camera_check == 2)
	{
		mSceneMgr->getSceneNode("CamNode2")->pitch(Ogre::Degree(-30 * mRotate));
	}
	if (camera_check == 3)
	{
		mSceneMgr->getSceneNode("CamNode3")->pitch(Ogre::Degree(-30 * mRotate));
	}
	if (camera_check == 4)
	{
		mSceneMgr->getSceneNode("CamNode4")->pitch(Ogre::Degree(-30 * mRotate));
	}
}

void OgreCampus::MouseButtonClick_Left(MyGUI::Widget* _sender)
{
	if (camera_check == 5)
	{
		mSceneMgr->getSceneNode("nodeCar")->yaw(Ogre::Degree(30 * mRotate));
		CarAngle = CarAngle - (30 * mRotate);
	}
	if (camera_check == 6)
	{
		mSceneMgr->getSceneNode("nodeHelic")->yaw(Ogre::Degree(30 * mRotate));
		HeliAngle = HeliAngle - (30 * mRotate);
	}
	if (camera_check == 1)
	{
		mSceneMgr->getSceneNode("CamNode1")->yaw(Ogre::Degree(30 * mRotate));
	}
	if (camera_check == 2)
	{
		mSceneMgr->getSceneNode("CamNode2")->yaw(Ogre::Degree(30 * mRotate));
	}
	if (camera_check == 3)
	{
		mSceneMgr->getSceneNode("CamNode3")->yaw(Ogre::Degree(30 * mRotate));
	}
	if (camera_check == 4)
	{
		mSceneMgr->getSceneNode("CamNode4")->yaw(Ogre::Degree(30 * mRotate));
	}
}

void OgreCampus::MouseButtonClick_Right(MyGUI::Widget* _sender)
{
	if (camera_check == 5)
	{
		mSceneMgr->getSceneNode("nodeCar")->yaw(Ogre::Degree(-30 * mRotate));
		CarAngle = CarAngle + (30 * mRotate);;
	}
	if (camera_check == 6)
	{
		mSceneMgr->getSceneNode("nodeHelic")->yaw(Ogre::Degree(-30 * mRotate));
		HeliAngle = HeliAngle + (30 * mRotate);
	}
	if (camera_check == 1)
	{
		mSceneMgr->getSceneNode("CamNode1")->yaw(Ogre::Degree(-30 * mRotate));
	}
	if (camera_check == 2)
	{
		mSceneMgr->getSceneNode("CamNode2")->yaw(Ogre::Degree(-30 * mRotate));
	}
	if (camera_check == 3)
	{
		mSceneMgr->getSceneNode("CamNode3")->yaw(Ogre::Degree(-30 * mRotate));
	}
	if (camera_check == 4)
	{
		mSceneMgr->getSceneNode("CamNode4")->yaw(Ogre::Degree(-30 * mRotate));
	}
}

void OgreCampus::MouseButtonClickMap(MyGUI::Widget* _sender)
{
	if (!MapOn)
	{
		imgMap->setVisible(true);

		if (camera_check == 1)
		{
			imgMap->setImageTexture("map1.png");
			CarPos->setVisible(false);
			HeliPos->setVisible(false);
		}

		if (camera_check == 2)
		{
			imgMap->setImageTexture("map2.png");
			CarPos->setVisible(false);
			HeliPos->setVisible(false);
		}

		if (camera_check == 3)
		{
			imgMap->setImageTexture("map3.png");
			CarPos->setVisible(false);
			HeliPos->setVisible(false);
		}

		if (camera_check == 4)
		{
			imgMap->setImageTexture("map4.png");
			CarPos->setVisible(false);
			HeliPos->setVisible(false);
		}

		if (camera_check == 5)
		{
			imgMap->setImageTexture("map.png");
			CarPos->setVisible(true);
			HeliPos->setVisible(false);
		}

		if (camera_check == 6)
		{
			imgMap->setImageTexture("map.png");
			CarPos->setVisible(false);
			HeliPos->setVisible(true);
		}

		MapOn = true;
	}
	else
	{
		imgMap->setVisible(false);	//隐藏地图

		MapOn = false;
	}
}

bool OgreCampus::frameRenderingQueued(const Ogre::FrameEvent& fe)
{
	Ogre::Real move = 100;
	static Ogre::Real toggleTimer = 0.0;	// to set how long the system waits before toggling(切换) the light again

	int a = 0;
	int b = 0;
	int *delteX = &a;	//每一帧，鹰眼地图X轴方向的位移量
	int *delteY = &b;	//每一帧，鹰眼地图Y轴方向的位移量

	bool ret = BaseApplication::frameRenderingQueued(fe);

	//makes sure that we only continue running the application if the input is processed successfully
	if(!processUnbufferedInput(fe))
		return false;

	////碰撞检测
	Vector3 result_ = Ogre::Vector3(0,0,0);
	ulong target_ = 0;
	float closest_distance_ = 0;

	Vector3 point = mCamNode->getPosition();
	Vector3 &result = result_;
	ulong &target = target_;
	float &closest_distance = closest_distance_;
	const uint32 queryMask = 1 << 0;

	MOC::CollisionTools *mCollisionTools = new MOC::CollisionTools(mSceneMgr);

	/*移动模型——汽车Car*/
	// WASD keys are used for the Camera
	//IJKL for move,UO for rotate
	
	Ogre::Vector3 dirVec = Ogre::Vector3::ZERO;	// create a vector to hold the direction we want to move the model

	//汽车移动
	if(camera_check == 5)
	{
		if (mKeyboard->isKeyDown(OIS::KC_I))
		{
			Vector3 normal_ = Ogre::Vector3::NEGATIVE_UNIT_Z;
			Vector3 &normal = normal_;

			bool isColli;
			isColli = mCollisionTools->raycastFromPoint( mCamNode->getPosition(), normal, result, target, closest_distance, queryMask);

			if (!isColli)
			{
				if(mKeyboard->isKeyDown(OIS::KC_LSHIFT))
					move = 400;

				dirVec.z -= move;
				Overview(move, delteX, delteY);
				CarPos->setPosition(CarPos->getLeft()+*delteX, CarPos->getTop()-*delteY);
			}
		}

		if (mKeyboard->isKeyDown(OIS::KC_K))
		{
			Vector3 normal_ = Ogre::Vector3::UNIT_Z;
			Vector3 &normal = normal_;

			bool isColli;
			isColli = mCollisionTools->raycastFromPoint( mCamNode->getPosition(), normal, result, target, closest_distance, queryMask);

			if (!isColli)
			{
				if(mKeyboard->isKeyDown(OIS::KC_LSHIFT))
					move = 400;

				dirVec.z += move;
				Overview(move, delteX, delteY);
				CarPos->setPosition(CarPos->getLeft()-*delteX, CarPos->getTop()+*delteY);
			}
		}

		if (mKeyboard->isKeyDown(OIS::KC_J))
		{    
			if(mKeyboard->isKeyDown(OIS::KC_LSHIFT))
			{
				mSceneMgr->getSceneNode("nodeCar")->yaw(Ogre::Degree(5 * mRotate));
				CarAngle = CarAngle - (5 * mRotate);
			}
			else
			{
				Vector3 normal_ = Ogre::Vector3::NEGATIVE_UNIT_X;
				Vector3 &normal = normal_;

				bool isColli;
				isColli = mCollisionTools->raycastFromPoint( mCamNode->getPosition(), normal, result, target, closest_distance, queryMask);

				if (!isColli)
				{
					dirVec.x -= move;
					Overview(move, delteX, delteY);
					CarPos->setPosition(CarPos->getLeft()-*delteY, CarPos->getTop()-*delteX);
				}
			}
		}

		if (mKeyboard->isKeyDown(OIS::KC_L))
		{
			if(mKeyboard->isKeyDown(OIS::KC_LSHIFT))
			{
				mSceneMgr->getSceneNode("nodeCar")->yaw(Ogre::Degree(-5 * mRotate));
				CarAngle = CarAngle + (5 * mRotate);
			}
			else
			{
				Vector3 normal_ = Ogre::Vector3::UNIT_X;
				Vector3 &normal = normal_;

				bool isColli;
				isColli = mCollisionTools->raycastFromPoint( mCamNode->getPosition(), normal, result, target, closest_distance, queryMask);

				if (!isColli)
				{
					dirVec.x += move;
					Overview(move, delteX, delteY);
					CarPos->setPosition(CarPos->getLeft()+*delteY, CarPos->getTop()+*delteX);
				}
			}
		}

		mSceneMgr->getSceneNode("nodeCar")->translate( dirVec * fe.timeSinceLastFrame, Ogre::Node::TS_LOCAL );
	}

	//飞机移动
	if(camera_check == 6)
	{
		if (mKeyboard->isKeyDown(OIS::KC_I))
		{
			Vector3 normal_ = Ogre::Vector3::NEGATIVE_UNIT_Z;
			Vector3 &normal = normal_;

			bool isColli;
			isColli = mCollisionTools->raycastFromPoint( mCamNode->getPosition(), normal, result, target, closest_distance, queryMask);

			if (!isColli)
			{
				if(mKeyboard->isKeyDown(OIS::KC_LSHIFT))
					move = 400;

				dirVec.z -= move;
				Overview(move, delteX, delteY);
				HeliPos->setPosition(HeliPos->getLeft()+*delteX, HeliPos->getTop()-*delteY);
			}
		}

		if (mKeyboard->isKeyDown(OIS::KC_K))
		{
			Vector3 normal_ = Ogre::Vector3::UNIT_Z;
			Vector3 &normal = normal_;

			bool isColli;
			isColli = mCollisionTools->raycastFromPoint( mCamNode->getPosition(), normal, result, target, closest_distance, queryMask);

			if (!isColli)
			{
				if(mKeyboard->isKeyDown(OIS::KC_LSHIFT))
					move = 400;

				dirVec.z += move;
				Overview(move, delteX, delteY);
				HeliPos->setPosition(HeliPos->getLeft()-*delteX, HeliPos->getTop()+*delteY);
			}
		}

		if (mKeyboard->isKeyDown(OIS::KC_U))
		{
			if(mKeyboard->isKeyDown(OIS::KC_LSHIFT))
				move = 400;

			dirVec.y -= move;
		}

		if (mKeyboard->isKeyDown(OIS::KC_O))
		{
			if(mKeyboard->isKeyDown(OIS::KC_LSHIFT))
				move = 400;

			dirVec.y += move;
		}

		if (mKeyboard->isKeyDown(OIS::KC_J))
		{    
			if(mKeyboard->isKeyDown(OIS::KC_LSHIFT))
			{
				mSceneMgr->getSceneNode("nodeHelic")->yaw(Ogre::Degree(5 * mRotate));
				HeliAngle = HeliAngle - (5 * mRotate);
			}
			else
			{
				Vector3 normal_ = Ogre::Vector3::NEGATIVE_UNIT_X;
				Vector3 &normal = normal_;

				bool isColli;
				isColli = mCollisionTools->raycastFromPoint( mCamNode->getPosition(), normal, result, target, closest_distance, queryMask);

				if (!isColli)
				{
					dirVec.x -= move;
					Overview(move, delteX, delteY);
					HeliPos->setPosition(HeliPos->getLeft()-*delteY, HeliPos->getTop()-*delteX);
				}
			}
		}

		if (mKeyboard->isKeyDown(OIS::KC_L))
		{
			if(mKeyboard->isKeyDown(OIS::KC_LSHIFT))
			{
				mSceneMgr->getSceneNode("nodeHelic")->yaw(Ogre::Degree(-5 * mRotate));
				HeliAngle = HeliAngle + (5 * mRotate);
			}
			else
			{
				Vector3 normal_ = Ogre::Vector3::UNIT_X;
				Vector3 &normal = normal_;

				bool isColli;
				isColli = mCollisionTools->raycastFromPoint( mCamNode->getPosition(), normal, result, target, closest_distance, queryMask);

				if (!isColli)
				{
					dirVec.x += move;
					Overview(move, delteX, delteY);
					HeliPos->setPosition(HeliPos->getLeft()+*delteY, HeliPos->getTop()+*delteX);
				}
			}
		}

		mSceneMgr->getSceneNode("nodeHelic")->translate( dirVec * fe.timeSinceLastFrame, Ogre::Node::TS_LOCAL );

	}

	mCamNode->translate(mDirection * fe.timeSinceLastFrame, Ogre::Node::TS_LOCAL);


	//防止摄像机进入地面以下
	if (mCamNode->getPosition().y < 0)
	{
		mCamNode->setPosition( mCamNode->getPosition().x, 10, mCamNode->getPosition().z );
	}

	return ret;
}

bool OgreCampus::processUnbufferedInput(const Ogre::FrameEvent& fe)
{
	static bool mouseDownLastFrame = false;	// to keep track of whether the left mouse button was held down during the last frame
	
	/*鼠标点击切换灯光*/
	//bool leftMouseDown = mMouse->getMouseState().buttonDown(OIS::MB_Left);	//be true whenever the left mouse was held down during the last frame
	//if (leftMouseDown && !mouseDownLastFrame)
	//{
	//	Ogre::Light* light = mSceneMgr->getLight("PointLight");
	//	light->setVisible(!light->isVisible());
	//}
	//mouseDownLastFrame = leftMouseDown;

	return true;
}

//键盘
bool OgreCampus::keyPressed(const OIS::KeyEvent& ke) 
{ 

	//视角位置
	if(ke.key == OIS::KC_1)
	{
		camera_check = 1;

		if (MapOn)
		{
			imgMap->setImageTexture("map1.png");
			CarPos->setVisible(false);
			HeliPos->setVisible(false);
		}
	}

	if(ke.key == OIS::KC_2)
	{
		camera_check = 2;

		if (MapOn)
		{
			imgMap->setImageTexture("map2.png");
			CarPos->setVisible(false);
			HeliPos->setVisible(false);
		}
	}

	if(ke.key == OIS::KC_3)
	{
		camera_check = 3;

		if (MapOn)
		{
			imgMap->setImageTexture("map3.png");
			CarPos->setVisible(false);
			HeliPos->setVisible(false);
		}
	}

	if(ke.key == OIS::KC_4)
	{
		camera_check = 4;

		if (MapOn)
		{
			imgMap->setImageTexture("map4.png");
			CarPos->setVisible(false);
			HeliPos->setVisible(false);
		}
	}

	if(ke.key == OIS::KC_5)
	{
		camera_check = 5;

		if (MapOn)
		{
			imgMap->setImageTexture("map.png");
			CarPos->setVisible(true);
			HeliPos->setVisible(false);
		}
	}

	if(ke.key == OIS::KC_6)
	{
		camera_check = 6;

		if (MapOn)
		{
			imgMap->setImageTexture("map.png");
			CarPos->setVisible(false);
			HeliPos->setVisible(true);
		}
	}

	if(ke.key == OIS::KC_7)
	{
		if (!MapOn)
		{
			imgMap->setVisible(true);

			if (camera_check == 1)
			{
				imgMap->setImageTexture("map1.png");
				CarPos->setVisible(false);
				HeliPos->setVisible(false);
			}

			if (camera_check == 2)
			{
				imgMap->setImageTexture("map2.png");
				CarPos->setVisible(false);
				HeliPos->setVisible(false);
			}

			if (camera_check == 3)
			{
				imgMap->setImageTexture("map3.png");
				CarPos->setVisible(false);
				HeliPos->setVisible(false);
			}

			if (camera_check == 4)
			{
				imgMap->setImageTexture("map4.png");
				CarPos->setVisible(false);
				HeliPos->setVisible(false);
			}

			if (camera_check == 5)
			{
				imgMap->setImageTexture("map.png");
				CarPos->setVisible(true);
				HeliPos->setVisible(false);
			}

			if (camera_check == 6)
			{
				imgMap->setImageTexture("map.png");
				CarPos->setVisible(false);
				HeliPos->setVisible(true);
			}

			MapOn = true;
		}
		else
		{
			imgMap->setVisible(false);	//隐藏地图

			MapOn = false;
		}
	}

	switch (ke.key)
	{
	//退出
	case OIS::KC_ESCAPE: 
		mShutDown = true;
		break;
	//视角1
	case OIS::KC_1:
		mCamera->getParentSceneNode()->detachObject(mCamera);
		mCamNode = mSceneMgr->getSceneNode("CamNode1");
		mCamNode->attachObject(mCamera);
		break;
	
	//视角2
	case OIS::KC_2:
		mCamera->getParentSceneNode()->detachObject(mCamera);
		mCamNode = mSceneMgr->getSceneNode("CamNode2");
		mCamNode->attachObject(mCamera);
		break;

	//视角3
	case OIS::KC_3:
		mCamera->getParentSceneNode()->detachObject(mCamera);
		mCamNode = mSceneMgr->getSceneNode("CamNode3");
		mCamNode->attachObject(mCamera);
		break;

	//视角4
	case OIS::KC_4:
		mCamera->getParentSceneNode()->detachObject(mCamera);
		mCamNode = mSceneMgr->getSceneNode("CamNode4");
		mCamNode->attachObject(mCamera);
		break;

	//汽车视角
	case OIS::KC_5:
		mCamera->getParentSceneNode()->detachObject(mCamera);
		mCamNode = mSceneMgr->getSceneNode("nodeCar");
		mCamNode->attachObject(mCamera);
		break;

	//飞机视角
	case OIS::KC_6:
		mCamera->getParentSceneNode()->detachObject(mCamera);
		mCamNode = mSceneMgr->getSceneNode("nodeHelic");
		mCamNode->attachObject(mCamera);
		break;

	//相机移动
	case OIS::KC_UP:
	case OIS::KC_W:
		mDirection.z = -mMove;
		break;

	case OIS::KC_DOWN:
	case OIS::KC_S:
		mDirection.z = mMove;
		break;

	case OIS::KC_LEFT:
	case OIS::KC_A:
		mDirection.x = -mMove;
		break;

	case OIS::KC_RIGHT:
	case OIS::KC_D:
		mDirection.x = mMove;
		break;

	case OIS::KC_E:
		mDirection.y = -mMove;
		break;

	case OIS::KC_Q:
		mDirection.y = mMove;
		break;

	default:
		break;
	}

	return true; 
}

//摄像机移动
bool OgreCampus::keyReleased(const OIS::KeyEvent& ke) 
{ 
	switch (ke.key)
	{
	case OIS::KC_UP:
	case OIS::KC_W:
		mDirection.z = 0;
		break;

	case OIS::KC_DOWN:
	case OIS::KC_S:
		mDirection.z = 0;
		break;

	case OIS::KC_LEFT:
	case OIS::KC_A:
		mDirection.x = 0;
		break;

	case OIS::KC_RIGHT:
	case OIS::KC_D:
		mDirection.x = 0;
		break;

	case OIS::KC_PGDOWN:
	case OIS::KC_E:
		mDirection.y = 0;
		break;

	case OIS::KC_PGUP:
	case OIS::KC_Q:
		mDirection.y = 0;
		break;

	default:
		break;
	}

	return true; 
}

//鼠标
bool OgreCampus::mouseMoved(const OIS::MouseEvent& me) 
{
	MyGUI::InputManager::getInstance().injectMouseMove(me.state.X.abs, me.state.Y.abs, me.state.Z.abs);

	//鼠标右键+鼠标移动
	if (me.state.buttonDown(OIS::MB_Right))
	{
		mCamNode->yaw(Ogre::Degree(-mRotate * me.state.X.rel), Ogre::Node::TS_WORLD);
		mCamNode->pitch(Ogre::Degree(-mRotate * me.state.Y.rel), Ogre::Node::TS_LOCAL);
	}

	return true; 
}

bool OgreCampus::mousePressed(const OIS::MouseEvent& me, OIS::MouseButtonID id) 
{ 
	MyGUI::InputManager::getInstance().injectMousePress(me.state.X.abs, me.state.Y.abs, MyGUI::MouseButton::Enum(id));

	//光线的鼠标控制
	/*switch (id)
	{
	case OIS::MB_Left:
	Ogre::Light* light = mSceneMgr->getLight("Light1");
	light->setVisible(!light->isVisible());
	break;

	default:
	break;
	}*/

	return true; 
}

bool OgreCampus::mouseReleased(const OIS::MouseEvent& me, OIS::MouseButtonID id) 
{ 
	MyGUI::InputManager::getInstance().injectMouseRelease(me.state.X.abs, me.state.Y.abs, MyGUI::MouseButton::Enum(id));

	return true; 
}

/*地形相关函数*/
void getTerrainImage(bool flipX, bool flipY, Ogre::Image& img)	//获取地形高度图
{
	img.load("upc_terr.png", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

	if (flipX)
		img.flipAroundY();
	if (flipY)
		img.flipAroundX();
}

void OgreCampus::defineTerrain(long x, long y)	//defineTerrain函数的重载
{
	Ogre::String filename = mTerrainGroup->generateFilename(x, y);

	bool exists = Ogre::ResourceGroupManager::getSingleton().resourceExists(mTerrainGroup->getResourceGroup(),filename);

	if (exists)
		mTerrainGroup->defineTerrain(x, y);
	else
	{
		Ogre::Image img;
		getTerrainImage(x % 2 != 0, y % 2 != 0, img);
		mTerrainGroup->defineTerrain(x, y, &img);

		mTerrainsImported = true;
	}
}

void OgreCampus::initBlendMaps(Ogre::Terrain* terrain)	//blend together the different layers we defined in configureTerrainDefaults
{
	Ogre::Real minHeight0 = 6;
	Ogre::Real fadeDist0 = 15;
	/*Ogre::Real minHeight1 = 70;
	Ogre::Real fadeDist1 = 15;*/

	Ogre::TerrainLayerBlendMap* blendMap0 = terrain->getLayerBlendMap(1);
	//Ogre::TerrainLayerBlendMap* blendMap1 = terrain->getLayerBlendMap(2);

	float* pBlend0 = blendMap0->getBlendPointer();
	//float* pBlend1 = blendMap1->getBlendPointer();

	for (Ogre::uint16 y = 0; y < terrain->getLayerBlendMapSize(); ++y)
	{
		for (Ogre::uint16 x = 0; x < terrain->getLayerBlendMapSize(); ++x)
		{
			Ogre::Real tx, ty;

			blendMap0->convertImageToTerrainSpace(x, y, &tx, &ty);

			Ogre::Real height = terrain->getHeightAtTerrainPosition(tx, ty);

			Ogre::Real val = (height - minHeight0) / fadeDist0;
			val = Ogre::Math::Clamp(val, (Ogre::Real)0, (Ogre::Real)1);
			*pBlend0++ = val;

			/*val = (height - minHeight1) / fadeDist1;
			val = Ogre::Math::Clamp(val, (Ogre::Real)0, (Ogre::Real)1);
			*pBlend1++ = val;*/
		}
	}

	blendMap0->dirty();
	//blendMap1->dirty();
	blendMap0->update();
	//blendMap1->update();
}

void OgreCampus::configureTerrainDefaults(Ogre::Light* light)
{
	mTerrainGlobals->setMaxPixelError(8);			//sets the largest error in pixels allowed between our ideal terrain and the mesh that is created to render it
	mTerrainGlobals->setCompositeMapDistance(3000);	//determines the distance at which Ogre will still apply our lightmap

	//pass lighting information to our terrain.
	mTerrainGlobals->setLightMapDirection(light->getDerivedDirection());
	mTerrainGlobals->setCompositeMapAmbient(mSceneMgr->getAmbientLight());
	mTerrainGlobals->setCompositeMapDiffuse(light->getDiffuseColour());

	Ogre::Terrain::ImportData& importData = mTerrainGroup->getDefaultImportSettings();	//导入数据
	importData.terrainSize = 513;
	importData.worldSize = 12000.0;
	importData.inputScale = 60;		// how the heightmap image will be scaled up for the 
	importData.layerList.resize(2);		//resize调整大小

	//set each texture's worldSize and add them to the list
	//The default material generator requires two textures per layer: a diffuse specular texture and a heightmap texture.
	importData.layerList[0].worldSize = 513;
	importData.layerList[0].textureNames.push_back("cement.jpg");
	//importData.layerList[0].textureNames.push_back("rockwall_NH.tga");
	importData.layerList[1].worldSize = 513;
	importData.layerList[1].textureNames.push_back("GreenSkin.jpg");
	importData.layerList[1].textureNames.push_back("grass_green-01_normalheight.dds");
	/*importData.layerList[2].worldSize = 100;
	importData.layerList[2].textureNames.push_back("growth_weirdfungus-03_diffusespecular.dds");
	importData.layerList[2].textureNames.push_back("growth_weirdfungus-03_normalheight.dds");*/
}




#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        OgreCampus app;

        try {
            app.go();
        } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif
