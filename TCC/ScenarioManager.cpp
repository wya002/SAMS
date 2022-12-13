#include "ScenarioManager.h"
#include "tinyxml.h"

void ScenarioManager::load()
{
	TiXmlDocument ReadDoc;
	ReadDoc.LoadFile("C:/Users/User/Desktop/Test.xml");

	// 루트 가져오기
	TiXmlElement* ReadRoot = ReadDoc.FirstChildElement("DB");
	TiXmlElement* sub1 = ReadRoot->FirstChildElement("Synario")->FirstChildElement("SynarioStart");
	TiXmlElement* sub2 = ReadRoot->FirstChildElement("Synario")->FirstChildElement("SynarioDestination");
	TiXmlElement* sub3 = ReadRoot->FirstChildElement("Synario")->FirstChildElement("SynarioMSS");

	// 노드를 다루기 위한 핸들
	TiXmlHandle handle1(0);
	TiXmlHandle handle2(0);
	TiXmlHandle handle3(0);
	handle1 = TiXmlHandle(sub1);
	handle2 = TiXmlHandle(sub2);
	handle3 = TiXmlHandle(sub3);

	TiXmlAttribute* pAttrib1;
	TiXmlAttribute* pAttrib2;
	TiXmlAttribute* pAttrib3;
	pAttrib1 = sub1->FirstAttribute();
	pAttrib2 = sub2->FirstAttribute();
	pAttrib3 = sub3->FirstAttribute();

	// 초기위치 값 변수 할당
	pAttrib1 = pAttrib1->Next();
	int x1 = pAttrib1->IntValue();
	pAttrib1 = pAttrib1->Next();
	int y1 = pAttrib1->IntValue();

	// 목표위치 값 변수 할당
	pAttrib2 = pAttrib2->Next();
	int x2 = pAttrib2->IntValue();
	pAttrib2 = pAttrib2->Next();
	int y2 = pAttrib2->IntValue();

	// 목표위치 값 변수 할당
	pAttrib3 = pAttrib3->Next();
	int x3 = pAttrib3->IntValue();
	pAttrib3 = pAttrib3->Next();
	int y3 = pAttrib3->IntValue();

}
