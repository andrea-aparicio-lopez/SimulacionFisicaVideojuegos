#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include "Vector3D.h"

#include <iostream>

std::string display_text = "This is a test";


using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;

RenderItem* ori;
RenderItem* xAxis;
RenderItem* yAxis;
RenderItem* zAxis;


// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);

	// EJES
	Vector3D origin(0), x_axis(10,0,0), y_axis(0,10,0), z_axis(0,0,10);
	
	PxSphereGeometry sphereGeo = PxSphereGeometry(1.0f);
	// Origen de coordenadas
	PxShape* originShape = CreateShape(sphereGeo);
	PxTransform* originTr = new PxTransform(origin.x, origin.y, origin.z);
	PxVec4 originColor(1, 1, 1, 1);
	ori = new RenderItem(originShape, originTr, originColor);
	RegisterRenderItem(ori);

	// Eje X
	PxShape* xShape = CreateShape(sphereGeo);
	PxTransform* xTr = new PxTransform(x_axis.x, x_axis.y, x_axis.z);
	PxVec4 xColor(x_axis.x, x_axis.y, x_axis.z, 1);
	xAxis = new RenderItem(xShape, xTr, xColor);
	RegisterRenderItem(xAxis);

	// Eje Y
	PxShape* yShape = CreateShape(sphereGeo);
	PxTransform* yTr = new PxTransform(y_axis.x, y_axis.y, y_axis.z);
	PxVec4 yColor(y_axis.x, y_axis.y, y_axis.z, 1);
	yAxis = new RenderItem(yShape, yTr, yColor);
	RegisterRenderItem(yAxis);

	// Eje Z
	PxShape* zShape = CreateShape(sphereGeo);
	PxTransform* zTr = new PxTransform(z_axis.x, z_axis.y, z_axis.z);
	PxVec4 zColor(z_axis.x, z_axis.y, z_axis.z, 1);
	zAxis = new RenderItem(zShape, zTr, zColor);
	RegisterRenderItem(zAxis);
}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	gScene->simulate(t);
	gScene->fetchResults(true);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	gFoundation->release();
	DeregisterRenderItem(ori);
	DeregisterRenderItem(xAxis);
	DeregisterRenderItem(yAxis);
	DeregisterRenderItem(zAxis);
}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch(toupper(key))
	{
	//case 'B': break;
	//case ' ':	break;
	case ' ':
	{
		break;
	}
	default:
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}


int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}