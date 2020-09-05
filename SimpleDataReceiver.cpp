//---------------------------------------------------------------------------
#pragma warning ( disable : 4503 )


#ifdef _WIN32
    #include <Windows.h>
    #include <process.h>
#else
    #include <dlfcn.h>
    #define GetProcAddress dlsym

   #include <thread>
#endif

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <vector>
#include <set>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iostream>

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

#include "DSimUI.h"			// coreDS API UI include
#include "DSimAPI.hpp"		// coreDS API main functions


using namespace DSimAPI;

std::string mSelectedConfiguration="-1";
std::map<std::string, std::string> mDSIMParameters;
bool mDebugEnabled = false;
bool mReload = false;

bool mEnabledLogging = false;
bool mEnableScripting = true;
bool mEnableLoggingToWindow = true;
std::string mLogFilePath ="coreDSlog.log";
bool mDisableWord = false;
CDSimAPI mDSimManager;

bool lbRunning = true;
bool lbRunningSim = true;
	
#ifdef _WIN32
	void commandlineparameter_thread(void* lpParameter)
#else
    void commandlineparameter_thread()
#endif
{
	do
	{
		string parameter;
		if (getline(cin, parameter))
		{
			if (!parameter.empty())
			{
				if (parameter == "q") //quit the software
				{
					lbRunning = false;
					lbRunningSim = false;
				}
				else if (parameter == "s") //stop the current simulation to start a new one
				{
					lbRunningSim = false;
				}
			}
		}
	}
	while(lbRunning);
}

void messageReceived(const std::string &iMessageName, const std::map<std::string, std::string > &oDataStruct)
{
	std::map<std::string, std::string >::const_iterator iter = oDataStruct.begin();
	for (; iter != oDataStruct.end(); iter++)
	{
		printf("Message: %s\t%s\n", (*iter).first.c_str(), (*iter).second.c_str());
	}
}

void objectRemoved(const std::string &objectclassName)
{
	printf("Object deleted: %s\n", objectclassName.c_str());
}

void objectDiscovered(const std::string &objecttypeName, const std::string &objectUniqueIdentifier, const std::string &objectName)
{
	printf("Object discovered: %s\t%s\t%s\n", objecttypeName.c_str(), objectUniqueIdentifier.c_str(), objectName.c_str());
}

void objectRemoved1(const std::string &objectclassName)
{
	printf("Object deleted -- obj1: %s\n", objectclassName.c_str());
}

void objectDiscovered1(const std::string &objecttypeName, const std::string &objectUniqueIdentifier, const std::string &objectName)
{
	printf("Object discovered -- obj1: %s\t%s\t%s\n", objecttypeName.c_str(), objectUniqueIdentifier.c_str(), objectName.c_str());
}


void updateAircraftPos(const std::string &oLocalUniqueObjectIdentifier, const std::string &objectType, std::map<std::string, std::string > &oDataStruct)
{
	std::map<std::string, std::string >::const_iterator iter = oDataStruct.begin();
	for(; iter != oDataStruct.end(); iter++)
	{
		printf("%s:  %s\t%s\n", objectType.c_str(), (*iter).first.c_str(), (*iter).second.c_str());
	}
}

int main(int argc, char* argv[])
{
	std::string lSelectedLUAEditor = "Unknown Editor";

	std::map<std::string, std::set< std::string > > lInputObjectVariables;
	lInputObjectVariables["ItemInput"].insert("X");
	lInputObjectVariables["ItemInput"].insert("Y");
	lInputObjectVariables["ItemInput"].insert("Z");

	lInputObjectVariables["ItemInput1"].insert("X");
	lInputObjectVariables["ItemInput1"].insert("Y");
	lInputObjectVariables["ItemInput1"].insert("Z");

	setInputObjectVariables(lInputObjectVariables);

	std::map<std::string, std::set< std::string > > linputMessageVariables;
	linputMessageVariables["CollisionIn"].insert("CollisionX");
	linputMessageVariables["CollisionIn"].insert("CollisionY");
	linputMessageVariables["CollisionIn"].insert("CollisionZ");
	setInputMessageVariables(linputMessageVariables);

	std::cout << "This is a simple testing application that sends a random X value" << std::endl;
	std::cout << "Press 'q' to QUIT" << std::endl;
	std::cout << "Press 's' to change simulation parameters" << std::endl;
	
	#ifdef _WIN32
		_beginthread(&commandlineparameter_thread, 0, NULL);
	#else
        std::thread t1(commandlineparameter_thread);
	#endif

	do
	{
		std::string  lSelectedConfig  = "";
		std::string useless = "";

		//the UI share globals states
		showUI(lSelectedConfig, useless,  mEnableScripting, lSelectedLUAEditor, mDisableWord, mDebugEnabled, mReload,mEnableLoggingToWindow, mEnabledLogging, mLogFilePath,  false, false, INT_MAX);

		mSelectedConfiguration = std::string(lSelectedConfig);
		if (mSelectedConfiguration == "0") 
		{
			mSelectedConfiguration = -1;;
		}
		else
		{
			mDSIMParameters["LogError"] = mEnabledLogging ? "1" : "0";
			mDSIMParameters["LogErrorWindow"] = mEnableLoggingToWindow ? "1" : "0";
			mDSIMParameters["LogErrorPath"] = mLogFilePath;
			mDSIMParameters["ReloadScriptEachUse"] = mReload ? "1" : "0";;
			mDSIMParameters["EnableScripting"] = mEnableScripting ? "1" : "0";;
			mDSIMParameters["EnableDebugging"] = mDebugEnabled ? "1" : "0";;

			try
			{
				mDSimManager.deinit();
				mDSimManager.init(mSelectedConfiguration, mDSIMParameters);	

				mDSimManager.registerObjectUpdateHandler("ItemInput", updateAircraftPos);
				mDSimManager.registerNewObjectFoundHandler("ItemInput", objectDiscovered);
				mDSimManager.registerObjectRemovedHandler("ItemInput", objectRemoved);

				mDSimManager.registerNewObjectFoundHandler("ItemInput1", objectDiscovered1);
				mDSimManager.registerObjectRemovedHandler("ItemInput1", objectRemoved1);
				mDSimManager.registerObjectUpdateHandler("ItemInput1", updateAircraftPos);
				
				mDSimManager.registerMessageReceivedHandler("CollisionIn", messageReceived);
			}
			catch(std::exception &e)
			{
				cout << e.what() << endl;
			}
		}

		lbRunningSim = true;
		
		while(lbRunningSim)
		{
			try
			{
				mDSimManager.step();
			}
			catch (const std::exception &e)
			{
				cout << e.what() << endl;
			}
		}
	}
	while(lbRunning);
}


